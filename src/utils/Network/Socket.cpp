#include "Socket.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <windows.h>
#include <sys/stat.h>


Socket::Socket()
	: usable(false)
	, fd()
{
}

Socket::Socket (uint16_t port)
	: usable(false)
	, fd()
{
	//*this = Socket::init();
	WSAData wsaData;

    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error == SOCKET_ERROR)
    {
        Log::e("Server: Winsock Failed to begin!");
        return;
    }
	Log::i("Server: WinSocket Started Correctly!");

	this->usable = true;
	
	this->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->fd == -1) {
		//Log::e("Couldn't open socket connection");
	}
	


	/* IP Address and connection info of the server A.K.A Destination */
	////printf("Creando socket");
	struct sockaddr_in server_addr;
	//Set properties for the host
	//memset((char *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	// Connect
	error = bind(this->fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if ( error == -1) {
		////printf("\nCouldn't bind server at specified address/port\n");
		////printf("Error during bind: %s, code: %d", std::strerror(errno),WSAGetLastError());
		//Log::e("Couldn't bind server at specified address/port"); 
	}

	error = listen(this->fd, 5); // Listen for connections

    if (error == SOCKET_ERROR)
    {
        Log::e("Server: Too deaf to listen"); 
    }

    Log::i("Server: Waiting for a client to connect"); // Just to keep us up to date





}

Socket Socket::init()
{
	Socket retval;

	WSAData wsaData;

    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error == SOCKET_ERROR)
    {
        std::cout << "Server: Winsock Failed to begin!\n";
        return 1;
    }
	std::cout << "Server: WinSocket Started Correctly!\n";
	retval.usable = true;
	
	retval.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (retval.fd == -1) {
		//Log::e("Couldn't open socket connection");
		////printf("Couldn't open socket connection");
	}
	this->fd = retval.fd;
	return retval;
}


Socket::~Socket(){
	if (usable) {
		closesocket(fd);
	}
}


bool Socket::rcvmsg (Datagram &msg){

	char buffer[MAX_MESSAGE_SIZE];
	size_t retries = 0;
	unsigned long messageSize;
    
	int nBytes = recv(fd, (char*)&messageSize, sizeof(messageSize), 0);

	if (nBytes == SOCKET_ERROR){
		return false;
	}
	
	messageSize = ntohl(messageSize); 
	//////printf("\nGet %d bytes",messageSize);

	while(retries < 3){
		int nBytes = recv(fd, (char*)(&buffer), messageSize, 0);
		Log::t("\nGetted %d bytes of %ld",nBytes,messageSize);
		if (nBytes == SOCKET_ERROR) {
			if ((errno == EAGAIN || errno == EWOULDBLOCK) &&retries < 3)  {
				retries++;
				Sleep(10);
				//////printf("\nRe-trying");
				continue;
			}
			Log::e("\nError getting message body");
			return false;
		}
		break;

	}
	//////printf("\nOK");
	memcpy(&msg,buffer,messageSize);
	
	//Log::i("\nbuffer player: %s, at pos: %d, %d",msg.playerID.c_str(),msg.play.x, msg.play.y );

	return true;
	
}


bool Socket::sendmsg(Datagram msg){

	size_t retries = 0;
	char buffer[MAX_MESSAGE_SIZE];
	unsigned long messageSize = sizeof(msg);
	unsigned long datagramSize = htonl(messageSize); 
	int nBytes;

	nBytes = send(fd, (char*)&datagramSize, sizeof(datagramSize), 0);

    if (nBytes == SOCKET_ERROR)
    {
        ////printf( "Client: Failed to send message size\n");
		return false;
    }


	if (!messageSize) {
		
		////printf("Sending empty message");
		return false;

	}
	//////printf("Send Bytes:  %d",messageSize);


	memcpy(&buffer,&msg,messageSize);

	while(retries < 3){
		nBytes = send(fd, buffer, messageSize, 0);
		//////printf("\n Client send %d bytes",nBytes);
		if (nBytes != messageSize){
			Log::e("sendmsg: I tried to send %d bytes, but I sent %d bytes", messageSize, nBytes);
		}
		if (nBytes == SOCKET_ERROR)
		{
			////printf("Client: failed to send it at first attempt.\n");

			if (errno == EAGAIN || errno == EWOULDBLOCK){
				Sleep(10);
				retries++;
				continue;
			}
			return false;
		}
		//////printf("\nClient: Sended OK. Player: %s, Worm: %d at pos: %d, %d",msg.playerID.c_str(), msg.play.wormid, msg.play.x, msg.play.y);
		return true;
	}
	////printf("Client: Failed to send after several retries.\n");
	return false;

}

