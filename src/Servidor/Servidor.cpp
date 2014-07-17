#include "Servidor.h"


Servidor::~Servidor(void){

}

bool Servidor::begin(void){

	return true;
}

void Servidor::loop(void){
	Log::i("============== INICIANDO SERVIDOR =============");		
	// Init conns from clients
	bool quit = false;		
	while (quit == false && !this->deleted){
		if( this->gameEngine.initWorld() ) quit = true;
	}

	return void();
}

bool Servidor::run(void){
	if( this->begin() == true ){
		this->loop();
	}else{
		return false;
	}
	return true;
}

void Servidor::destroyWorld(void){
	//TODO @future -  this->gameEngine.destroyWorld();
}

GameLevel* Servidor::getLevel(){

	return this->gameEngine.getLevel();
}

GameEngine Servidor::getGameEngine(){

	return this->gameEngine;
}


Servidor::Servidor(int nroPuerto, size_t cantJugadores)
	: input (nroPuerto) // En este port se recibe data del cliente
	, output (nroPuerto + 1) // Por aca realizamos updates a los clientes
	, cantJugadores(cantJugadores)
	, pList()
	, changes()
	, lock()
	, netlock()
	, playerslock()
	, worldlock()
	, canUpdate(lock)
	, canBroadcast(netlock)
	, canCreate(worldlock)
	, canAddNews(playerslock)
	, turnMgr(cantJugadores)
{

	this->advance = SDL_CreateSemaphore( 1 );
	this->deleted = false;
	jugadoresConectados = 0;

	//Carga el servidor con un nivel, ese nivel tiene el terreno y su fisica y los jugadores que han
	// sido registrados en el
	this->gameEngine.initWorld();


	/* Start threading stuff */
	this->data.srv = this;

	this->worldQ.type = UPDATE;

	//Start connection Loop, when a client connects I will trigger a new thread for him
	Thread waitConnections("Connection Handler Thread",wait4Connections,&data);

	//		Dispara el thread que ante un update modifica el mundo, simula un paso
	//		y notifica a los clientes.
	Thread clientThread("Updating Thread",updating,&data);

	Thread stepOverThread("step",stepOver,&data);

}

void Servidor::reinit(){

	this->advance = SDL_CreateSemaphore( 1 );
	this->deleted = false;
	jugadoresConectados = 0;

	/*	Start threading stuff	*/
	this->data.srv = this;

	this->worldQ.type = UPDATE;

	//	Start connection Loop, when a client connects I will trigger a new thread for him
	Thread waitConnections("Connection Handler Thread",wait4Connections,&data);

	//	Dispara el thread que ante un update modifica el mundo, simula un paso
	//	y notifica a los clientes.
	Thread clientThread("Updating Thread",updating,&data);

	//	Step Over the
	Thread stepOverThread("step",stepOver,&data);


}


int Servidor::updating(void* data){
	//printf("\n\n\nUpdating Thread running\n");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;
	std::vector<Playable>* changes =  &srv->changes;
	
	Condition* cond =  &srv->canUpdate;
	Mutex* m = &srv->lock;

	Condition* netcond =  &srv->canBroadcast;
	Mutex* n =  &srv->netlock;

	while(true && !srv->deleted){
		Sleep(10);

		m->lock();
		if ( changes->empty() ){
			cond->wait();
		}

		if ( srv->deleted ){
			printf("\nEXITING Updating Thread");
			return 0;
		}

		Playable p;
		p = srv->changes.back();

		srv->updateModel(p); 
		
		srv->changes.pop_back();
		m->unlock();
	}
	printf("\nEXITING Updating Thread");
	return 0;
}



