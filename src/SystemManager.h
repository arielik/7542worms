#pragma once

#include "./Servidor/Servidor.h"
#include "./Cliente/Cliente.h"

enum mode{
	SERVER=0,
	CLIENT=1
};

class SystemManager{

	private:
		mode runningMode;
		Servidor* aServer;
		Cliente* aClient;

		void parseCommands(void);

	public:
		SystemManager(void);
		~SystemManager(void);
		void run();

};