bool Socket::connect2(std::string hostname, uint16_t port)
{
	
	//this->init();
	WSAData wsaData;

    int error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error == SOCKET_ERROR)
    {
        Log::e("Server: Winsock Failed to begin!\n");
        return false;
    }
	Log::e("Server: WinSocket Started Correctly!\n");

	this->usable = true;
	
	this->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->fd == -1) {
		//Log::e("Couldn't open socket connection");
	}
	


	//char server_name[40] = "localhost";
	struct hostent *server = gethostbyname(hostname.c_str());
	if (server == NULL) {
		Log::e("Couldn't find host: %s",hostname.c_str());
		////printf("Couldn't find host: %s",hostname.c_str());
		return false;
	}

	

	//Init server struct and its data
	struct sockaddr_in server_addr;
	memset((char *) &server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	memcpy(	(char *)&server_addr.sin_addr.s_addr,
			(char *)server->h_addr,
			server->h_length
		);
	
	//Connect server
	if (connect(this->fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR ) {
		Log::e("Couldn't connect to specified address/port: %s : %d",hostname.c_str(),port);
		////printf("Couldn't connect to specified address/port: %s : %d",hostname.c_str(),port);
		return false;
	}

	return true;
}

bool Socket::sendmsg (Messages tipo, std::vector<uint8_t> datos)
{
	
	size_t intentos = 0;
	size_t base = 0;
	size_t aEnviar = datos.size();
	
	if (datos.empty()) {
		//Log::e("Sending empty message");
		////printf("Sending empty message");

	}
	//////printf("\nSending bytes: %d",datos.size() );
	while (aEnviar != 0) {
		int bytes = send(fd, (char*)(&datos[base]), aEnviar, 0);
		
		if (bytes == -1) {
			if (errno == EINTR) {

				continue;
			} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				if (intentos < 3) {
					intentos += 1;
					Sleep(10);
					continue;
				}
			}
			
			////printf("\nFailed to send msg");
			return false;
		} else if (bytes == 0) {
			return false;
		} else {
			base += bytes;
			aEnviar -= bytes;
		}
		if (bytes != aEnviar){
			Log::e("sendmsg: I tried to send %d bytes, but I sent %d bytes", aEnviar, bytes);
		}
	}
	return true;	
	
}

bool Socket::rcvmsg (Messages &tipo, std::vector<uint8_t> &datos)
{
	// return Red::recibir(fd, tipo, datos);
	int tamEsperado = 10; //TODO
	std::vector<uint8_t> datosRetorno(tamEsperado);
	size_t intentos = 0;
	size_t base = 0;
	size_t aRecibir = tamEsperado;
	int bytes;
	while (aRecibir != 0) {
		bytes = recv(fd, (char*)(&datosRetorno[base]), aRecibir, 0);
		
		if (bytes == -1) {
			if (errno == EINTR) {
				continue;
			} else if (errno == EAGAIN || errno == EWOULDBLOCK) {
				if (intentos < 3) {
					intentos += 1;
					Sleep(10);
					continue;
				}
			}
			//Log::e("Failed to get data from remote host");
			//////printf("Failed to get data from remote host");
			return false;
		} else if (bytes == 0) {
			return false;
		} else {
			base += bytes;
			aRecibir -= bytes;
		}
	}
	using std::swap;
	swap(datos, datosRetorno);
	//////printf("\nGet %d bytes",bytes);
	return true;
	
}