int Servidor::stepOver(void* data){
	//printf("\n\n\StepOver Thread running\n");

	threadData* aThreadData = (threadData*)data;
	Servidor* srv = aThreadData->srv;
	
	Condition* netcond =  &srv->canBroadcast;
	Mutex* n =  &srv->netlock;

	Condition* worldcond =  &srv->canCreate;
	Mutex* w =  &srv->worldlock;

	Condition* canStart =  &srv->canAddNews;
	Mutex* allIn =  &srv->playerslock;
	
	srv->startNewTurn = false;
	int i=0;



	Timer timeHandler;
	
	bool doWeHaveAExplosion = false;
	bool simulationEnded = false;
	int waitingForMissil = false;

	float explosionTime = 0;
	float shootTime = 0;
	bool localShoot = false;

	allIn->lock();
	while ( srv->turnMgr.getRegisteredPlayers() != srv->cantJugadores ){
		canStart->wait();
	}
	allIn->unlock();

	if ( srv->deleted ){
		printf("\nEXITING StepOver Thread");
		return 0;
	}

	//printf("\nInicio tiempo");
	Sleep(10);

	timeHandler.start();
	//srv->notifyTurnForPlayer( srv->turnMgr.getNextPlayerTurn() );

	float stepTime = 0;


	while(true){
		
		if ( srv->deleted ){
			printf("\nEXITING StepOver Thread");
			return 0;
		}

		if ( srv->gameEngine.didWeShoot ){
			shootTime = timeHandler.elapsed();
			srv->gameEngine.didWeShoot = false;
			localShoot = true;
		}

		/* Si paso 1 segundo */
		if ( (timeHandler.elapsed() - stepTime) >= 1 ){
			stepTime = timeHandler.elapsed();
			srv->notifyTimeUpdate( TURN_DURATION - stepTime );
		
		}


		/* Se termino el turno o pasaron 5 seg desde el disparo */
		if ( timeHandler.elapsed() >= TURN_DURATION || (localShoot && ((timeHandler.elapsed() - shootTime)  >= 5) ) ){

			////printf("\nSe termino el turno o pasaron 5 seg desde el disparo");
			srv->gameEngine.stopPlayer( srv->turnMgr.getCurrentPlayerTurn() );

/* HUBO EXPLOSION y pasaron 5 seg despues del disparo o acabo el turno */
			if ( doWeHaveAExplosion ){

				printf("\n\nCAMBIO DE TURNO \n");
				/* Actualizo la vida y notifico */
				srv->processPlayersLife();



				/* Veo si hubo ganador */
				if ( srv->doWeHaveAWinner() ){
					printf("\nHay un ganador");
					srv->notifyWinner();
				}

				doWeHaveAExplosion = false;
				waitingForMissil = false;
				simulationEnded = false;
				localShoot = false;
				explosionTime = 0;
				shootTime = 0;
				stepTime = 0;
				timeHandler.reset();

				/* Inicio el turno del nuevo player */
				srv->notifyTurnForPlayer( srv->turnMgr.getNextPlayerTurn() );

/* NO DISPARO y se acabo el turno */
			}else if ( !localShoot ){

				printf("\n\nCAMBIO DE TURNO 2 (No disparo) \n");
				/* Actualizo la vida y notifico */
				srv->processPlayersLife();

				/* Veo si hubo ganador */
				if ( srv->doWeHaveAWinner() ){
					printf("\nHay un ganador");
					srv->notifyWinner();
				}
						
				doWeHaveAExplosion = false;
				waitingForMissil = false;
				simulationEnded = false;
				localShoot = false;
				explosionTime = 0;
				shootTime = 0;
				stepTime = 0;
				timeHandler.reset();

				/* Inicio el turno del nuevo player */
				srv->notifyTurnForPlayer( srv->turnMgr.getNextPlayerTurn() );

			}

/* DISPARO y NO HUBO EXPLOSION*/

		}

		Sleep(15);

		w->lock();
		
		waitingForMissil = srv->gameEngine.step();
		if ( waitingForMissil ){
			doWeHaveAExplosion = true;
		}

		w->unlock();

		//si algo cambio actualizo a los clientes
		if ( i>=1 ){
			i=0;
	
			//chequeo si hay clientes
			if ( srv->pList.size()  ){
				int res = srv->somethingChange();
				if ( res ){
					srv->worldQ.type = UPDATE;
					srv->notifyAll();
				}
			} 
		}
		i++;
	}
	printf("\nEXITING StepOver Thread");
	return 0;
}

