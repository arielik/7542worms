#include "./SystemManager.h"
#include "./utils/Log.h"
#include <string>
#include <iostream>

SystemManager::SystemManager(void){
	this->runningMode = CLIENT;
	this->aServer = NULL;
	this->aClient = NULL;
}

SystemManager::~SystemManager(void){
	if( this->aServer != NULL){
		this->aServer->destroyWorld();
		delete this->aServer;
		this->aServer = NULL;
	}

	if( this->aClient != NULL){
		this->aClient->destroyWorld();
		delete this->aClient;
		this->aClient = NULL;
	}
}

void SystemManager::run(){

	this->parseCommands();

	this->aServer = new Servidor();
	if( this->aServer->run() == false ){
			//std::cout << "error" << std::endl;
			Log::e("Error al correr el juego en modo Servidor");
		}
	
	this->aClient = new Cliente(this->aServer);
	if( this->aClient->run() == false ){
		//std::cout << "error" << std::endl;
		Log::e("Error al correr el juego en modo Cliente");
	}	
	return void();
}

void SystemManager::parseCommands(void){

	// TODO @future - Detects if it's going to run as server or client mode
	return void();
}
