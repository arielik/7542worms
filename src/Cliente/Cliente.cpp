
#include "./Cliente.h"


Cliente::Cliente(std::string playerID, std::string ip, int port)
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
	, domainMx()
	, updateDomain(domainMx)
	, serverPort(port)
	, serverIp(ip)
	, updater(&input, &output,&m,&n,&somethingToTell,&localChanges)
{
	this->loginOk = false;
	this->advance = SDL_CreateSemaphore( 1 );
	this->deleted = false;
	this->gameReady = false;
	this->gameOver = false;
		
}

Cliente::~Cliente(void){

}


void Cliente::run(){
	

	bootstrap.init();

	while( !this->deleted ){


		this->rebooted = false;
		Log::i("Bootstrap iniciado");
		this->waitActivity = new WaitActivity(bootstrap.getScreen());	
		this->gameActivity = new GameActivity(bootstrap.getScreen(), &this->domain, &this->cController, this->pl, this->updater);	


		if (!this->begin()){
			Log::e("Error al iniciar el juego el cliente");
		}
		this->loop();
		this->resetModel();
		bootstrap.reinit();

		Log::i("Game rebooted or ended");
		Sleep(10);
	}

	bootstrap.shoutDown();
	Log::i("Bootstrap finalizado");
}

/************************ Start Network Client Side code *************************/
bool Cliente::openConnection() {
	
	bool stat = input.connect2(serverIp.c_str(), serverPort+1);
	if (!stat){
		this->srvStatus = SERVER_NOT_RESPONDING;
		return false;
	}

	Log::i("Connected to data port: %d", serverPort);
	
	stat = output.connect2(serverIp.c_str(), serverPort);
	if (!stat){
		this->srvStatus = SERVER_NOT_RESPONDING;
		return false;
	}

	
	Log::i("Connected to update port: %d", serverPort+1);
	this->srvStatus = SERVER_OK;
	return true;
}

bool Cliente::begin(){


		if (!this->openConnection())
		{
			return false;
		}


	this->data.cli = this;
	strcpy(this->data.p,this->pl.c_str());
	this->domain.setPlayerID(this->pl);
	this->updater.setPlayerId(this->pl);


	if (this->updater.doLogin())
	{
		this->loginOk = true;
	}

	if (this->isLoginOk())
	{
		updater.retrieveLevel();

		// lo voy a lanzar despues de que el server me diga que comience el juego
		//getRemoteWorld(); 

		//Thread de escucha de mensajes en la red
		Thread networkUpdatesThread("Net Updates",applyNetworkChanges,&data);

		//Thread de keepalive (Listen for disconnect)
		Thread keepaliveThread("Listening",netListener,&data);

		//Thread de escucha de actualizaciones locales
		Thread localUpdatesThread("LocalUpdates",notifyLocalUpdates,&data);
		return true;
	}
	else
	{
		return false;
	}
}


void Cliente::getRemoteWorld() {

	EDatagram* msg = new EDatagram();
	
	//Get amount of users from the server
	Log::t("Getting amount of users from server ");
	if (!this->input.rcvmsg(*msg)) {
		Log::e("Client: connection error - Server disconnected/not responding while retrieving amount of users");
		this->srvStatus = SERVER_NOT_RESPONDING;
		return;
	}

	int count = msg->elements;
	Log::i("Going to load %d players",count);

	for ( int i=0 ; i < count ; i++ ){
		Log::t("Loading player: %d ",i);
		if (!this->input.rcvmsg(*msg)) {
			Log::e("Client: connection error - Server disconnected/not responding while retrieving their worms");
			this->srvStatus = SERVER_NOT_RESPONDING;
			return;
		}
		int els = msg->elements;
		this->domainMx.lock();
		int auxLife =0;
		for ( int j=0; j < els; j++){
			bool added = false;
			Log::i("Got worm id: %d at pos: %f, %f, action: %s, life %d",msg->play[j].wormid, msg->play[j].x, msg->play[j].y, Util::actionString(msg->play[j].action).c_str(), msg->play[j].life);

			//Trigger changes into game elements of the client
			GameElement* elem = getElementFromPlayable(msg->playerID, msg->play[j]);
			auxLife = auxLife + msg->play[j].life;		
			this->domain.addElementToDomain(*elem);
			
			if ( (msg->play[j].action == NOT_CONNECTED_RIGHT || msg->play[j].action == NOT_CONNECTED_LEFT || msg->play[j].action == NOT_CONNECTED) && !added ){
				//Set user disconnected
				Log::i("Adding player %s to team: %d",msg->playerID.c_str(), msg->type);
				this->domain.addPlayer(msg->playerID,DISCONNECTED,msg->type);
			}else if (!added){
				Log::i("Adding player %s to team: %d",msg->playerID.c_str(), msg->type);
				this->domain.addPlayer(msg->playerID,CONNECTED,msg->type);
				added = true;
			}
		}
		this->domain.setPlayerLife(msg->playerID,auxLife);
		this->domainMx.unlock();

	}
	//delete msg;
}