int Servidor::somethingChange(){

	std::map<int,GameElement*> copy = this->gameEngine.getLevel()->getEntities();
	std::map<int,GameElement*>::iterator it = copy.begin();

	bool flag = false;
	int i=0;

	for ( ; it != copy.end() ; ++it){
		if( it->second->changed ){

			this->worldQ.play[i].wormid = it->second->getId();
			this->worldQ.play[i].x = it->second->getPosition().first;
			this->worldQ.play[i].y = it->second->getPosition().second;
			this->worldQ.play[i].life = it->second->getLife();
			this->worldQ.play[i].action = it->second->getAction();
			this->worldQ.play[i].weaponid = it->second->getWeaponId();

			flag = true;
			i++;
		}
		//if ( !static_cast<Worm*>(it->second)->isAlive() ){
		//	this->gameEngine.getLevel()->removeEntity(it->second->getId());
		//}
	}
	this->worldQ.elements = i; 
	return i;
}


bool Servidor::updateModel(Playable p){
	// p.life tiene la intensidad del arma
	//this->worldlock.lock();
	this->gameEngine.applyAction2Element(p.wormid, p.weaponid, p.x, p.y, p.action, p.life);
	//this->worldlock.unlock();
	return true;
}



int Servidor::wait4Connections(void* data){
	//this is where client connects. srv will hang in this mode until client conn
	//printf("Listening");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;

	std::vector<Playable>* changes = &srv->changes;

	Condition* cond = &srv->canUpdate;
	Mutex* m = &srv->lock;



	int players = 0;
	while (true && !srv->deleted){
		Sleep(10);
		while(srv->cantJugadores > srv->jugadoresConectados){
			
			Socket sClientO = srv->input.aceptar();
			Socket sClientI = srv->output.aceptar();

			threadData* dataCliente = new threadData();
			dataCliente->srv = srv;
			dataCliente->clientI = sClientI;
			dataCliente->clientO = sClientO;
			srv->jugadoresConectados++;
			Thread clientThread("Client Thread",initClient,dataCliente);
		}

		// Avisa si todos estan conectados
		if ( srv->jugadoresConectados == srv->cantJugadores){
			srv->initialNotify();
		}

		if ( srv->deleted ){
			printf("\nEXITING Wait4Clients Thread");
			return 0;
		}

	}
	printf("\nEXITING Wait4Clients Thread");
	return 0;
}


void Servidor::waitConnections(){

}