void Socket::setListen (int tamCola)
{
	if (::listen(fd, 4) == -1) {
		// throw Log::Suceso(Log::FATAL, "No se pudo setear el tamanio maximo de la cola de conexiones pendientes en el port.");
	}
}

int Socket::getFD(){
	return this->fd;
}

void Socket::setRcvTimeout (long sec, long usec)
{
	struct timeval timeout;
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;

	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) == -1) {
		Log::e("Couldn't set specified timeout");
	}
}

void Socket::setSendTimeout (long sec, long usec)
{
	struct timeval timeout;
	timeout.tv_sec = sec;
	timeout.tv_usec = usec;

	if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) == -1) {
		
		Log::e("Couldn't set specified timeout");
	}
}

void Socket::setKeepAlive ()
{
	int iOption = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (const char *) &iOption,  sizeof(int)) == -1) {
		Log::e("Fallo seteo de la opcion keepalive en socket.");
	}
}

Socket Socket::aceptar ()
{
	Socket retval;

	struct sockaddr_in dirCli;
	socklen_t dirCliSize = sizeof (dirCli);
	retval.fd = accept(this->fd, (struct sockaddr*) &dirCli, &dirCliSize);

	if (retval.fd == -1) {
		//auto msg = "No se pudo aceptar la llamada de salida en el servidor.";
		//throw Log::Suceso(Log::ERROR, msg);
	}
	////printf("Recibida conexion %i de %s port %d\n", retval.fd,
	       //inet_ntoa(dirCli.sin_addr), ntohs(dirCli.sin_port));

	return retval;
}

int Socket::extraerFd ()
{
	usable = false;
	return fd;
}




// ********************************************************************************************************

bool Socket::rcvmsg (EDatagram &msg){

	char buffer[MAX_MESSAGE_SIZE];
	size_t retries = 0;
	unsigned long messageSize = sizeof(EDatagram);
	int nBytes = 0;
	int count = 0;

	while(retries < 5){
		nBytes = recv(fd, (char*)(&buffer), messageSize, 0);
		
		//Log::t("Getted %d bytes of %ld",nBytes,messageSize);
		if (nBytes == SOCKET_ERROR) {
			Sleep(5);
			Log::t("Re-trying because of error: %ld", WSAGetLastError());
			retries++;
		}

		//Si lo recibo en la primera vez 
		if ( nBytes == messageSize){
			Log::t("Getted ALL!");
			memcpy(&msg,buffer,messageSize);
			return true;
		}


		 if ( nBytes != messageSize && nBytes != SOCKET_ERROR ){
			 //Log::e("Socket::rcvmsg >> I can't recive all message");
			 memcpy(&msg + count,buffer,nBytes);
			 count = count + nBytes;
			 messageSize = messageSize - count;
		 }

		////Si lo termine de recibir tras varios intentos
		//if ( count == messageSize ){
		//	Log::t("Getted All, after some retries");
		//	return true;
		//}

	}

	if (retries == 5){
		Log::e("Error getting message body");
		return false;
	}
	return false;

	
}


bool Socket::sendmsg(EDatagram msg){

	size_t retries = 0;
	char buffer[MAX_MESSAGE_SIZE];
	unsigned long messageSize = sizeof(msg);
	int nBytes = 0;
	int count = 0;

	memcpy(&buffer,&msg,messageSize);

	while(retries < 5){
		nBytes = send(fd, buffer + count, messageSize, 0);
		
		if (nBytes == SOCKET_ERROR)
		{
			
			Sleep(5);
			retries++;
			Log::t("Re-trying because of error: %ld", WSAGetLastError());
			////printf("Re-trying because of error: %ld", WSAGetLastError());
		}

		//Si lo envio bien en la primera vez o tras varios intentos
		if ( nBytes == messageSize ){
			Log::t("Sended OK");
			return true;
		}

		if (nBytes != messageSize && nBytes != SOCKET_ERROR){
			count = count + nBytes;
			messageSize = messageSize - nBytes;
		}


		
	}

	////printf("Client: Failed to send after several retries.\n");
	return false;
}