void Cliente::loop(void){
	Log::i("============== INICIANDO CLIENTE =============");		


	this->currentActivity = this->waitActivity;
	if (this->isLoginOk()) {
		this->showWaitting();
	}
	this->runGame();

	/** refresh the initial view*/
	this->currentActivity->render();
	informStateClient();
	FPSmanager fpsManager;
	fpsManager.rate = 30;
	SDL_initFramerate(&fpsManager);
	
	while (!this->cController.isQuit() && !this->rebooted ){		
		cController.handlerEvent();
		currentActivity->update();
		currentActivity->render();
		// evaluar cambio de pantalla

		if (this->gameOver) 
		{
			this->currentActivity = this->waitActivity;
		}
		else if (this->gameReady) 
		{
			this->currentActivity = this->gameActivity;
		} 
		

		SDL_framerateDelay(&fpsManager);

	}
	Log::i("Ending While LOOP");
	if ( this->cController.isQuit() ){
		Log::i("Ending cONTROLLER");
		this->deleted = true;
	}
	currentActivity->stop();
	Log::i("aCTIVITY sTOPPED");
	cController.destroy();
	Log::i("Controller destroyed");
	//this->disconnectClient();
	delete this->gameActivity;
	delete this->waitActivity;
	Log::i("Ending LOOP");



}


void Cliente::disconnectClient(){

	if (this->isLoginOk()) {
		Log::i("Doing LOGOUT");
		this->updater.doLogout();
		// TODO: Cerrar hilo y sockets

		//closesocket(this->input.getFD());
		//closesocket(this->output.getFD());

	}	
}


void Cliente::destroyWorld(void){
	//TODO: Destructor
}

void Cliente::informStateClient()
{
	if (this->srvStatus == SERVER_NOT_RESPONDING)
	{
		this->currentActivity->showMessageError("El servidor no responde. Vuelva a conectarse mas tarde");
	}
	else if (this->srvStatus == SERVER_TIMEDOUT)
	{
		this->currentActivity->showMessageError("El servidor ha dejado de responder");
	}
	else if (this->srvStatus == SERVER_OK)
	{
		this->currentActivity->showMessageInfo("Se ha registrado correctamente");
	}
}


void Cliente::runGame(){
	bootstrap.getScreen().setState("Jugando como " + this->pl);
}




int Cliente::applyNetworkChanges(void *data){
	Log::i("Cliente::applyNetworkChanges >> Disparado apply Network Changes thread");
	Cliente* cli = ((threadData*)data)->cli;
	
	Mutex* n = &((Cliente*)((threadData*)data)->cli)->n;
	Condition* netcond = &((Cliente*)((threadData*)data)->cli)->somethingToUpdate;
	
	char* playerId = ((threadData*)data)->p;
	EDatagram* msg = new EDatagram();
	msg->type = KEEPALIVE;

	while(true && !cli->cController.isQuit() && !cli->rebooted ){

		Sleep(1); 

		// Wait for network updates from server
		n->lock();
		while ( cli->clientQueue.empty() ){
			netcond->wait();
		}
		EDatagram temp = cli->clientQueue.front();
		cli->clientQueue.pop();
		n->unlock();

		Playable p;

		for ( int i=0; i < temp.elements; i++){
			p.wormid = temp.play[i].wormid;
			p.weaponid = temp.play[i].weaponid;
			p.life = temp.play[i].life;
			p.x = temp.play[i].x;
			p.y = temp.play[i].y;
			p.action = temp.play[i].action;
			cli->updateModel(p);
			Log::d("\nProcessing wid: %d, x: %f, y: %f, weapong %d, action %s", p.wormid,p.x,p.y, p.weaponid, Util::actionString(p.action).c_str() );
		}
	}
	if ( cli->cController.isQuit() )
		cli->deleted = true;

	Log::i("Cliente::applyNetworkChanges >> Terminado apply Network Changes thread");
	return 0;

}