int Servidor::initClient(void* data){
	//printf("Disparado cliente");

	threadData* aThreadData = (threadData*)data;

	Servidor* srv = aThreadData->srv;

	std::vector<Playable>* changes = &srv->changes;
	Condition* cond = &srv->canUpdate;
	Mutex* m = &srv->lock;
	char* playerId = aThreadData->p;

	Condition* worldcond =  &srv->canCreate;
	Mutex* w =  &srv->worldlock;

	Condition* canStart =  &srv->canAddNews;
	Mutex* allIn =  &srv->playerslock;

	EDatagram* datagram = new EDatagram();

	// Receive LOGIN info
	if (! ((threadData*)data)->clientO.rcvmsg(*datagram)) {
		
		//printf("\nDesconectando cliente at login");
		closesocket(aThreadData->clientO.getFD());
		closesocket(aThreadData->clientI.getFD());
		srv->jugadoresConectados--;
		return 1;
	}

	w->lock();
	//Valido si puede estar en el nivel antes de avanzar
	Log::i("Valido nuevo cliente en el server - %d", datagram->playerID.c_str());
	if ( !srv->getGameEngine().registerPlayer(datagram->playerID) ){
		w->unlock();
		//printf("\nCliente no permitido en el server");
		Log::i("Cliente ya resgistrado en el server - %s", datagram->playerID.c_str());
		// envio Rechazo
		Sleep(1);
		EDatagram* msg = new EDatagram();
		msg->type = ALREADY_EXIST_USER;
		aThreadData->clientI.sendmsg(*msg);
		
		// Cierro socket abiertos del cliente
		closesocket(aThreadData->clientO.getFD());
		closesocket(aThreadData->clientI.getFD());
		srv->jugadoresConectados--;

		delete msg;
		return 1;
	} else {
		// envio LOGIN_OK
		Log::i("Cliente registrado correctamente - %s", datagram->playerID.c_str());
		w->unlock();
		EDatagram* msg = new EDatagram();
		msg->type = LOGIN_OK;
		((threadData*)data)->clientI.sendmsg(*msg);
	}
	
	srv->pList.insert(	std::make_pair<std::string,std::pair<Socket,Socket>>(datagram->playerID,
					std::make_pair(aThreadData->clientO,
					aThreadData->clientI)
					)
				);


	allIn->lock();
	srv->inserPlayerIntotWorld(datagram->playerID);
	canStart->signal();
	allIn->unlock();

	//printf("\nCliente registrado satisfactoriamente en el servidor");
	std::strcpy((char*)playerId,datagram->playerID.c_str() );

	//Envio el nivel YAML al cliente
	Log::i("Envio yaml al cliente");
	ParserYaml* aParser = ParserYaml::getInstance();
	aThreadData->clientI.sendFile(aParser->getLevelFilePath());

	//En este punto el cliente se registro OK, chequeo si estan todos los players, si no espero.

	srv->playerMutexes[playerId].first->lock();
	
	while ( srv->pList.size() != srv->cantJugadores ){
		srv->playerMutexes[playerId].second->wait();
	}
	srv->playerMutexes[playerId].first->unlock();


	//printf("\nElements at model: %d, sending to the client", srv->getGameEngine().getLevel()->getEntities().size() );
	int i = 0;
	std::string pl;
		
	//Notifico de todos los players que tengo en el mundo
	datagram->elements = srv->gameEngine.getLevel()->getAmountOfUsers();
	aThreadData->clientI.sendmsg(*datagram);
	//printf("\nAmount of user into the level: %d",datagram->elements);

	std::map<std::string, GamePlayer*> gpcopy = srv->gameEngine.getLevel()->getPlayers();
	std::map<std::string, GamePlayer*>::iterator itGP = gpcopy.begin(); 
	
	//Por cada player envio sus elementos
	for ( ; itGP != gpcopy.end(); ++itGP ){
		datagram->playerID = itGP->second->playerID;
		datagram->playerState = srv->gameEngine.getLevel()->getPlayerStatus(itGP->second->playerID);
		int el = srv->gameEngine.getLevel()->getWormsFromPlayer(itGP->second->playerID,datagram->play);
		datagram->type = (Messages)srv->gameEngine.getLevel()->getPlayerColor(itGP->second->playerID);
		datagram->elements = el;
		//printf("\nSending %d elements about player: %s at init",el,itGP->second->playerID.c_str());
		aThreadData->clientI.sendmsg(*datagram);
	}
	

	threadData* dataCliente = new threadData();
	dataCliente->srv = srv;
	dataCliente->clientI = aThreadData->clientI;
	dataCliente->clientO = aThreadData->clientO;
	std::strcpy(dataCliente->p,playerId);
	Thread clientThread("Update Client Thread",updateClient,dataCliente);

	Sleep(10);

	//Tell everybody that a new player has arrived!
	srv->notifyUsersAboutPlayer(playerId);


	//Envio la cantidad de agujeros
	srv->sendHoles();


	//Envio turno inicial
	srv->notifyTurnForPlayer( srv->turnMgr.getCurrentPlayerTurn() );

	int activeClient=1;
		try {
		while (activeClient &&  srv->gameEngine.getLevel()->getPlayerStatus(playerId) != DISCONNECTED ) {
			Sleep(10);

			if ( srv->deleted )
				return 0;

			if (! aThreadData->clientO.rcvmsg(*datagram)) {
				//printf("\nDesconectando cliente: %s",playerId );
				//srv->notifyUsersAboutPlayer(playerId);
				srv->disconnect(playerId);
				activeClient=0;
				break;
			}

			switch (datagram->type) {
			case UPDATE:
				m->lock();
				Log::t("Got update, action %s to worm: %d",Util::actionString(datagram->play[0].action).c_str(), datagram->play[0].wormid);
				////printf("\nGot update, action %d to worm: %d",datagram->play[0].action, datagram->play[0].wormid);
				srv->changes.push_back(datagram->play[0]);


				cond->signal();
				m->unlock();

				break;

			case LOGIN:
				m->unlock();
				cond->signal();
				break;

			case LOGOUT:
				srv->disconnect(playerId);
				break;

			}
		}
	} catch (...) {
		srv->disconnect(playerId);
		throw std::current_exception();
	}
	//printf("\nSali intacto");
	return 0;
}

