#include "PersistYaml.h"
#include <vector>
#include <iostream>

PersistYaml::PersistYaml(){}
PersistYaml::~PersistYaml(){}

void PersistYaml::DestroySingleton(){
	if(pInstance != NULL) delete pInstance;
}

PersistYaml* PersistYaml::getInstance(){
	if(pInstance == NULL){
		pInstance = new PersistYaml();
		atexit(&DestroySingleton);
	}
	return pInstance;
}



void PersistYaml::setMetaEps(std::string eps){
	this->meta.epsilon = eps;
}

void PersistYaml::setMetaSca(std::string sca){
	this->meta.scale = sca;
}

void PersistYaml::setMetaMaxPlay(std::string play){
	this->meta.maxPlay = play;
}
void PersistYaml::setMetaMaxPj(std::string pj){
	this->meta.MaxPj = pj;
}

void PersistYaml::setEscenarioFps(std::string fps){
	this->escenario.fps = fps;
}

void PersistYaml::setEscenarioAnchoU(std::string ancho){
	this->escenario.ancho = ancho;
}

void PersistYaml::setEscenarioAltoU(std::string alto){
	this->escenario.alto = alto;
}

void PersistYaml::setEscenarioAltoP(std::string altoP){
	this->escenario.altoP = altoP;
}
void PersistYaml::setEscenarioAnchoP(std::string anchoP){
	this->escenario.anchoP = anchoP;
}
void PersistYaml::setEscenarioNivelAgua(std::string agua){
	this->escenario.agua = agua;
}

void PersistYaml::setEscenarioColorAgua(std::string agua){
	this->escenario.colorAgua = agua;
}


void PersistYaml::setEscenarioImTierra(std::string tierra){
	this->escenario.tierra = tierra;
}

void PersistYaml::setEscenarioColorTierra(std::string tierra){
	this->escenario.colorTierra = tierra;
}

void PersistYaml::setEscenarioImCielo(std::string cielo){
	this->escenario.cielo = cielo;
}



void PersistYaml::setElemTipo(std::string tipo){
	this->elem.tipo = tipo;
}

void PersistYaml::setElemX(std::string x){
	this->elem.x = x;
}

void PersistYaml::setElemY(std::string y){
	this->elem.y = y;
}

void PersistYaml::setElemRot(std::string rot){
	this->elem.rot = rot;
}

void PersistYaml::setElemAlto(std::string alto){
	this->elem.alto = alto;
}
void PersistYaml::setElemAncho(std::string ancho){
	this->elem.ancho = ancho;
}
void PersistYaml::setElemColor(std::string color){
	this->elem.color = color;
}
void PersistYaml::setElemEstatico(std::string estatico){
	this->elem.estatico = estatico;
}
void PersistYaml::setElemMasa(std::string masa){
	this->elem.masa = masa;
}

void PersistYaml::setEscenarioElem(stElemento elem){
	this->escenario.elem.push_back(elem);
}

void PersistYaml::setArmaTipo(std::string tipo){
	this->arma.tipo = tipo;
}

void PersistYaml::setArmaHab(std::string hab){
	this->arma.habilitado = hab;
}

void PersistYaml::setEscenarioArm(stArma arma){
	this->escenario.arma.push_back(arma);
}


void PersistYaml::setElem(std::string tipo,std::string x,std::string y,std::string alto,std::string ancho,std::string color, std::string estatico,std::string rot,std::string masa){
	stElemento elem;
	elem.tipo = tipo;
	elem.x = x;
	elem.y = y;
	elem.rot = rot;
	elem.masa = masa;
	elem.alto = alto;
	elem.ancho = ancho;
	elem.color = color;
	elem.estatico = estatico;

	this->escenario.elem.push_back(elem);
}

	/*rec: tipo,id,x,y,rot,masa,alto,ancho,estatico,color*/
