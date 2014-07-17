#pragma once

#ifndef __CLIENTE_H__
#define __CLIENTE_H__


#include "controlador/GameController.h"
#include "vista/GameViewBuilder.h"
#include <SDL2_framerate.h>
#include "vista\Bootstrap.h"
#include "vista\Activity.h"
#include "vista\GameActivity.h"
#include "vista\WaitActivity.h"
#include "controlador\Contracts\OnMovementListener.h"
#include <SDL2_framerate.h>
#include "../utils/Network/Socket.h"
#include "../utils/Network/Messages.h"
#include "../utils/Network/Thread.h"
#include "../utils/Network/Condition.h"
#include "../utils/Util.h"
#include "../utils/Log.h"
#include "Updater.h"
#include <string>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <queue>


// todo: cambiar TICK_INTERVAL por  DELAY_TIME y recuperar fps del yaml
//const int FPS = 60;
//const int DELAY_TIME = 1000.0f / FPS;

//#define TICK_INTERVAL    15

static Uint32 next_time;
class Cliente;
typedef struct {
	Cliente * cli;
	Socket clientO;
	Socket clientI;
	char p[15];
} threadData;


class Cliente { //: public OnMovementListener{

	private:
		//TODO @future: Going to need a socket conn;
		
		
		/**Inicializador de componentes de la vista*/
		Bootstrap bootstrap;

		/**Activity que manerja la pantalla actual de la vista*/
		Activity* currentActivity;


		/**Activity que maneja la vista del juego*/
		WaitActivity* waitActivity;

		/**Controlador de eventos y estados*/
		GameController cController;
		
		GameDomain domain;

		Updater updater;

		/* Open sockets*/
		bool openConnection();

		/* Estado de loggin en el server*/
		bool loginOk;

		bool gameReady;
		bool gameOver;

		/**Inicia la conexion con el servidor y 
		   inicia la session con el servidor*/
		bool begin();	
	
		/** Main loop de la pantalla*/
		void loop(void);

		void runGame();

		/** Objetos para la conexion con el server */
		Socket input;
		Socket output;
		std::string serverIp;
		int serverPort;
		ServerStatus srvStatus;

		/** Player en este cliente ???????*/
		Player pl;
		
		/** Obejtos para sincronismo entre modelo y red*/
		Mutex m;
		Mutex n;
		Condition somethingToTell;
		Condition somethingToUpdate;

		//size_t revision;
		/** Colas de entrada y salidas*/
		std::vector<Playable> localChanges;
		std::queue<Playable> networkChanges;

		/** Obtiene el estado actual del mundo para iniciar el cliente*/
		void getRemoteWorld();
		
		int sendMsg(Messages type, std::vector<uint8_t> buffer);

	
		/** informa estado de conexion al servidor*/
		void informStateClient();

		/* Data for threading**/
		threadData data;


	public:

		bool deleted;
		bool rebooted;

		void processExplosions(float x, float y, int radio);

		/**Activity que maneja la vista del juego*/
		GameActivity* gameActivity;

		Mutex domainMx;
		Condition updateDomain;
		
		void disconnectClient();

		SDL_sem* advance;
		std::queue<EDatagram> clientQueue;

		Cliente(std::string playerID, std::string ip, int port);
		
		virtual ~Cliente(void);

		bool isLoginOk() {return this->loginOk;}

		void run();

		void destroyWorld();

		Activity* getCurrentActivity() {return this->currentActivity;}

		
		//Listen changes in the network
		static int netListener(void* data);

		//notify over the network for a local change on the client
		static int notifyLocalUpdates(void* data);

		//Apply the changes that we receive on listen state
		static int applyNetworkChanges(void* data);

		void lockLocalMutex();

		void unlockLocalMutex();

		void lockNetworkMutex();

		void unlockNetworkMutex();

		void addLocalChange(Playable p);

		bool updateModel(Playable p);

		void signalLocalChange();

		void signalNetworkChange();

		void reinitGame();

		void resetModel();

		void showAlert();

		void showWaitting();

		void showWinner();

		void showGameOver();

		GameElement* getElementFromPlayable(std::string playerID, Playable p);

};


#endif