bool Servidor::allConnected() const {
	return !( this->pList.size() < cantJugadores);
	//return false;
}

void Servidor::notifyReject(Socket& client) {
	std::vector<uint8_t> buffer;
	buffer.push_back(uint8_t(Messages::REJECT));
	client.sendmsg(Messages::REJECT, buffer);
}


void Servidor::processPlayersLife(){

	std::map<std::string, GamePlayer*> gpcopy = this->gameEngine.getLevel()->getPlayers();
	std::map<std::string, GamePlayer*>::iterator itGP = gpcopy.begin(); 
	
	//Por cada player proceso su vida
	for ( ; itGP != gpcopy.end(); ++itGP ){
		itGP->second->updateLife();

		// Notifico de la vida de cada player
		this->worldQ.type = LIFE_UPDATE;
		this->worldQ.playerID = itGP->first;
		this->worldQ.play[0].life = itGP->second->getLife();
		this->worldQ.elements = 1;
		this->notifyAll();

		if ( !itGP->second->getLife() ){
			printf("\nRemoving player");
			this->turnMgr.removePlayer(itGP->first);
		}

	}



}


void Servidor::disconnect(Player playerId) {
	
	//No desconecto dos veces
	if ( this->gameEngine.getLevel()->getPlayerStatus(playerId) != DISCONNECTED ){
		Log::i("Releasing player: %s",playerId.c_str());
		//printf("\nReleasing player: %s\n",playerId.c_str());
		this->gameEngine.getLevel()->disconnectPlayer(playerId);
		this->gameEngine.getLevel()->disconnectWormsFromPlayer(playerId);
		closesocket(this->pList[playerId].first.getFD());
		closesocket(this->pList[playerId].second.getFD());
		this->pList.erase(playerId);
		this->jugadoresConectados--;
		this->notifyUsersAboutPlayer(playerId);
		this->playerQueueStat.erase(playerId);

	}

}

void Servidor::notifyUsersAboutPlayer(std::string playerId){

	SDL_SemWait(this->advance);
	this->worldQ.type = PLAYER_UPDATE;
	this->worldQ.playerID = playerId;
	this->worldQ.playerState = this->gameEngine.getLevel()->getPlayerStatus(playerId);
	int el = this->gameEngine.getLevel()->getWormsFromPlayer(playerId,this->worldQ.play);
	this->worldQ.elements = el;
				
	printf("\nNOTIFYING NEWS: Sending type: %d (player_update), about: %s, elements: %d",this->worldQ.type, this->worldQ.playerID.c_str(), this->worldQ.elements);

	
	this->notifyAll();
	SDL_SemPost(this->advance);



}


