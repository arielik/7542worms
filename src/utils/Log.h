#pragma once
#ifndef __LOG_H_1__
#define __LOG_H_1__

/**
	TRACE 0
	DEBUG 1
	INFO  2
	ERROR 3
*/
#define LOG_LEVEL 1
#define LOG_CONFIG_FILE "./config/logForTaller.properties"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdarg>
#include <cstdio>
#include <map>
//#include "Constantes\Constantes.h"
#include "../utils/Util.h"

enum LogSide{
	LOG_SERVER,
	LOG_CLIENT,
};


enum TipoLog{
	TRACE=0,
	DEBUG,
	INFO,
	ERRORLOG
};

enum LugarLog{
	NO_DEFINIDO,
	PARSER,
	BOOT,
	VIEW_BUILDER,
	DETECTOR,
	GAME_CONTROLLER,
	HANDLE_CONTOUR,
	VIEW,
	SOUND,
	GAME_ACTIVITY
};

class Log
{
private:

	std::ofstream file;
	
	std::map<std::string, std::string> properties;

	void retriveConfigFile();

public:
	Log(void);
	virtual ~Log(void);
	
	static LogSide logSide;

	static std::string userId;

	static Log & Instance(){
			static Log logger;
			return logger;
	}



	/**
	* Logea con TRACE
	* 
	* @param msj String con el mensaje
	*/
	static void t(std::string msj);

	/**
	* Logea con DEBUG
	* 
	* @param msj String con el mensaje
	*/
	static void d(std::string msj);

	/**
	* Logea con INFO
	* 
	* @param msj String con el mensaje
	*/
	static void i(std::string msj);

	/**
	* Logea con ERROR
	* 
	* @param msj String con el mensaje
	*/
	static void e(std::string msj);

	
	/**
	* Logea con TRACE
	* 
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void t(char* form, ...);

	/**
	* Logea con DEBUG
	* 
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void d(char* form, ...);

	/**
	* Logea con INFO
	* 
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void i(char* form, ...);
	
	/**
	* Logea con ERROR
	* 
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void e(char* form, ...);

	/**
	* Logea con TRACE
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void t(LugarLog lugarLog,char* form, ...);

	/**
	* Logea con DEBUG
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void d(LugarLog lugarLog,char* form, ...);

	/**
	* Logea con INFO
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void i(LugarLog lugarLog,char* form, ...);

	/**
	* Logea con ERROR
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param form Cadena con mascara para imprimir mensaje (Idem fprint)
	* @param ... Argumentos (Idem fprint)
	*/
	static void e(LugarLog lugarLog,char* form, ...);


	/**
	* Logea con TRACE
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param msj Mensaje a logguear
	*/
	static void t(LugarLog lugarLog, std::string msj);

	/**
	* Logea con DEBUG
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param msj Mensaje a logguear
	*/
	static void d(LugarLog lugarLog, std::string msj);

	/**
	* Logea con INFO
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param msj Mensaje a logguear
	*/
	static void i(LugarLog lugarLog, std::string msj);

	/**
	* Logea con ERROR
	* 
	* @param LugarLog lugar donde se utiliza el logger
	* @param msj Mensaje a logguear
	*/
	static void e(LugarLog lugarLog, std::string msj);




private:

	std::string  Log::stringConFormato(char* form,va_list argumentos);

	/**
	* Escribe en el archivo de logs
	*
	* @param TipoLog Nivel del log utilizado
	* @param LugarLog Lugar donde se utliza el logger
	* @param msj Mensaje a logguear
	*/
	void log(TipoLog tipoLog,LugarLog lugarLog,std::string msj);

	/**
	* Devuelve el literal del tipo de log utilizado
	*
	* @param TipoLog Nivel del log utilizado
	* @return String El literal literal del log utilizado
	*/
	static std::string logearTipoLog(TipoLog tipoLog);

	
	/**
	* Devuelve el literal del lugar donde se indico el logueo
	*
	* @param LugarLog Lugar donde se utliza el logger
	* @return String El literal del lugar
	*/
	static std::string logearLugarLog(LugarLog lugarLog);


	/**
	* Devuelve el tiempo actual
	*
	* @return String El tiempo Actual
	*/
	const static std::string tiempoActual();
};
#endif /**__LOG_H_1__*/