bool Cliente::updateModel(Playable p){

	if ( p.action == CREATE_MISSIL ) {
		this->domainMx.lock();
		this->gameActivity->buildProjectile(p.wormid, p.x, p.y, p.weaponid, p.life, p.action);
		Log::d("Cliente::updateModel >> Creando proyectil id: %d, pos[ %f ul, %f ul], accion: %s, tipo %d, life: %d", p.wormid, p.x, p.y, Util::actionString(p.action).c_str(), p.weaponid, p.life);
		this->domainMx.unlock();
	
	} else 	if ( p.action != EXPLOSION ){		
		this->domainMx.lock();
		this->domain.updateElement(p.wormid, p.x, p.y, p.action, p.life, p.weaponid );
		this->domainMx.unlock();
	
	}else{
		Log::d("Cliente::updateModel >> Processing explosion id: %d, at pos[ %f ul, %f ul] of weapon %d action: %s", p.wormid, p.x, p.y, p.weaponid, Util::actionString(p.action).c_str());
		// lo actualiza para que llegue el EXPLOTE al misil con  id p.wormid tambien.
		this->domainMx.lock();
		this->domain.updateElement(p.wormid, p.x, p.y, p.action, p.life, p.weaponid );
		
		switch( p.weaponid ){
		case GRENADE:
			this->processExplosions( p.x, p.y, EXPLODE_RSMALL );
			break;
		case HOLY:
			this->processExplosions( p.x, p.y, EXPLODE_RGIANT );
			break;
		case DYNAMITE:
			this->processExplosions( p.x, p.y, EXPLODE_RMEDIUM );
			break;
		case BURRO:
			this->processExplosions( p.x, p.y, EXPLODE_RMEDIUM );
			this->gameActivity->buildExplosion(p.x, p.y, p.weaponid, EXPLODE_RMEDIUM);
			break;
		case AIRATTACK:
			this->processExplosions( p.x, p.y, EXPLODE_RSMALL );
			break;
		case BAZOOKA:
			this->processExplosions( p.x, p.y, EXPLODE_RSMALL );
			break;
		case SHEEP:
			this->processExplosions( p.x, p.y, EXPLODE_RSMALL );
			break;
		case BANANA:
			this->processExplosions( p.x, p.y, EXPLODE_RSMALL );
			break;
		default:
			this->processExplosions( p.x, p.y, EXPLODE_RSMALL );
			break;
		}
		
		this->domainMx.unlock();
	}

	return true;

}


int Cliente::notifyLocalUpdates(void *data){
	Log::i("Cliente::notifyLocalUpdates >> Disparado notify local updates thread");
	threadData* aThreadData = (threadData*)data;
	Cliente* cli = aThreadData->cli;
	Mutex* m = &cli->m;
	Condition* cond = &(cli->somethingToTell);
	char* playerId = aThreadData->p;
	EDatagram* msg = new EDatagram();

	while(true && !cli->cController.isQuit() && !cli->rebooted ){
		m->lock();
		if ( cli->localChanges.empty() ){
			////printf("\nwaiting.. is empty :(");
			cond->wait();
		}
		Log::t("\nGot a local change");

		msg->play[0].wormid = cli->localChanges.back().wormid;
		msg->play[0].weaponid = cli->localChanges.back().weaponid;
		msg->play[0].x =  cli->localChanges.back().x;
		msg->play[0].y =  cli->localChanges.back().y;
		msg->play[0].life = cli->localChanges.back().life;
		msg->play[0].action = cli->localChanges.back().action;
		msg->playerID = cli->pl.c_str();

		msg->type = UPDATE;

		if ( !cli->output.sendmsg(*msg) ) {
			if (  !cli->rebooted ){
				Log::t("Local Update - Client connection with server error");
				cli->srvStatus = SERVER_TIMEDOUT;
				cli->informStateClient();
			}
			m->unlock();
			
			return 1;
		}

		cli->localChanges.pop_back();
		m->unlock();
	}
	if ( cli->cController.isQuit() )
		cli->deleted = true;

	Log::i("Cliente::notifyLocalUpdates >> Terminado notify local updates thread");
	return 0;
}