bool Socket::sendFile(std::string path){

	FILE *file = fopen(path.c_str(), "rb");
	size_t retries = 0;
	struct stat stat_buf;
    int rc = stat(path.c_str(), &stat_buf);

	if (!file){
		fclose (file);
		return false;
	}

	//fseek( file, 0, SEEK_END );

	////printf("File Size: \n%d bytes\n", stat_buf.st_size);



	unsigned long datagramSize = htonl( stat_buf.st_size ); 
	int nBytes;

	nBytes = send(fd, (char*)&datagramSize, sizeof(datagramSize), 0);

    if (nBytes == SOCKET_ERROR || nBytes != sizeof(datagramSize))
    {
		Log::e( "Client: Failed to send message size, sended: %d",nBytes);
		return false;
    }


    char buffer[4096];
    //buffer = new char[size];
 
    fread(buffer, sizeof(buffer[0]), stat_buf.st_size, file);
	nBytes = 0;
	int count = 0;

	while(retries < 5){
		nBytes = send(fd, buffer + count, stat_buf.st_size, 0);
		
		if (nBytes == SOCKET_ERROR)
		{
			Log::i("Client: failed to send it at attempt n.:%d",retries);
			Sleep(10);
			retries++;
		}

		if (nBytes != stat_buf.st_size && nBytes != SOCKET_ERROR){
			count = count + nBytes;
		}

		//Si lo envio bien en la primera vez o tras varios intentos
		if ( nBytes == stat_buf.st_size || count == stat_buf.st_size ){
			Log::i("Sended FILE OK");
			return true;
		}

	}

	Log::e("I tried to send %d bytes, but I sent %d bytes", stat_buf.st_size, nBytes);
	return false;

}


bool Socket::receiveFile(std::string path){

	FILE *file = fopen(path.c_str(), "wb");
 
    int retries = 0;
	unsigned long messageSize;
    
	int nBytes = recv(fd, (char*)&messageSize, sizeof(messageSize), 0);

	if (nBytes == SOCKET_ERROR || nBytes != sizeof(messageSize)){
		Log::e("Failed to retrieve File size, getted %d bytes",nBytes);
		return false;
	}
	
	messageSize = ntohl(messageSize);
 
    char buffer[4096];
	nBytes = 0;
	int count = 0;
    while(retries < 5){
		nBytes = recv(fd, (char*)(&buffer), messageSize, 0);

		if (nBytes == SOCKET_ERROR) {
			Log::i("\nError getting message body, retrying n: %d",retries);
			retries++;
			Sleep(10);
		}

		 if ( nBytes != messageSize && nBytes != SOCKET_ERROR ){
			 fwrite(&buffer + count, sizeof(char), nBytes, file);
			 count = count + nBytes;
		 }

		 //Si lo recibo en la primera vez 
		 if (nBytes == messageSize){
			Log::i("File getted correctly");
			fwrite(&buffer, sizeof(char), nBytes, file);
			fclose(file);
			return true;
		}

		//Si lo termine de recibir tras varios intentos
		if ( count == messageSize ){
			Log::i("File getted correctly, after some retries");
			return true;
		}


	}
	
	Log::e("Couldn't get FILE properly");
	return false;

}

void Socket::defaultSocketOption()
{
        BOOL TRUE_BOOLEAN_VALUE = TRUE;
		int BOOLEAN_OPTION_LENGTH = sizeof(BOOL);
                if (setsockopt(this->fd, IPPROTO_TCP, TCP_NODELAY, (char*)&TRUE_BOOLEAN_VALUE, BOOLEAN_OPTION_LENGTH) == SOCKET_ERROR)
                {
                       Log::i("Imposible asignar opcion al socket ");
           
                }
}