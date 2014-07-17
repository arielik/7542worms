#pragma once


#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <sstream>
#include "../utils/Constantes/Constantes.h"
#include "./Log.h"
#include "PersistYaml.h"

//#include <boost/lexical_cast.hpp>
//#include <boost/math/special_functions/round.hpp>


enum TipoDato{
	UnsInt,
	SigInt,
	UnsFloat,
	SigFloat,
	Hexa,
	HexaSdl,
	Estatico,
	TipoValido,
	Str,
	Imagen,
	ArmTipoValido,
	ArmHabilitado
};

class ParserYaml{
private:
	
	static ParserYaml* pInstance;//puntero a la instacia para hacer el singleton
	static void DestroySingleton();

	struct stElemento{
		std::string tipo;
		std::string id;
		std::string escala;
		std::string x;
		std::string y;
		std::string alto;
		std::string ancho;
		std::string color;
		std::string estatico;
		std::string masa;
		std::string rot;
		std::string radio;
	};

	struct stArma{
		std::string tipo;
		std::string habilitado;
	};
	struct stEscenario{
		std::string fps;
		std::string alto;
		std::string ancho;
		std::string agua;
		std::string colorAgua;
		std::string anchoP;
		std::string altoP;
		std::string tierra;
		std::string colorTierra;
		std::string cielo;
		std::vector <stElemento> elem;
		std::vector <stArma> arma;	
	};
	struct stMeta{
		std::string epsilon ;
		std::string scale ;
		std::string timestep;
		std::string serverPort;
		std::string connTimeOut;
		std::string maxPlay;
		std::string MaxPj;

	};

	


	/*
	struct dtElemento{
		std::string nombre;
		std::string imagen;
	};*/


	struct stTodo{
		//std::vector <dtElemento> dataE;//contiene la data de un elemento
		stEscenario escenario;
		stMeta meta;
	};
private:
	
	stTodo todo;
	std::string yamlNodeToString(const YAML::Node&);
	void cargarElementos(const YAML::Node&,std::vector <stElemento>&);
	void cargarArmas(const YAML::Node&,std::vector <stArma>&);
//	void cargarDataElementos(const YAML::Node&,std::vector <dtElemento>&);
	void cargarNiveles(const YAML::Node&,stEscenario&);
	void cargarMeta(const YAML::Node&,stMeta&);
		
//	bool existeElemen(std::string,std::vector <dtElemento>&);

	void startWithDefaultLevel();
	void startWithDefaultElem(std::vector <stElemento>&);
	
	bool esUnsFloat(std::string);
	bool esSigFloat(std::string);
	bool esHexa(std::string);
	bool esTipoValido(std::string);
	bool validarGuardar(std::string,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool);
	void loggearErrGuardar(std::string,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,bool,YAML::Mark);
	bool estaticoValido(std::string);
	bool esHexaSdl(std::string);
	bool esUnsInt(std::string str);
	bool esImagen(std::string str);

	bool esArmaTipoValido(std::string str);
	bool esArmaHabilitadoValido(std::string str);


	void label(std::string &campo,bool &flag,TipoDato tipo,std::string key,const YAML::Node& node,int line,int col);


	bool isDefault;

	std::string confFilePath;
	std::string levelFilePath;

	void initializeElementMap();
	std::map< std::string, std::pair<int,std::string> > elementMap;

	ParserYaml(std::string config, std::string level, bool aux);
	ParserYaml(std::string config, std::string level);
	std::string validaAngulo(std::string ang);
	std::string validaPosicion(std::string ang);
	std::string validaPantalla(std::string tam);


public:
	
	
	std::string getFilePath();
	int getElementPosition(std::string name);
	std::string getImagePath(std::string name);
	std::string getElementType(int id);
	std::string getLevelFilePath();

	ParserYaml();
	virtual ~ParserYaml();
	static ParserYaml* getInstance();
	static ParserYaml* getInstance(std::string file);
	//void cargarConfYaml(std::string);
	void cargarNivelYaml(std::string);
	//std::string getImElem(const std::vector <dtElemento>,std::string);
	bool getDefault();


	//++++++geters+++++++++
	
	//dataElem
	/*int getCantDataElem();
	std::string getDataElemNombre(int);//devuelve el nombre de el dataElem de la posicion que se le pase
	std::string getDataElemImagen(int);*/
	
	std::string getMetaEps();
	std::string getMetaSca();
	std::string getMetaMaxPlay();
	std::string getMetaMaxPj();

	
	//para trabajar con un solo escenario
	std::string getEscenarioFps();
	std::string getEscenarioAltoU();
	std::string getEscenarioAnchoU();
	std::string getEscenarioAgua();
	std::string getEscenarioColorAgua();
	std::string getEscenarioTierra();
	std::string getEscenarioColorTierra();
	std::string getEscenarioAnchoP();
	std::string getEscenarioAltoP();
	std::string getEscenarioCielo();

	//elemento en escenario
		//el primer int que siempre se pasa es para el nivel especificado de la lista de niveles
	int getCantElem();
	std::string getElemTipo(int);
	std::string getElemId(int);
	std::string getElemEscala(int);
	std::string getElemX(int);
	std::string getElemY(int);
	std::string getElemAncho(int);
	std::string getElemAlto(int);
	std::string getElemColor(int);
	std::string getElemMasa(int);
	std::string getElemEstatico(int);
	std::string getElemRot(int);
	std::string getElemRadio(int);


	//arma en escenario
	int getCantArm();
	std::string getArmaTipo(int);
	std::string getArmaHab(int);



	std::string getColorById(std::string id);



	/*para modificar el terreno si sale algo mal*/
	void setTerrain(std::string terrain);
	

};