void PersistYaml::setRec(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string alto,std::string ancho,std::string estatico,std::string color){
	stElemento elem;
	elem.tipo = "rec";
	elem.id = id;
	elem.x = x;
	elem.y = y;
	elem.rot = rot;
	elem.masa = masa;
	elem.alto = alto;
	elem.ancho = ancho;
	elem.color = color;
	elem.estatico = estatico;

	this->escenario.elem.push_back(elem);
}
	/*tri: tipo,id,x,y,rot,masa,estatico,color,escala	*/
void PersistYaml::setTri(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string estatico,std::string color,std::string escala){
	stElemento elem;
	elem.tipo = "tri";
	elem.id = id;
	elem.x = x;
	elem.y = y;
	elem.rot = rot;
	elem.masa = masa;
	elem.color = color;
	elem.escala = escala;
	elem.estatico = estatico;

	this->escenario.elem.push_back(elem);
}
	/*pent: tipo,id,x,y,rot,masa,escala,estatico,color*/
void PersistYaml::setPent(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string escala,std::string estatico,std::string color){
	stElemento elem;
	elem.tipo = "pent";
	elem.id = id;
	elem.x = x;
	elem.y = y;
	elem.rot = rot;
	elem.masa = masa;
	elem.escala = escala;
	elem.color = color;
	elem.estatico = estatico;

	this->escenario.elem.push_back(elem);
}


void PersistYaml::setHexa(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string escala,std::string estatico,std::string color){
	stElemento elem;
	elem.tipo = "hexa";
	elem.id = id;
	elem.x = x;
	elem.y = y;
	elem.rot = rot;
	elem.masa = masa;
	elem.escala = escala;
	elem.color = color;
	elem.estatico = estatico;

	this->escenario.elem.push_back(elem);
}
	/*circ:	tipo,id,x,y,rot,masa,escala,estatico,color,radio*/
void PersistYaml::setCirc(std::string id,std::string x,std::string y,std::string rot,std::string masa,std::string escala,std::string estatico,std::string color,std::string radio){
	stElemento elem;
	elem.tipo = "circ";
	elem.id = id;
	elem.x = x;
	elem.y = y;
	elem.rot = rot;
	elem.masa = masa;
	elem.escala = escala;
	elem.color = color;
	elem.estatico = estatico;
	elem.radio = radio;

	this->escenario.elem.push_back(elem);
}


void PersistYaml::setArma(std::string tipo,std::string hab){
	this->setArmaTipo(tipo);
	this->setArmaHab(hab);
	this->setEscenarioArm(this->arma);
}


void PersistYaml::setBazooka(std::string hab){
	this->setArma("Bazooka",hab);
}
void PersistYaml::setGrenade(std::string hab){
	this->setArma("Grenade",hab);
}
void PersistYaml::setDynamite(std::string hab){
	this->setArma("Dynamite",hab);
}
void PersistYaml::setDonkey(std::string hab){
	this->setArma("Donkey",hab);
}
void PersistYaml::setAirStrike(std::string hab){
	this->setArma("AirStrike",hab);
}

void PersistYaml::setHoly(std::string hab){
	this->setArma("Holy",hab);
}
void PersistYaml::setSheep(std::string hab){
	this->setArma("Sheep",hab);
}
void PersistYaml::setSuicide(std::string hab){
	this->setArma("Suicide",hab);
}
void PersistYaml::setKick(std::string hab){
	this->setArma("Kick",hab);
}
void PersistYaml::setParrot(std::string hab){
	this->setArma("Parrot",hab);
}
void PersistYaml::setAutomissil(std::string hab){
	this->setArma("Automissil",hab);
}