int Cliente::netListener(void* data){
	Log::i("Cliente::netListener >> Disparado net listen thread");
	threadData* tData = (threadData*)data;
	Cliente* cli = tData->cli;
	char* playerId = tData->p;
	Mutex* n = &(cli)->n;
	Condition* netcond = &(cli)->somethingToUpdate;
	
	
	cli->getRemoteWorld();

	cli->gameActivity->buildView();

	cli->gameReady = true;

	EDatagram* emsg = new EDatagram();
	bool closeListen = false;
	while(!cli->cController.isQuit() && !closeListen && !cli->rebooted ){
		Sleep(10);
	
		if ( !cli->input.rcvmsg(*emsg) ) {
			Log::e("\nNETLISTENER: Desconectando cliente at listening state");
			cli->srvStatus = SERVER_TIMEDOUT;
			closeListen = true;
		}

		switch(emsg->type){
		case UPDATE:
			//Log::t("Got UPDATE message from server");
			
			try{
				Log::t("\nGot something from client %s worm: %d posY: %f",emsg->playerID.c_str(),emsg->play[0].wormid,emsg->play[0].y);
				n->lock();
				cli->clientQueue.push(*emsg);
				netcond->signal();
				n->unlock();

			}catch(...){
				
				throw std::current_exception();
				break;
			}
			
			
			break;

		case TURN_CHANGE:
			////Process turn variation
			if ( emsg->playerID.compare(playerId) ){
				//not my turn
				Log::i("Not My turn, turn for: %s, i am: %s",emsg->playerID.c_str(),playerId );
				cli->gameActivity->endMyTurn();
				cli->gameActivity->otherTurn(emsg->playerID);

			}else{
				//my turn
				Log::i("My turn ( %s ) :D",playerId );
				cli->gameActivity->beginMyTurn();
			}

			break;
			
		case PLAYER_UPDATE:
			//Add the user to the players that are playing list
			Log::i("Updated player: %s state to %d",emsg->playerID.c_str(), emsg->playerState);
			//cli->domain.addPlayer(emsg->playerID,emsg->playerState,0);
			cli->domain.updatePlayerState(emsg->playerID,emsg->playerState);

			if (emsg->playerState == DISCONNECTED)
			{
				Log::d("El usuario %s se ha DESCONECTADO ", emsg->playerID.c_str());
				cli->getCurrentActivity()->showMessageInfo("El usuario " + emsg->playerID + " se ha desconectado");	
			}
			else if (emsg->playerState == RECONNECTED)
			{
				Log::d("El usuario %s se ha RECONECTADO ", emsg->playerID.c_str());
				cli->getCurrentActivity()->showMessageInfo("El usuario " + emsg->playerID + " se ha reconectado");	
			}
			break;

		case TIME_UPDATE:
			//Llamo al metodo de Erik
			cli->gameActivity->printTimer(emsg->elements);
			break;

		case LIFE_UPDATE:
			Log::i("La vida del player %s se seteo en: %d",emsg->playerID.c_str(),emsg->play[0].life);
			cli->domain.setPlayerLife(emsg->playerID,emsg->play[0].life);
			break;

		case MAP_UPDATE:
			Log::i("\nDoing explosion: %f, %f, %d",emsg->play[0].x, emsg->play[0].y, emsg->play[0].weaponid);
			cli->processExplosions( emsg->play[0].x, emsg->play[0].y, emsg->play[0].weaponid );
			break;

		case LOGOUT:
			Log::i("Logging out");
			//TODO NESTOR: Pone la pantalla diciendo que cierre y vuelva a abrir
			closesocket(cli->input.getFD());
			closesocket(cli->output.getFD());
			break;

		case GAME_UPDATE:
			Log::i("We have a winner");
			if ( !emsg->playerID.compare(playerId) ){
				//YO GANE
				cli->showWinner();
				Log::i("YO: %s, gane",emsg->playerID.c_str() );
			}else{
				//PERDI
				cli->showGameOver();
				Log::i("YO: %s, perdi",emsg->playerID.c_str() );
			}
			break;

		case REINIT_SRV:
			Log::i("Resetting game");

			closesocket( cli->input.getFD() );
			closesocket( cli->output.getFD() );

			Sleep(15);
			cli->rebooted = true;
			return 0;
			break;

		}
	
	}

	if ( cli->cController.isQuit() )
		cli->deleted = true;

	Log::i("Cliente::netListener >> Terminado net listen thread");
	return 0;
}

void Cliente::reinitGame(){

	this->resetModel();

}

void Cliente::resetModel(){
	
	this->domain.domainElements.clear();
	this->domain.playersLife.clear();
	this->domain.playersPlaying.clear();
	this->localChanges.clear();

}


void Cliente::processExplosions(float x, float y, int radio){
	this->gameActivity->doExplotion(x, y, radio);
}



GameElement* Cliente::getElementFromPlayable(std::string playerID, Playable p){
	// OJO! Esto siempre crea worms
	GameElement* g = new GameElement(p.wormid,"PLAYER 1",WORM,p.x,p.y,0.0,40,40,15,false);
	g->playerID = playerID;
	g->setAction( p.action );
	g->setLife ( p.life );
	g->setWeapon ( p.weaponid );
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
		////printf("Client: connection error");
		return 1;
	}
	return 0;

}

void Cliente::showAlert()
{
	this->waitActivity->showAlert();
}

void Cliente::showWaitting()
{
	this->gameOver=false;
	this->waitActivity->showWaitting();
}

void Cliente::showWinner()
{
	this->gameOver = true;
	this->gameReady = false;
	this->waitActivity->showWinner();
}

void Cliente::showGameOver()
{
	this->gameOver = true;
	this->gameReady = false;
	this->waitActivity->showGameOver();
}