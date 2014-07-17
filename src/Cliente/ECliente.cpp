#include "./Cliente.h"



//
//Cliente::Cliente(Servidor* server)
//	: input(Socket())
//	, output(Socket())
//	, pl()
//	, localChanges()
//	, networkChanges()
//	, m()
//	, n()
//	, somethingToTell(m)
//	, somethingToUpdate(n)
//{
//	this->server = server;
//}

Cliente::~Cliente(void){

}

bool Cliente::begin(){
	// TODO @future: Initialize sockets
	//this->connect2server(this->server);
	return true;
}



void Cliente::loop(void){
	Log::i("============== INICIANDO CLIENTE =============");		

	Uint32 start = 0;
	bool quit = false;

	bootstrap.init();
	GameViewBuilder* builder = new GameViewBuilder(&this->cController, &this->domain);

	builder->setPlayerID(this->pl);
	this->currentActivity = new GameActivity (bootstrap.getScreen(), *builder, &this->cController);
	this->gameActivity = static_cast<GameActivity*> (currentActivity);
	
	
	/** refresh the initial view*/
	this->currentActivity->render();
	this->cController.addListener(this);


	int running = 0;
	
	bootstrap.getScreen().setState("Juego Creado");
	FPSmanager fpsManager;
	fpsManager.rate = 60;
	SDL_initFramerate(&fpsManager);
	while (!this->cController.isQuit()){
		cController.handlerEvent();
		this->runGame();
		currentActivity->update();
		currentActivity->render();
		SDL_framerateDelay(&fpsManager);
	}
	cController.destroy();
	bootstrap.getScreen().terminate();
	delete currentActivity;
	delete builder;

}

bool Cliente::run(){

	if( this->begin() == true ){
		this->loop();
	}else{
		Log::e("Error al iniciar el juego el cliente");
		return false;
	}
	return true;
}

void Cliente::destroyWorld(void){
	//TODO: Destructor
}



//
//bool Cliente::connect2server(Servidor* server){
//	this->cLevel = server->getLevel();
//	//this->cController = GameController(&this->cLevel);
//	
//	return true;
//}


Uint32 Cliente::time_left(void)
{
    Uint32 now;
    now = SDL_GetTicks();
    if (next_time <= now)
        return 0;
    else
        return next_time - now;
}

Uint32 Cliente::getTickInterval()
{
	int fps = 60;
	ParserYaml* aParser = ParserYaml::getInstance();
	fps = Util::string2int(aParser->getInstance()->getEscenarioFps());
	Uint32 tick_interval = 1000.0f / fps;
	return tick_interval;
}




void Cliente::runGame(){
	bootstrap.getScreen().setState("Juego corriendo");
	
	//this->server->getGameEngine().step();
}
/*
void Cliente::stopGame(){
	Log::i("Detencion de secuencia");
	bootstrap.getScreen().setState("Juego Pausado");
}*/
/*
void Cliente::iniGame(){
	//TODO: Regenerar el mundo
	Log::i("RE-Inicio de secuencia");
	bootstrap.getScreen().setState("Juego Reiniciado");
	this->server->getGameEngine().reInitWorld();
	currentActivity->update();
	currentActivity->render();
}
*/


