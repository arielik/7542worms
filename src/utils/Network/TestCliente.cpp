#include "Cliente.h"

Cliente::Cliente()
	: input(Socket())
	, output(Socket())
	, pl()
	, localChanges()
	, networkChanges()
	, m()
	, n()
	, somethingToTell(m)
	, somethingToUpdate(n)
{
}

Cliente::Cliente(std::string playerID, char* ip, int port)
	: input(Socket())
	, output(Socket())
	, pl(playerID)
	, localChanges()
	, networkChanges()
	, m()
	, n()
	, somethingToTell(m)
	, somethingToUpdate(n)

{

	input.connect2(ip, port+1);
	printf("Connected to data port: %d", port);
	output.connect2(ip, port);
	printf("Connected to update port: %d", port+1);
	this->srvStatus = true;

	threadData data;
	data.cli = this;

	getRemoteWorld(); // recibo el mundo o un codigo de reject

	//Thread de escucha de mensajes en la red
	Thread networkUpdatesThread("Net Updates",applyNetworkChanges,&data);

	//Thread de escucha de actualizaciones locales
	Thread localUpdatesThread("LocalUpdates",notifyLocalUpdates,&data);

	//Thread de keepalive (Listen for disconnect)
	Thread keepaliveThread("Listening",netListener,&data);

	//Thread de simulacion de cambios locales
	Thread clientSideThread("Emulation",clientSideEmulation,&data);

}


