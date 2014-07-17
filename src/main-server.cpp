#include <iostream>
#include "./utils/Log.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "utils/ParserYaml.h"
#include "utils/PersistYaml.h"
#include <cstdio>
#include "Servidor\Servidor.h"


#define SERVER_PORT 10025

using namespace std;

std::string path;
Servidor* srvPointer;

void selectYaml(){
	std::cout << "Ingrese el directorio del archivo YAML\n";
	std::string path;

	getline (std::cin, path);
	if (path.empty() ) path = DEFAULT_YAML_SERVER;
	std::cout << "YAML:" << path << "\n";

}
void initGame(){
	if (path.empty() ) path = DEFAULT_YAML_SERVER;
	ParserYaml* aParser = ParserYaml::getInstance(path);
	srvPointer = new Servidor( SERVER_PORT , Util::string2int(aParser->getMetaMaxPlay()) );

}
void stopGame(){
	std::cout << "JUEGO DETENIDO\n";
	srvPointer->shutdown();

}


void resetGame(){
	std::cout << "JUEGO REINICIADO\n";
	srvPointer->reboot();
	
	//delete srvPointer;
	//srvPointer->shutdown();
	std::cout << "\nINICIANDO NUEVO JUEGO\n";
	initGame();
}


void printOptions(){
	char option;
	std::cout << "<y> Seleccionar YAML\n";
	std::cout << "<i> Seleccionar INICIAR JUEGO\n";
	std::cout << "<s> Seleccionar DETENER JUEGO\n";
	std::cout << "<r> Seleccionar REINICIAR JUEGO\n";
	
	std::cin >> option;
	switch (option){
		case 'y': selectYaml();break;
		case 'i': initGame();break; 
		case 's': stopGame();break; 
		case 'r': resetGame();break;
		default: std::cout << "Opcion Incorrecta\n";
	}
	
}



int main(int argc, char* argv[]) {
	
	Log::logSide = LOG_SERVER;
	
	while(true){
		Sleep(1);
		printOptions();
	}
	return 0;

}