/************************ Start Network Client Side code *************************/
Cliente::Cliente(std::string playerID, const char* ip, int port)
	: input(Socket())
	, output(Socket())
	, pl(playerID)
	, localChanges()
	, networkChanges()
	, m()
	, n()
	, somethingToTell(m)
	, somethingToUpdate(n)
	, domain()
{

	input.connect2(ip, port+1);
	printf("Connected to data port: %d", port);
	output.connect2(ip, port);
	printf("Connected to update port: %d", port+1);
	this->srvStatus = true;

	
	this->data.cli = this;

	this->domain.setPlayerID(this->pl);
	

	getRemoteWorld(); // recibo el mundo o un codigo de reject


	//Thread de escucha de mensajes en la red
	Thread networkUpdatesThread("Net Updates",applyNetworkChanges,&data);

	//Thread de keepalive (Listen for disconnect)
	Thread keepaliveThread("Listening",netListener,&data);

	//Thread de escucha de actualizaciones locales
	Thread localUpdatesThread("LocalUpdates",notifyLocalUpdates,&data);

	//Thread de simulacion de cambios locales
	//Thread clientSideThread("Emulation",clientSideEmulation,&data);

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


int Cliente::applyNetworkChanges(void *data){
	Sleep(10);
	printf("\nDisparado apply Network Changes thread");
	Cliente* cli = ((threadData*)data)->cli;
	
	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;
	
	char* playerId = ((threadData*)data)->p;
	EDatagram* msg = new EDatagram();
	msg->type = KEEPALIVE;

	while(true){

		Sleep(10);

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
	this->domain.updateElement(p.wormid, p.x, p.y );
	//Update his position to new x,y
	//p.x;
	//p.y;

	return true;
}

//
int Cliente::notifyLocalUpdates(void *data){
	printf("\nDisparado notify local updates thread");
	threadData* aThreadData = (threadData*)data;
	Cliente* cli = aThreadData->cli;
	Mutex* m = &cli->m;
	Condition* cond = &(cli->somethingToTell);
	char* playerId = aThreadData->p;
	EDatagram* msg = new EDatagram();

	while(true){
		m->lock();
		if ( cli->localChanges.empty() ){
			//printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		Log::t("\nGot a local change");

		msg->play[0].wormid = cli->localChanges.back().wormid;
		msg->play[0].weaponid = cli->localChanges.back().weaponid;
		msg->play[0].state = cli->localChanges.back().state;
		msg->play[0].action = cli->localChanges.back().action;
		msg->playerID = cli->pl.c_str();

		msg->type = UPDATE;

		if ( !cli->output.sendmsg(*msg) ) {
			Log::t("Local Update - Client connection with server error");
			m->unlock();
			return 1;
		}

		cli->localChanges.pop_back();
		m->unlock();
	}
	return 0;
}


int Cliente::netListener(void* data){
	Sleep(10);
	printf("\nDisparado net listen thread");
	Cliente* cli = ((threadData*)data)->cli;

	char* playerId = ((threadData*)data)->p;
	Datagram* msg = new Datagram();
	EDatagram* emsg = new EDatagram();

	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;

	while(true){

		Sleep(10);

		if ( !cli->input.rcvmsg(*emsg) ) {
			printf("\nDesconectando cliente at listening state");
			//TODO: metodo de desconexion del server, mensaje y grisar pantalla o retry

			return 1;
		}
		printf("\nGot network change");
		switch(emsg->type){
		case UPDATE:
			n->lock();
			try{
				//printf("\nGot something from client %s at i: %d ;)",playerId,i );
				Playable p;
				/*p.wormid=37;*/
				//p.wormid = msg->play.wormid;
				//p.weaponid = msg->play.weaponid;
				//p.x = msg->play.x;
				//p.y = msg->play.y;

				//cli->networkChanges.push_back(p);

				for ( int i=0; i < 15; i++){
					p.wormid = emsg->play[i].wormid;
					p.weaponid = emsg->play[i].weaponid;
					p.x = emsg->play[i].x;
					p.y = emsg->play[i].y;

					cli->networkChanges.push_back(p);
				}

			}catch(...){
				n->unlock();
				throw std::current_exception();
				break;
			}
			n->unlock();
			netcond->signal();

			break;
		case PLAYER_UPDATE:

			//Add the user to the players that are playing list
			cli->domain.addPlayer(emsg->playerID,emsg->playerState,0);

			//Aca metes el mensaje de player logged in/logged out
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
	EDatagram* msg = new EDatagram();
	
	//Login to server
	msg->type = LOGIN;
	msg->playerID = this->pl; 
	//printf("\nLogin player id: %s",msg->playerID.c_str());

	if ( !this->output.sendmsg(*msg) ) {
		//Log::e("connection error");
		printf("\nClient: connection error");
		return;
	}

	//printf("\nSTART - Retrieving data from server");
	if (!this->input.rcvmsg(*msg)) {
		//Log::e("connection error");
		printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}
	//printf("\nDONE - Retrieving data from server, level: %s", msg->play.level);
	//TODO SET LEVEL ON CLIENT


	if (!this->input.rcvmsg(*msg)) {
		Log::e("Client: connection error - Server disconnected/not responding");
		//printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}
	//printf("\nDONE - Retrieving data from server, world elements: %d", msg->elements);
	int count = msg->elements;
	Log::i("Going to load %d elements",count);

	if (!this->input.rcvmsg(*msg)) {
		Log::e("Client: connection error - Server disconnected/not responding");
		//printf("\nClient: connection error - Server disconnected/not responding");
		return;
	}


	for ( int i=0; i < count; i++){

		//Log::i("Getted worm id: %d at pos: %d, %d",msg->play.wormid, msg->play.x, msg->play.y);

		//Trigger changes into game elements of the client
		
		GameElement* elem = getElementFromPlayable(msg->play[i]);

		elem->playerID = msg->playerID;

		//Log::i("Inserting worm id: %d at pos: %f, %f",elem->getId(), elem->getPosition().first, elem->getPosition().second);

		this->domain.addElementToDomain(*elem);





	}

	


}

bool Cliente::serverAlive () {
	return this->srvStatus;
}


GameElement* Cliente::getElementFromPlayable(Playable p){

	GameElement* g = new GameElement(p.wormid,"PLAYER 1",WORM,p.x,p.y,0.0,40,40,15,false);

	return g;

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
		Log::e("connection error");
		//printf("Client: connection error");
		return 1;
	}
	return 0;

}

void Cliente::addLocalMovementFromView(Playable p){

	this->m.lock();
	try{
		this->localChanges.push_back(p);
	}catch(...){
		this->m.unlock();
		throw std::current_exception();
	}
	this->m.unlock();
	this->somethingToTell.signal();

}

void Cliente::OnMovement(MovementEvent e){

	Playable p;
	int wormIdSelected = this->gameActivity->getWormIdSelected();
	if (wormIdSelected > 0)
	{
		p.wormid = wormIdSelected;
		if (e.y == -1)
		{
			p.action = 	JUMP;
		}
		else if (e.x == 1) // derecha
		{
			p.action = 	MOVE_RIGHT;
		}
		else if (e.x == -1) // izquierda
		{
			p.action = 	MOVE_LEFT;
		} 
		else if (e.x == 0) // quieto
		{
			p.action = 	MOVE_STOP;
		}
		this->addLocalMovementFromView(p);
	}
}