void PersistYaml::escribirYaml(std::string fileOut){
	int i;
	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "metadata";
	out << YAML::Value;
	out << YAML::BeginMap;
	out << YAML::Key << "epsilon";
	out << YAML::Value << this->meta.epsilon;
	out << YAML::Key << "scale";
	out << YAML::Value << this->meta.scale;
	out << YAML::Key << "max_player";
	out << YAML::Value << this->meta.maxPlay;
	out << YAML::Key << "max_per_team";
	out << YAML::Value << this->meta.MaxPj;
	out << YAML::EndMap;


	out << YAML::Key << "escenario";
	out << YAML::Value; //<< YAML::BeginSeq;
	out << YAML::BeginMap;
	out << YAML::Key << "fps";
	out << YAML::Value << this->escenario.fps;
	out << YAML::Key << "ancho-un";
	out << YAML::Value << this->escenario.ancho;
	out << YAML::Key << "alto-un";
	out << YAML::Value << this->escenario.alto;
	out << YAML::Key << "ancho-px";
	out << YAML::Value << this->escenario.anchoP;
	out << YAML::Key << "alto-px";
	out << YAML::Value << this->escenario.altoP;
	out << YAML::Key << "nivel_agua";
	out << YAML::Value << this->escenario.agua;
	out << YAML::Key << "imagen_tierra";
	out << YAML::Value << this->escenario.tierra;
	out << YAML::Key << "imagen_cielo";
	out << YAML::Value << this->escenario.cielo;
	out << YAML::Key << "color_tierra";
	out << YAML::Value << this->escenario.colorTierra;
	out << YAML::Key << "color_agua";
	out << YAML::Value << this->escenario.colorAgua;
	out << YAML::Key << "objetos";
	out << YAML::Value << YAML::BeginSeq;
	for(unsigned i=0;i<this->escenario.elem.size();i++){
		stElemento elem = this->escenario.elem[i];
		out << YAML::BeginMap;
		out << YAML::Key << "tipo";
		out << YAML::Value << elem.tipo;
		out << YAML::Key << "id";
		out << YAML::Value << elem.id;
		out << YAML::Key << "x";
		out << YAML::Value << elem.x;
		out << YAML::Key << "y";
		out << YAML::Value << elem.y;
		if (elem.tipo.compare("rec")==0){
			out << YAML::Key << "alto";
			out << YAML::Value << elem.alto;
			out << YAML::Key << "ancho";
			out << YAML::Value << elem.ancho;
		}
		out << YAML::Key << "color";
		out << YAML::Value << elem.color;
		out << YAML::Key << "estatico";
		out << YAML::Value << elem.estatico;
		out << YAML::Key << "rot";
		out << YAML::Value << elem.rot;
		out << YAML::Key << "masa";
		out << YAML::Value << elem.masa;
		if (elem.tipo.compare("rec")!=0){
			out << YAML::Key << "escala";
			out << YAML::Value << elem.escala;
		}
		if (elem.tipo.compare("circ")==0){
			out << YAML::Key << "radio";
			out << YAML::Value << elem.radio;
		}
		out << YAML::EndMap;		
	}
	//out << YAML::EndMap;
	out << YAML::EndSeq;
	

	out << YAML::Key << "armas";
	out << YAML::Value << YAML::BeginSeq;
	for(unsigned i=0;i<this->escenario.arma.size();i++){
		stArma arma = this->escenario.arma[i];
		out << YAML::BeginMap;
		out << YAML::Key << "tipo";
		out << YAML::Value << arma.tipo;
		out << YAML::Key << "habilitado";
		out << YAML::Value << arma.habilitado;
		out << YAML::EndMap;		
	}


	out << YAML::EndMap;
	out << YAML::EndSeq;



	//out << YAML::EndSeq;
	
	/* escribe el archivo*/
	std::ofstream file(fileOut.c_str());
	out << YAML::EndMap;
	file << out.c_str()<<std::endl;
	file.close();

	//vacia los maps internos - TODO @Optimizacion: guardar solo lo que cambia
	this->destroyLevel();
}

void PersistYaml::destroyLevel(){
	this->escenario.elem.clear();
	this->escenario.arma.clear();
}


PersistYaml* PersistYaml::pInstance = NULL;