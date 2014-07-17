#pragma once

#include <fstream>
#include <list>
#include <yaml-cpp/yaml.h>
#include <vector>


class PersistYaml{
public:
	//YAML::Emitter out;
	std::string fileOut;

private:
	//std::string fileOut;
	//YAML::Emitter out;
	static PersistYaml* pInstance;//puntero a la instacia para hacer el singleton
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
		std::string maxPlay;
		std::string MaxPj;
	};

	stElemento elem;
	stEscenario escenario;
	stArma arma;
	stMeta meta;

	void destroyLevel();


public:
	PersistYaml();
	virtual ~PersistYaml();
	static PersistYaml* getInstance();


	void setMetaEps(std::string);
	void setMetaSca(std::string);
	void setMetaMaxPlay(std::string);
	void setMetaMaxPj(std::string);

	void setEscenarioFps(std::string);
	void setEscenarioAltoU(std::string);
	void setEscenarioAnchoU(std::string);
	void setEscenarioAltoP(std::string);
	void setEscenarioAnchoP(std::string);
	void setEscenarioNivelAgua(std::string);
	void setEscenarioColorAgua(std::string);
	void setEscenarioImTierra(std::string);
	void setEscenarioColorTierra(std::string);
	void setEscenarioImCielo(std::string);

	
	
	
	void setElemTipo(std::string);
	void setElemX(std::string);
	void setElemY(std::string);
	void setElemRot(std::string);
	void setElemAlto(std::string);
	void setElemAncho(std::string);
	void setElemMasa(std::string);
	void setElemEstatico(std::string);
	void setElemColor(std::string);

	void setEscenarioElem(stElemento);



	void setArmaTipo(std::string);
	void setArmaHab(std::string);
	void setEscenarioArm(stArma);


	void setElem(std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
	/*rec: tipo,id,x,y,rot,masa,alto,ancho,estatico,color*/
	void setRec(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string alto,std::string ancho,std::string estatico,std::string color);
	/*tri: tipo,id,x,y,rot,masa,estatico,color,escala	*/
	void setTri(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string estatico,std::string color,std::string escala);
	/*pent: tipo,id,x,y,rot,masa,escala,estatico,color*/
	void setPent(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string escala,std::string estatico,std::string color);
	/*circ:	tipo,id,x,y,rot,masa,escala,estatico,color,radio*/
	void setCirc(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string escala,std::string estatico,std::string color,std::string radio);

	void setArma(std::string,std::string);
	void setBazooka(std::string);
	void setGrenade(std::string);
	void setDynamite(std::string);
	void setDonkey(std::string);
	void setAirStrike(std::string);
	void setHoly(std::string);
	void setSheep(std::string);
	void setSuicide(std::string);
	void setKick(std::string);
	void setParrot(std::string);
	void setAutomissil(std::string);

	void setHexa(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string escala,std::string estatico,std::string color);

	void escribirYaml(std::string);

};