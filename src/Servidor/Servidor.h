#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>
#include <queue>

#include "Socket.h"
#include "Thread.h"
#include "Condition.h"
#include ".\modelo\TurnManager.h"
#include ".\modelo\GameEngine.h"
#include "../utils/ParserYaml.h"



class Servidor;

typedef struct{
	Servidor* srv;
	Socket clientO;
	Socket clientI;
	char p[15];
} threadData;

class Servidor{

	private:
		GameEngine gameEngine;
		//TODO @future Going to run over a socket;

		bool begin();
		void loop();

		Socket input;
		Socket output;
		size_t cantJugadores;
		size_t jugadoresConectados;

		

		// Lista de clientes conectados y sus file descriptors asociados
		typedef std::map<std::string, std::pair<Socket,Socket>> Players;
		Players pList;

		//This really is client side requested changes/actions
		std::vector<Playable> changes;

		// This is all the changes after apply all client side actions, THIS
		// MUST be propagated to all the clients.
		std::vector<Playable> worldChanges;	

		std::map<int,Playable> worldModifications;

		std::map<std::string,TransmitStatus> playerQueueStat;



		void sendHeartBeat(Player playerId, Messages type);
	
		void broadcastMsg(Playable change);
		void enviarMensaje(Player playerId, std::vector<uint8_t> buffer);
		void wait4Updates(Player playerId);
		void disconnect(std::string playerId);

		bool updateModel(Playable p);

		/* Data for threading**/
		threadData data;

	public:

		~Servidor();

		TurnManager turnMgr;
		
		SDL_sem* advance;
		std::string winner;

		bool deleted;
		bool doWeHaveAWinner();
		std::string getWinner(){ return this->winner; }

		void sendHoles();
		void shutdown();
		void reboot();

		void notifyTimeUpdate(int time);

		void logoutPlayer(std::string player);
		void disconnectAll();
		void hardDisconnect();

		//TurnManager turnMgr;

		bool startNewTurn;
		void notifyTurnForPlayer(std::string player);
		void notifyWinner();

		//Mutex per player - basado en consume/producer model
		std::map<std::string,std::pair<Mutex*,Condition*>> playerMutexes;
		std::map<std::string,std::queue<EDatagram>* > playerQueues;

		TransmitStatus getWorldQStatus(std::string pl){ return this->playerQueueStat[pl]; }
		void setWorldQStatus(std::string pl, TransmitStatus tx) { this->playerQueueStat[pl] = tx; }
		
		void inserPlayerIntotWorld(std::string pl);
		void resetWorldQ();
		void setWorldQ();

		Servidor(int nroPuerto, size_t cantJugadores);

		EDatagram worldQ;

		void notifyUsersAboutPlayer(std::string playerID);

		bool allInWaitingStatus();
		bool allConnected() const;
		void esperarUserDelta ();
	
		Mutex lock;
		Condition canUpdate;
		
		Mutex netlock;
		Condition canBroadcast;

		Mutex worldlock;
		Condition canCreate;

		Mutex playerslock;
		Condition canAddNews;

		void processPlayersLife();

		void reinit();

		void waitConnections();
		void notifyAll();
		void initialNotify();
	
		static int updating(void* data);
		static int initClient(void* data);
		static void notifyReject(Socket& fdCli);
		static int wait4Connections(void* data);
		static int stepOver(void* data);
		static int updateClient(void* data);

		int somethingChange();

		bool run(void);
		void destroyWorld();
		GameEngine getGameEngine();
		GameLevel* getLevel();

};



#endif /* SERVIDOR_H_ */