int Servidor::updateClient(void* data){

	//printf("\n\nUpdate Client Thread running for player: %s\n",static_cast<threadData*>(data)->p);

    threadData* aThreadData = (threadData*)data;

    Servidor* srv = aThreadData->srv;
    std::vector<Playable>* changes =  &srv->changes;

    Condition* netcond =  &srv->canBroadcast;
    Mutex* n =  &srv->netlock;

    char* playerId = aThreadData->p;

    EDatagram datagram;

    while(true){           
		//Sleep(25);
		if ( srv->deleted )
			return 0;

		srv->playerMutexes[playerId].first->lock();
		while ( srv->playerQueues[playerId]->empty() ){
			srv->playerMutexes[playerId].second->wait();
		}
		////printf("Messages at queue: %d", srv->playerQueues[playerId]->size() );

		datagram = srv->playerQueues[playerId]->front() ;
		srv->playerQueues[playerId]->pop();
		srv->playerMutexes[playerId].first->unlock();
		if ( datagram.type == PLAYER_UPDATE && !datagram.playerID.compare(playerId) )
			continue;
		//Log::i("Sending type: %d to %s",datagram.type,playerId);
		////printf("\nENVIO");
		if ( !aThreadData->clientI.sendmsg(datagram) ){
			//printf("Desconectando cliente: %s desde Update Thread",playerId);
			srv->disconnect(playerId);
			return 0;
		}
    }
    return 0;
}

void Servidor::resetWorldQ(){

	std::map<std::string,TransmitStatus> copy = this->playerQueueStat;
	std::map<std::string,TransmitStatus>::iterator it=copy.begin();

	for( ; it!=copy.end(); ++it)
		it->second = TX_WAIT;

}

void Servidor::setWorldQ(){

	std::map<std::string,TransmitStatus> copy = this->playerQueueStat;
	std::map<std::string,TransmitStatus>::iterator it=copy.begin();

	for( ; it!=copy.end(); ++it)
		it->second = TX_READY;

}

bool Servidor::allInWaitingStatus(){

	std::map<std::string,TransmitStatus> copy = this->playerQueueStat;
	std::map<std::string,TransmitStatus>::iterator it=copy.begin();

	for( ; it!=copy.end(); ++it){
		if ( it->second == TX_READY ){
			return false;
		}
	}

	return true;
}

void Servidor::inserPlayerIntotWorld(std::string pl){

	this->playerQueueStat[pl] = TX_WAIT;
	Mutex* m = new Mutex();
	Condition* c = new Condition(*m);
	this->playerMutexes[pl] = std::make_pair(m,c);
	this->playerQueues[pl] = new queue<EDatagram>;
	this->turnMgr.addPlayer(pl);


}


void Servidor::notifyAll(){

	std::map<std::string,std::pair<Mutex*,Condition*>> mutexes = this->playerMutexes;
	std::map<std::string,std::pair<Mutex*,Condition*>>::iterator itm=mutexes.begin();

	for( ; itm!=mutexes.end(); ++itm){
		itm->second.first->lock();
		this->playerQueues[itm->first]->push( this->worldQ );
		itm->second.second->signal();
		itm->second.first->unlock();
	}


}

void Servidor::initialNotify(){

	std::map<std::string,std::pair<Mutex*,Condition*>> mutexes = this->playerMutexes;
	std::map<std::string,std::pair<Mutex*,Condition*>>::iterator itm=mutexes.begin();

	for( ; itm!=mutexes.end(); ++itm){
		itm->second.first->lock();
		itm->second.second->signal();
		itm->second.first->unlock();
	}


}