int Cliente::clientSideEmulation(void *data){

	printf("\nDisparado apply Network Changes thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	Condition* cond = &((Cliente*)((threadData*)data)->cli)->somethingToTell;
	
	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;
	
	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();
	msg->type = KEEPALIVE;
	size_t i = 0;

	while(true){
		//copy and (un)comment this to mock local changes
		Sleep(10);
		i++;

		//Esto es lo que se va disparar al haber una accion del lado del cliente
		if ( i == 500 || i == 2000 ){
			m->lock();
			try{
				//printf("\nGot something from client %s at i: %d ;)",playerId,i );
				Playable p;
				p.wormid=37;
				cli->localChanges.push_back(p);
			}catch(...){
				m->unlock();
				throw std::current_exception();
			}
			m->unlock();
			cond->signal();
		}

	}

	return 0;
}


Cliente::~Cliente() {


}


int Cliente::applyNetworkChanges(void *data){

	printf("\nDisparado apply Network Changes thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	Condition* cond = &((Cliente*)((threadData*)data)->cli)->somethingToTell;
	
	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;
	
	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();
	msg->type = KEEPALIVE;

	while(true){



		// Wait for network updates from server
		n->lock();
		if ( cli->networkChanges.empty() ){
			netcond->wait();
		}
		printf("\nGot a network change");

		// TODO: Apply playable to the gameEntities at client side
		Playable p;
		p = cli->networkChanges.back();

		cli->updateModel(p);

		cli->networkChanges.pop_back();


		n->unlock();
	}

	return 0;


}


bool Cliente::updateModel(Playable p){

	//Search worm id
	//p.wormid

	//Update his position to new x,y
	//p.x;
	//p.y;

	return true;
}

//
int Cliente::notifyLocalUpdates(void *data){

	printf("\nDisparado notify local updates thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	Condition* cond = &((Cliente*)((threadData*)data)->cli)->somethingToTell;
	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();

	while(true){
		m->lock();
		if ( cli->localChanges.empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		printf("\nGot a local change");

		msg->play.wormid = cli->localChanges.back().wormid;
		msg->play.weaponid = cli->localChanges.back().weaponid;
		msg->play.state = cli->localChanges.back().state;
		msg->play.action = cli->localChanges.back().action;
		msg->playerID = cli->pl.c_str();

		msg->type = UPDATE;

		if ( !cli->output.sendmsg(*msg) ) {
			//Log::e("connection error");
			printf("\nClient: connection error");
			m->unlock();
			return 1;
		}

		cli->localChanges.pop_back();
		m->unlock();
	}
	return 0;
}


int Cliente::netListener(void* data){
	printf("\nDisparado net listen thread");
	Cliente* cli = ((threadData*)data)->cli;
	Mutex* m = &((Cliente*)((threadData*)data)->cli)->m;
	Condition* cond = &((Cliente*)((threadData*)data)->cli)->somethingToTell;
	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();

	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;

	while(true){

		if ( !cli->input.rcvmsg(*msg) ) {
			printf("\nDesconectando cliente at listening state");
			//TODO: metodo de desconexion del server, mensaje y grisar pantalla o retry

			return 1;
		}
		printf("\nGot network change");
		switch(msg->type){
		case UPDATE:
			n->lock();
			try{
				//printf("\nGot something from client %s at i: %d ;)",playerId,i );
				Playable p;
				/*p.wormid=37;*/
				
				p.wormid = msg->play.wormid;
				p.weaponid = msg->play.weaponid;
				p.x = msg->play.x;
				p.y = msg->play.y;

				cli->networkChanges.push_back(p);

			}catch(...){
				n->unlock();
				throw std::current_exception();
			}
			n->unlock();
			netcond->signal();

			break;
		}
	
	}

	return 0;
}

int Cliente::login(){

	Datagram msg;

	msg.type = LOGIN;
	std::strcpy((char*)&msg.playerID,this->pl.c_str()); // works?
	printf("\nplayer id: %s",msg.playerID.c_str());

	this->sendDatagram(msg);
	//Send login datagram

	return 0;
}


int Cliente::sendDatagram(Datagram msg){

	if ( !this->output.sendmsg(msg) ) {
		//Log::e("connection error");
		printf("\nClient: connection error");
		return 1;
	}
	return 0;

}



void Cliente::getRemoteWorld() {
	Messages type = LOGIN;
	std::vector<uint8_t> datos;
	std::vector<uint8_t> buffer;
	Datagram* msg = new Datagram();
	
	//Login to server
	msg->type = LOGIN;
	msg->playerID = "PLAYER1"; 
	printf("\nLogin player id: %s",msg->playerID.c_str());

	if ( !this->output.sendmsg(*msg) ) {
		//Log::e("connection error");
		printf("\nClient: connection error");
		return;
	}

	printf("\nSTART - Retrieving data from server");
	if (!this->input.rcvmsg(*msg)) {
		//Log::e("connection error");
		printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}
	printf("\nDONE - Retrieving data from server, level: %s", msg->play.level);
	//TODO SET LEVEL ON CLIENT


	if (!this->input.rcvmsg(*msg)) {
		//Log::e("connection error");
		printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}
	printf("\nDONE - Retrieving data from server, world elements: %d", msg->elements);
	int count = msg->elements;
	for ( int i=0; i < count; i++){
		if (!this->input.rcvmsg(*msg)) {
			//Log::e("connection error");
			printf("\nClient: connection error - Server disconnected/not responding");
			return;
		}
		printf("\nGetted worm id: %d",msg->play.wormid);
		//TODO @aliguo
		//Trigger changes into game elements of the client


	}

	


}

bool Cliente::serverAlive () {
	return this->srvStatus;
}





void Cliente::lockLocalMutex(){
	this->m.lock();
}

void Cliente::unlockLocalMutex(){
	this->m.unlock();
}

void Cliente::lockNetworkMutex(){
	this->n.lock();
}

void Cliente::unlockNetworkMutex(){
	this->n.unlock();
}

void Cliente::addLocalChange(Playable p){
	this->localChanges.push_back(p);
}

void Cliente::signalLocalChange(){
	this->somethingToTell.signal();
}

void Cliente::signalNetworkChange(){
	this->somethingToUpdate.signal();
}

int Cliente::sendMsg(Messages type, std::vector<uint8_t> buffer) {
	if ( !this->output.sendmsg(type, buffer) ) {
		//Log::e("connection error");
		printf("Client: connection error");
		return 1;
	}
	return 0;

}

int main(){

	Cliente myClient("aliguori","localhost",10025);
	//Cliente myClient2("localhost",10026);
	size_t i = 0;

	while(true){
	//	Sleep(10);
	//	i++;

	//	//Esto es lo que se va disparar al haber una accion del lado del cliente
	//	if ( i == 500 || i == 2000 ){
	//		myClient.lockLocalMutex();
	//		try{
	//			printf("\nGot something from client at i: %d ;)",i );
	//			Playable p;
	//			p.wormid=37;
	//			myClient.addLocalChange(p);
	//		}catch(...){
	//			myClient.unlockLocalMutex();
	//			throw std::current_exception();
	//		}
	//		myClient.unlockLocalMutex();
	//		myClient.signalLocalChange();
	//	}


	}

	return 0;
}