void Servidor::notifyTurnForPlayer(std::string player){


	std::map<std::string,std::pair<Mutex*,Condition*>> mutexes = this->playerMutexes;
	std::map<std::string,std::pair<Mutex*,Condition*>>::iterator itm=mutexes.begin();

	this->worldQ.type = TURN_CHANGE;
	this->worldQ.elements = 1;
	this->worldQ.play[0].action = YOUR_TURN;
	this->worldQ.playerID = player;

	for( ; itm!=mutexes.end(); ++itm){
		itm->second.first->lock();
		this->playerQueues[itm->first]->push( this->worldQ );
		itm->second.second->signal();
		itm->second.first->unlock();
	}

}

void Servidor::sendHoles(){

	std::vector<Explosion*> copy = this->gameEngine.getMapExplosions();
	std::map<std::string,std::pair<Mutex*,Condition*>> mutexes = this->playerMutexes;
	std::map<std::string,std::pair<Mutex*,Condition*>>::iterator itm=mutexes.begin();
	EDatagram* msg = new EDatagram();
	
	for( ; itm!=mutexes.end(); ++itm){
		//Log::i("\n Enviando holes: %d", copy.size());
		for ( int i=0; i< copy.size() ; i++ ){
			itm->second.first->lock();
			Log::i("\n Enviando hole: %f, %f, %d", copy[i]->x, copy[i]->y, copy[i]->radio);
			msg->type = MAP_UPDATE;
			msg->play[0].weaponid = copy[i]->radio;
			msg->play[0].x = copy[i]->x;
			msg->play[0].y = copy[i]->y;

			this->playerQueues[itm->first]->push( *msg );
			itm->second.second->signal();
			itm->second.first->unlock();
		}
	}

}

void Servidor::shutdown(){
	this->disconnectAll();
	deleted = true;
	Sleep(10);
	closesocket(this->input.getFD());
	closesocket(this->output.getFD());
}


void Servidor::reboot(){

	this->worldQ.type = REINIT_SRV;
	//gameEngine.mapExplosions.clear();
	this->notifyAll();
	Sleep(2);
	deleted = true;
	this->canUpdate.broadcast();
	this->canAddNews.broadcast();
	Sleep(10);
	this->hardDisconnect();
	closesocket(this->input.getFD());
	closesocket(this->output.getFD());
	


}


void Servidor::logoutPlayer(std::string player){

}


void Servidor::notifyTimeUpdate(int time){

	this->worldQ.type = TIME_UPDATE;
	this->worldQ.playerID = this->turnMgr.getCurrentPlayerTurn();
	this->worldQ.elements = time;
	this->notifyAll();

}

void Servidor::disconnectAll(){

	/* Mnado Logout a los clientes*/
	this->worldQ.type = LOGOUT;
	this->notifyAll();

	/* Cierro el socket */
	Players::iterator it = this->pList.begin();
	for ( ; it != this->pList.end(); ++it ){
		disconnect(it->first);
	}
}

void Servidor::hardDisconnect(){

	/* Cierro el socket */
	Players::iterator it = this->pList.begin();
	for ( ; it != this->pList.end(); ++it ){
		closesocket(it->second.first.getFD());
		closesocket(it->second.second.getFD());
	}
}


bool Servidor::doWeHaveAWinner(){
	printf("Do we have a winner?");
	std::map<string, GamePlayer*> copy = this->gameEngine.getLevel()->getPlayers();
	std::map<string, GamePlayer*>::iterator it =  copy.begin();
	int q=0;
	std::vector<string> possibleWinner;

	for ( ; it != copy.end() ; ++it ){
		if ( it->second->getLife() != 0){
			//printf("\nplayer %s life: %d",it->first.c_str(),it->second->getLife());
			q++;
			possibleWinner.push_back(it->first);
		}
	}

	if ( q == 1){
		//printf("\Winner: %s",possibleWinner[0].c_str());
		this->winner = possibleWinner[0];
		return true;
	}

	return false;
}



void Servidor::notifyWinner(){

	this->worldQ.type = GAME_UPDATE;
	this->worldQ.playerID = this->winner;
	this->notifyAll();

}