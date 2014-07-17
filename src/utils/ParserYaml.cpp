#include "ParserYaml.h"
#include <vector>
#include <iostream>


#define DEFAULT_EPSILON "1.5"
#define DEFAULT_SCALE "100"
#define DEFAULT_FSP "60"
#define DEFAULT_ALTOU "600"
#define DEFAULT_ANCHOU "600"
#define DEFAULT_ALTOP "400"
#define DEFAULT_ANCHOP "400"
#define DEFAULT_NIVEL_AGUA "50"
#define DEFAULT_COLOR_AGUA "#0000FF99"
#define DEFAULT_IM_TIERRA "res/images/terrain1.png"
#define DEFAULT_COLOR_TIERRA "#BC794FFF"
#define DEFAULT_IM_CIELO "res/images/cielo1.png"
#define DEFAULT_MAX_PLAY "4"
#define DEFAULT_MAX_PJ_PLAY "5"

ParserYaml::ParserYaml(){}

ParserYaml::ParserYaml(std::string config, std::string level, bool aux){
	this->confFilePath = config;
	this->levelFilePath = level;
	//this->cargarConfYaml(this->confFilePath);
	this->isDefault = false;	
	this->cargarNivelYaml(this->levelFilePath);
}

ParserYaml::ParserYaml(std::string config,std::string level){
	this->confFilePath = config;
	this->levelFilePath = level;
	//this->cargarConfYaml(this->confFilePath);
	this->isDefault = true;
	this->startWithDefaultLevel();
}


 std::string ParserYaml::getLevelFilePath(){	
	return this->levelFilePath;	
}


ParserYaml::~ParserYaml(){}

std::string ParserYaml::getFilePath(){
	return this->levelFilePath;
}

void ParserYaml::startWithDefaultElem(std::vector <stElemento>& vElem){
	stElemento elem;

	/* Para agregar uno o varios objetos default rapido copiar y pegar los parametros
	IMPORTANTE: recordar que no todos los objetos reciben los mismos parametros
	rec:
		tipo,id,x,y,rot,masa,alto,ancho,estatico,color
	tri:
		tipo,id,x,y,rot,masa,estatico,color	
	pent:
		tipo,id,x,y,rot,masa,escala,estatico,color
	circ:
		tipo,id,x,y,rot,masa,escala,estatico,color,radio

	elem.tipo = "";
	elem.id = "";
	elem.escala = "";
	elem.x = "";
	elem.y = "";
	elem.alto = "";
	elem.ancho = "";
	elem.color = "";
	elem.estatico = "";
	elem.masa = "";
	elem.rot = "";
	elem.radio = "";
	vElem.push_back(elem);
	*/
	

}


void ParserYaml::label(std::string &campo,bool &flag,TipoDato tipo,std::string key,const YAML::Node& node,int line,int col){
	campo = this->yamlNodeToString(node);
	
	switch (tipo)
	{
		case UnsInt:
				if (this->esUnsInt(campo)) flag = true;
			break;
		case UnsFloat:
			if (this->esUnsFloat(campo)) flag = true;
			break;
		case SigFloat:
			if (this->esSigFloat(campo)) flag = true;
			break;
		case Hexa:
			if (this->esHexa(campo)) flag = true;
			break;
		case HexaSdl:
			if (this->esHexaSdl(campo)) flag = true;
			break;
		case Estatico:
			if (this->estaticoValido(campo)) flag = true;
			break;
		case Imagen:
			if (this->esImagen(campo)) flag = true;
			break;
		case TipoValido:
			if (this->esTipoValido(campo)) flag = true;
			break;
		case ArmTipoValido:
			if (this->esArmaTipoValido(campo)) flag = true;
			break;
		case ArmHabilitado:
			if (this->esArmaHabilitadoValido(campo)) flag = true;
			break;
		case Str:
			flag = true;
			break;
	}
	if (!flag)Log::e(PARSER,"Valor incorrecto para atributo %s en linea: %d, columna: %d",key.c_str(),(line + 1),(col + 1));


}

void ParserYaml::startWithDefaultLevel(){
	
	std::ifstream fin(this->levelFilePath.c_str());
	if( fin.good() == true) this->levelFilePath = "default_level.yaml";



	PersistYaml* aPersist=PersistYaml::getInstance();
	aPersist->setMetaEps(DEFAULT_EPSILON);
	aPersist->setMetaSca(DEFAULT_SCALE);	
	aPersist->setMetaMaxPlay(DEFAULT_MAX_PLAY);	
	aPersist->setMetaMaxPj(DEFAULT_MAX_PJ_PLAY);	
	aPersist->setEscenarioFps(DEFAULT_FSP);
	aPersist->setEscenarioAltoU(DEFAULT_ALTOU);
	aPersist->setEscenarioAnchoU(DEFAULT_ANCHOU);
	aPersist->setEscenarioAltoP(DEFAULT_ALTOP);
	aPersist->setEscenarioAnchoP(DEFAULT_ANCHOP);
	aPersist->setEscenarioNivelAgua(DEFAULT_NIVEL_AGUA);
	aPersist->setEscenarioColorAgua(DEFAULT_COLOR_AGUA);
	aPersist->setEscenarioImTierra(DEFAULT_IM_TIERRA);
	aPersist->setEscenarioColorTierra(DEFAULT_COLOR_TIERRA);
	aPersist->setEscenarioImCielo(DEFAULT_IM_CIELO);
	aPersist->setRec("1","100","100","0","1","10","10","no","#FF0000FF");
	aPersist->setTri("2","100","200","0","1","si","#00FF00FF","3.5");
	aPersist->setPent("3","150","50","10","4","2","si","#0000FFFF");
	aPersist->setCirc("4","150","250","10","4","1.5","no","#00FFFFFF","3");
	aPersist->setBazooka("si");
	aPersist->setGrenade("si");
	aPersist->setDynamite("si");
	aPersist->setDonkey("si");
	aPersist->setAirStrike("si");
	aPersist->setHoly("si");
	aPersist->setSheep("si");
	aPersist->setSuicide("si");
	aPersist->setKick("si");
	aPersist->setParrot("si");
	aPersist->setAutomissil("si");


	aPersist->escribirYaml(this->levelFilePath);
	Log::i(PARSER,"Se creo el archivo de Nivel Default");
	this->cargarNivelYaml(this->levelFilePath);

}


void ParserYaml::setTerrain(std::string terrain){
	
	PersistYaml* aPersist=PersistYaml::getInstance();
	aPersist->setMetaEps(this->getMetaEps());
	aPersist->setMetaSca(this->getMetaSca());	
	aPersist->setMetaMaxPlay(this->getMetaMaxPlay());	
	aPersist->setMetaMaxPj(this->getMetaMaxPj());	
	aPersist->setEscenarioFps(this->getEscenarioFps());
	aPersist->setEscenarioAltoU(this->getEscenarioAltoU());
	aPersist->setEscenarioAnchoU(this->getEscenarioAnchoU());
	aPersist->setEscenarioAltoP(this->getEscenarioAltoP());
	aPersist->setEscenarioAnchoP(this->getEscenarioAnchoP());
	aPersist->setEscenarioNivelAgua(this->getEscenarioAgua());
	aPersist->setEscenarioColorAgua(this->getEscenarioColorAgua());
	aPersist->setEscenarioImTierra(terrain);
	aPersist->setEscenarioColorTierra(this->getEscenarioColorTierra());
	aPersist->setEscenarioImCielo(this->getEscenarioCielo());
	for(unsigned j=0;j<this->getCantElem();j++){
		if (this->getElemTipo(j).compare("rec") == 0){
			aPersist->setRec(this->getElemId(j),this->getElemX(j),this->getElemY(j),this->getElemRot(j),this->getElemMasa(j),this->getElemAlto(j),this->getElemAncho(j),this->getElemEstatico(j),this->getElemColor(j));
		
		}
		if (this->getElemTipo(j).compare("tri") == 0){
			aPersist->setTri(this->getElemId(j),this->getElemX(j),this->getElemY(j),this->getElemRot(j),this->getElemMasa(j),this->getElemEstatico(j),this->getElemColor(j),this->getElemEscala(j));
		
		}
		if (this->getElemTipo(j).compare("pent") == 0){
			aPersist->setPent(this->getElemId(j),this->getElemX(j),this->getElemY(j),this->getElemRot(j),this->getElemMasa(j),this->getElemEscala(j),this->getElemEstatico(j),this->getElemColor(j));
		}
		if (this->getElemTipo(j).compare("hexa") == 0){
			aPersist->setHexa(this->getElemId(j),this->getElemX(j),this->getElemY(j),this->getElemRot(j),this->getElemMasa(j),this->getElemEscala(j),this->getElemEstatico(j),this->getElemColor(j));
		}
		if (this->getElemTipo(j).compare("circ") == 0){
			aPersist->setCirc(this->getElemId(j),this->getElemX(j),this->getElemY(j),this->getElemRot(j),this->getElemMasa(j),this->getElemEscala(j),this->getElemEstatico(j),this->getElemColor(j),this->getElemRadio(j));
		}
		
		}
	for(unsigned l=0;l<this->getCantArm();l++){
		aPersist->setArma(this->getArmaTipo(l),this->getArmaHab(l));	
	}




	aPersist->escribirYaml(this->levelFilePath);



}

void ParserYaml::DestroySingleton(){
	if(pInstance != NULL) delete pInstance;
}




ParserYaml* ParserYaml::getInstance(){
	std::string path = "level.yaml";
	if(pInstance == NULL){
		pInstance = new ParserYaml(CONFIG_FILE,path,true);
	}
	return pInstance;
}


ParserYaml* ParserYaml::getInstance(std::string file){
	if(pInstance == NULL){
		std::ifstream fin(file.c_str());
		if( fin.good() == true){
			pInstance = new ParserYaml(CONFIG_FILE,file,true);
		}else{
			Log::e(PARSER,"Archivo de escenario: %s, invalido/corrupto o no encontrado", file.c_str());
			Log::i(PARSER,"Se carga informacion default");
			pInstance = new ParserYaml(CONFIG_FILE,file);
		}
	}
	else{
	std::ifstream fin(file.c_str());
		if( fin.good() == true){
			pInstance = new ParserYaml(CONFIG_FILE,file,true);
		}else{
			Log::e(PARSER,"Archivo de escenario: %s, invalido/corrupto o no encontrado", file.c_str());
			Log::i(PARSER,"Se carga informacion default");
			pInstance = new ParserYaml(CONFIG_FILE,file);
		}
	
	}


	return pInstance;
}

bool ParserYaml::getDefault(){
	return this->isDefault;
}

std::string ParserYaml::yamlNodeToString(const YAML::Node& node){
	std::string sNode;
	node >> sNode;
	return sNode;
}


/*bool ParserYaml::existeElemen(std::string elem,std::vector <dtElemento>& elemVect){
	for(unsigned i=0;i<elemVect.size();i++){
		if (elemVect[i].nombre.compare(elem)==0) return true;
	}
	return false;
} */

void ParserYaml::cargarElementos(const YAML::Node& nodeVect,std::vector <stElemento>& elemVect){
	
	bool fNombre = false;
	bool fX = false;
	bool fY = false;
	bool fRot = false;
	bool fMasa = false;
	bool fAlto = false;
	bool fAncho = false;
	bool fEstatico = false;
	bool fColor = false;
	bool fId = false;
	bool fEscala = false;
	bool fRadio = false;

	
	elemVect.clear();//debo limpiar el elemVect de algun ciclo anterior

	for (unsigned i=0; i<nodeVect.size();i++){
		stElemento elem;
		const YAML::Node& node = nodeVect[i];
		YAML::Mark mark1 = node.GetMark();

		for(YAML::Iterator it=node.begin();it!=node.end();++it){			
			std::string key = this->yamlNodeToString(it.first());
			YAML::Mark mark = it.first().GetMark();

			if (key.compare("tipo")==0)
				label(elem.tipo,fNombre,TipoValido,key,it.second(),mark.line,mark.column);
			else if (key.compare("id")==0)
				label(elem.id,fId,UnsInt,key,it.second(),mark.line,mark.column);
			else if (key.compare("escala")==0)
				label(elem.escala,fEscala,UnsFloat,key,it.second(),mark.line,mark.column);
			else if (key.compare("x")==0)
				label(elem.x,fX,SigFloat,key,it.second(),mark.line,mark.column);
			else if (key.compare("y")==0)
				label(elem.y,fY,SigFloat,key,it.second(),mark.line,mark.column);
			else if (key.compare("ancho")==0)
				label(elem.ancho,fAncho,UnsFloat,key,it.second(),mark.line,mark.column);
			else if (key.compare("alto")==0)
				label(elem.alto,fAlto,UnsFloat,key,it.second(),mark.line,mark.column);
			else if (key.compare("color")==0)
				label(elem.color,fColor,Hexa,key,it.second(),mark.line,mark.column);
			else if (key.compare("masa")==0)
				label(elem.masa,fMasa,UnsFloat,key,it.second(),mark.line,mark.column);
			else if (key.compare("estatico")==0)
				label(elem.estatico,fEstatico,Estatico,key,it.second(),mark.line,mark.column);
			else if (key.compare("rot")==0)
				label(elem.rot,fRot,UnsFloat,key,it.second(),mark.line,mark.column);
			else if (key.compare("radio")==0)
				label(elem.radio,fRadio,UnsFloat,key,it.second(),mark.line,mark.column);
			else {
				Log::e(PARSER,"%s atributo incorrecto en linea: %d, columna: %d",key.c_str(),(mark.line + 1),(mark.column + 1));
			}

		}
		if (!fNombre) elem.tipo = "no init";

		if (validarGuardar(elem.tipo,fNombre,fId,fEscala,fX,fY,fRot,fMasa,fAlto,fAncho,fEstatico,fColor,fRadio)){

			elemVect.push_back(elem);
			//Log se carga el elemento correctamente
		}
		else{
			loggearErrGuardar(elem.tipo,fNombre,fId,fEscala,fX,fY,fRot,fMasa,fAlto,fAncho,fEstatico,fColor,fRadio,mark1);
		}
		fNombre = false;
		fX = false;
		fY = false;
		fRot = false;
		fMasa = false;
		fAlto = false;
		fAncho = false;
		fEstatico = false;
		fColor = false;
		fId = false;
		fEscala = false;
		fRadio = false;
	
	
	}

}

void ParserYaml::cargarNiveles(const YAML::Node& nodeVect,stEscenario& escenarioVect){
	stEscenario escenario;
	
	bool fElem = false;
	bool fAncho = false;
	bool fAlto = false;
	bool fAnchoP = false;
	bool fAltoP = false;
	bool fAgua = false;
	bool fTierra = false;
	bool fCielo = false;
	bool fFPS = false;
	bool fCAgua = false;
	bool fCTierra = false;
	bool fArma = false;
	
		const YAML::Node& node = nodeVect;
		
		 try{
			 YAML::Iterator it=node.begin();
			 
			 if (!node.size()){
				Log::e(PARSER,"Error parseando escenario. Iniciando escenario con configuración default");
				this->startWithDefaultLevel();
				return;
			 }
			 
			 for(;it!=node.end();++it){

				std::string key = this->yamlNodeToString(it.first());
				YAML::Mark mark = it.first().GetMark();
				if (key.compare("ancho-un")==0)
					label(escenario.ancho,fAncho,UnsFloat,key,it.second(),mark.line,mark.column);
				else if (key.compare("alto-un")==0)
					label(escenario.alto,fAlto,UnsFloat,key,it.second(),mark.line,mark.column);
				else if (key.compare("ancho-px")==0)
					label(escenario.anchoP,fAnchoP,UnsInt,key,it.second(),mark.line,mark.column);				
				else if (key.compare("alto-px")==0)
					label(escenario.altoP,fAltoP,UnsInt,key,it.second(),mark.line,mark.column);				
				else if (key.compare("nivel_agua")==0)
					label(escenario.agua,fAgua,UnsFloat,key,it.second(),mark.line,mark.column);				
				else if (key.compare("color_agua")==0)
					label(escenario.colorAgua,fCAgua,Hexa,key,it.second(),mark.line,mark.column);
				else if (key.compare("imagen_tierra")==0)
					label(escenario.tierra,fTierra,Imagen,key,it.second(),mark.line,mark.column);
				else if (key.compare("color_tierra")==0)
					label(escenario.colorTierra,fCTierra,Hexa,key,it.second(),mark.line,mark.column);
				else if (key.compare("imagen_cielo")==0)
					label(escenario.cielo,fCielo,Imagen,key,it.second(),mark.line,mark.column);
				else if (key.compare("fps")==0)
					label(escenario.fps,fFPS,UnsInt,key,it.second(),mark.line,mark.column);
				else if (key.compare("objetos")==0){
					fElem = true;
					this->cargarElementos(it.second(),escenario.elem);
				}
				else if (key.compare("armas")==0){
					fArma = true;
					this->cargarArmas(it.second(),escenario.arma);
				}
				else {
					//LOG: key no es un identificador correcto del nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e(PARSER,"%s no es un identificador correcto de elemento. Linea: %d, Columna: %d",key.c_str(),(mark.line+1),(mark.column + 1));
				}
				
			}
		 }catch(YAML::Exception& e){ 
			Log::e(PARSER,"%s",e.what());
			exit(1);
		 }
		
		if ( fCAgua && fCTierra && fFPS && fElem && fArma && fAncho && fAlto && fAnchoP && fAltoP && fAgua && fTierra && fCielo){
			escenarioVect = escenario;
			//Log carga Nivel correctamente
		}
		else{
			if (!fElem){
				Log::i(PARSER,"Objetos no encontrado, escenario vacio");
			}
			if (!fArma){
				Log::i(PARSER,"Armas no encontrado");
			}
			if (!fFPS){
				Log::e(PARSER,"FPS no encontrado, seteando default");
				escenario.fps = DEFAULT_FSP;
			}
			if (!fAncho){
				Log::e(PARSER,"Ancho no encontrado, seteando default");
				escenario.ancho = DEFAULT_ANCHOU;
			}
			if (!fAlto){
				Log::e(PARSER,"Alto no encontrado, seteando default");
				escenario.alto = DEFAULT_ALTOU;
			}
			if (!fAnchoP){
				Log::e(PARSER,"Ancho Pantalla no encontrado, seteando default");
				escenario.anchoP = DEFAULT_ANCHOP;
			}
			if (!fAltoP){
				Log::e(PARSER,"Alto Pantalla no encontrado, seteando default");
				escenario.altoP = DEFAULT_ALTOP;
			}
			if (!fAgua){
				Log::e(PARSER,"Nivel agua no encontrado, seteando default");
				escenario.agua = DEFAULT_NIVEL_AGUA;
			}
			if (!fCAgua){
				Log::e(PARSER,"Color_agua no encontrado, seteando default");
				escenario.colorAgua = DEFAULT_COLOR_AGUA;
			}
			if (!fTierra){
				Log::e(PARSER,"Tierra no encontrado, seteando default");
				escenario.tierra = DEFAULT_IM_TIERRA;
			}
			if (!fCTierra){
				Log::e(PARSER,"Color_tierra no encontrado, seteando default");
				escenario.colorTierra = DEFAULT_COLOR_TIERRA;
			}
			if (!fCielo){
				Log::e(PARSER,"Cielo no encontrado, seteando default");
				escenario.cielo=DEFAULT_IM_CIELO;
			}
			escenarioVect = escenario;
		}
	//}
	
}

void ParserYaml::cargarMeta(const YAML::Node& nodeVect,stMeta& esMeta){
	stMeta meta;
	//bool fNombre = false;
	bool fEps = false;
	bool fSca = false;
	bool fMaxPlay = false;
	bool fMaxPj = false;
	
	const YAML::Node& node = nodeVect;
		 try{
			 YAML::Iterator it=node.begin();
			 
			 if (!node.size()){
				Log::e(PARSER,"Error parseando escenario. Iniciando escenario con configuración default");
				this->startWithDefaultLevel();
				return;
			 }

			 for(;it!=node.end();++it){
				
				std::string key = this->yamlNodeToString(it.first());
				YAML::Mark mark = it.first().GetMark();
				if (key.compare("epsilon")==0)
					label(meta.epsilon,fEps,UnsFloat,key,it.second(),mark.line,mark.column);
				else if (key.compare("scale")==0)
					label(meta.scale,fSca,UnsInt,key,it.second(),mark.line,mark.column);
				else if (key.compare("max_player")==0)
					label(meta.maxPlay,fMaxPlay,UnsInt,key,it.second(),mark.line,mark.column);
				else if (key.compare("max_per_team")==0)
					label(meta.MaxPj,fMaxPj,UnsInt,key,it.second(),mark.line,mark.column);
				else {
					//LOG: key no es un identificador correcto del nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e(PARSER,"Metadata key no es un identificador correcto de metadata. Linea: %d, Columna: %d",(mark.line + 1),(mark.column + 1));
				}
			 }
			}catch(YAML::Exception& e){ 
			Log::e(PARSER,"%s",e.what());
			exit(1);
		 }
		 if ( fEps && fSca && fMaxPlay && fMaxPj){
			esMeta = meta;
			//Log carga Nivel correctamente
		}
		else{
			if (!fEps){
				Log::e(PARSER,"epsilon no encontrado, seteando default");
				meta.epsilon = DEFAULT_EPSILON ;
			}
			if (!fSca){
				Log::e(PARSER,"scale no encontrado, seteando default");
				meta.scale = DEFAULT_SCALE ;
			}
			if (!fMaxPlay){
				Log::e(PARSER,"max_player no encontrado, seteando default");
				meta.maxPlay = DEFAULT_MAX_PLAY ;
			}
			if (!fMaxPj){
				Log::e(PARSER,"max_per_team no encontrado, seteando default");
				meta.MaxPj = DEFAULT_MAX_PJ_PLAY ;
			}

		}
		esMeta = meta;

}

int ParserYaml::getElementPosition(std::string name){
	std::map< std::string, std::pair<int,std::string> >::iterator it;
	it = this->elementMap.find(name);
	return it->second.first;
}

std::string ParserYaml::getImagePath(std::string name){
	std::map< std::string, std::pair<int,std::string> >::iterator it;
	it = this->elementMap.find(name);
	return it->second.second;
}

std::string ParserYaml::getElementType(int id){
	std::map< std::string, std::pair<int,std::string> >::iterator it = this->elementMap.begin();
	for ( ; it!=this->elementMap.end() ; it++){
		if ( (*it).second.first == id){
			return (*it).first;
		}
	}
}



void ParserYaml::cargarNivelYaml(std::string file){
	std::ifstream fin(file.c_str());
	this->levelFilePath = file;
	
	//flags
	bool fNivel = false;
	bool fMeta = false;

	if (fin.good() == true){
		try{
			YAML::Parser parser(fin);
			YAML::Node node;
			try{ parser.GetNextDocument(node);
			}catch(YAML::Exception& e){

				Log::e(PARSER,"%s", e.what());
				Log::e(PARSER,"Iniciado juego con escenario default");
				this->startWithDefaultLevel();
				//exit(1);

			}

			for(YAML::Iterator it=node.begin();it!=node.end();++it){
				std::string key = this->yamlNodeToString(it.first());
				const YAML::Node& data = it.second();
				YAML::Mark mark = it.first().GetMark();
				if (key.compare("escenario")==0){
					fNivel = true;
					this->cargarNiveles(data,this->todo.escenario);
				}
				else if (key.compare("metadata")==0){
					fMeta = true;
					this->cargarMeta(data,this->todo.meta);
				}
				else{
					//LOG: key no es un identificador correcto del archivo de nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e(PARSER,"%s no es un identificador correcto del archivo de escenario.", key.c_str());
				}
			}
			
			if(fNivel){
				//LOG: Se cargo el nivel correctamente
				Log::i(PARSER,"Se cargo el escenario correctamente");
				
			}
			else{
				//LOG: La carga del nivel guardado es incorrecta
				Log::e(PARSER,"La carga del escenario guardado es incorrecta");
				Log::e(PARSER,"Iniciando escenario con configuración default");
				this->startWithDefaultLevel();
				//exit(1);
			}
			if(fMeta){
				//LOG: Se cargo el nivel correctamente
				Log::i(PARSER,"Se cargo la metadata correctamente");
				
			}
			else{
				//LOG: La carga del nivel guardado es incorrecta
				Log::e(PARSER,"La carga de la metadata guardado es incorrecta");
				Log::i(PARSER,"Iniciando metadata con configuración default");
				//this->startWithDefaultLevel();
				//exit(1);
				this->todo.meta.epsilon = DEFAULT_EPSILON;
				this->todo.meta.scale = DEFAULT_SCALE;
				this->todo.meta.maxPlay = DEFAULT_MAX_PLAY;
				this->todo.meta.MaxPj = DEFAULT_MAX_PJ_PLAY;
				Log::i(PARSER,"Metadata default cargada correctamente");
			}
			fin.close();
		
		}catch(YAML::Exception& e){
			Log::e(PARSER,"%s", e.what());
			Log::e(PARSER,"Iniciando escenario con configuración default");
			this->startWithDefaultLevel();
		}
	
		fin.close();
	} else {
		//LOG: No se puede abrir el archivo de escenario
		Log::e(PARSER,"No se puede abrir el archivo de escenario");
		this->startWithDefaultLevel();
		//exit(1);	
	}
	fin.close();
}




//+++++geters++++++

std::string ParserYaml::getMetaEps(){
	return this->todo.meta.epsilon;
}

std::string ParserYaml::getMetaSca(){
	return this->todo.meta.scale;
}


std::string ParserYaml::getMetaMaxPlay(){
	return this->todo.meta.maxPlay;
}
std::string ParserYaml::getMetaMaxPj(){
	return this->todo.meta.MaxPj;
}


std::string ParserYaml::getEscenarioFps(){
	return this->todo.escenario.fps;
}

std::string ParserYaml::getEscenarioAltoU(){
	return this->todo.escenario.alto;
}

std::string ParserYaml::getEscenarioAnchoU(){
	return this->todo.escenario.ancho;
}

std::string ParserYaml::getEscenarioAltoP(){
	return this->todo.escenario.altoP;
}

std::string ParserYaml::getEscenarioAnchoP(){
	return this->todo.escenario.anchoP;
}


std::string ParserYaml::getEscenarioAgua(){
	return this->todo.escenario.agua;
}

std::string ParserYaml::getEscenarioColorAgua(){
	return this->todo.escenario.colorAgua;
}
std::string ParserYaml::getEscenarioTierra(){
	return this->todo.escenario.tierra;
}
std::string ParserYaml::getEscenarioColorTierra(){
	return this->todo.escenario.colorTierra;
}
std::string ParserYaml::getEscenarioCielo(){
	return this->todo.escenario.cielo;
}

int ParserYaml::getCantElem(){
	return this->todo.escenario.elem.size();
}

std::string ParserYaml::getElemTipo(int e){
	return this->todo.escenario.elem[e].tipo;
}

std::string ParserYaml::getElemId(int e){
	return this->todo.escenario.elem[e].id;
}

std::string ParserYaml::getElemEscala(int e){
	return this->todo.escenario.elem[e].escala;
}
	
std::string ParserYaml::getElemX(int e){
	return this->todo.escenario.elem[e].x;
}

std::string ParserYaml::getElemY(int e){
	return this->todo.escenario.elem[e].y;
}

std::string ParserYaml::getElemAncho(int e){
	return this->todo.escenario.elem[e].ancho;
}

std::string ParserYaml::getElemAlto(int e){
	return this->todo.escenario.elem[e].alto;
}

std::string ParserYaml::getElemColor(int e){
	return this->todo.escenario.elem[e].color;
}

std::string ParserYaml::getElemMasa(int e){
	return this->todo.escenario.elem[e].masa;
}

std::string ParserYaml::getElemEstatico(int e){
	return this->todo.escenario.elem[e].estatico;
}

std::string ParserYaml::getElemRot(int e){
	return this->todo.escenario.elem[e].rot;
}
std::string ParserYaml::getElemRadio(int e){
	return this->todo.escenario.elem[e].radio;
}


int ParserYaml::getCantArm(){
	return this->todo.escenario.arma.size();
}

std::string ParserYaml::getArmaTipo(int e){
	return this->todo.escenario.arma[e].tipo;
}


std::string ParserYaml::getArmaHab(int e){
	return this->todo.escenario.arma[e].habilitado;
}

std::string parserFloat2String(float n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}

std::string parserInt2String(int n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}


std::string ParserYaml::validaAngulo(std::string ang){
	return "";
}


std::string ParserYaml::validaPosicion(std::string pos){
	return ""; }


std::string ParserYaml::validaPantalla(std::string tam){
	return "";
	}


bool ParserYaml::esUnsInt(std::string str){
	for (unsigned int i=0;i<str.length();i++)
		if (isdigit(str[i])==0) return false;
	return true;

}

bool ParserYaml::esSigFloat(std::string str){
	int len = str.length();
	int i = 0;
	int ret = 1;
	int deccnt = 0;
	if (str[0]== '-') i++;
		while(i < len && ret != 0)
		{
			if(str[i] == '.')           // is there a decimal
			{
				deccnt++;               // count a decimal
				if(deccnt > 1)          // is there too many decimal points
					ret = 0;            // too many decimals set return for not numeric
			}
			else
				ret = isdigit(str[i]); // is this character numeric
			i++;                       // increment to next character
		}
	// return result =0 not numeric !=0 is numeric
	if (ret == 0) return false;
	else return true;

}

bool ParserYaml::esUnsFloat(std::string str){
	int len = str.length();
	int i = 0;
	int ret = 1;
	int deccnt = 0;
	while(i < len && ret != 0)
    {
        if(str[i] == '.')           // is there a decimal
        {
            deccnt++;               // count a decimal
            if(deccnt > 1)          // is there too many decimal points
                ret = 0;            // too many decimals set return for not numeric
        }
        else
            ret = isdigit(str[i]); // is this character numeric
        i++;                       // increment to next character
    }
	// return result =0 not numeric !=0 is numeric
	if (ret == 0) return false;
	else return true;

}
bool ParserYaml::esHexa(std::string str){
	int len = str.length();
	int i = 1;
	bool ret = true;
	if (len != 9) return false;
	//else return true;
	if (str[0] != '#') return false;
	while(i < len && ret != 0)
    {
        if ((isdigit(str[i]) || str[i]=='A' || str[i]=='B' || str[i]=='C' || str[i]=='D' || str[i]=='E' || str[i]=='F') == false) return false;
        i++;                       // increment to next character
    }
	// return result =0 not numeric !=0 is numeric
	if (ret == false) return false;
	else return true;
}

bool ParserYaml::esHexaSdl(std::string str){
	int len = str.length();
	int i = 1;
	bool ret = true;
	if (len != 9) return false;
	//else return true;
	if (str[0] != '#') return false;
	while(i < 7 && ret != 0)
    {
        if ((isdigit(str[i]) || str[i]=='A' || str[i]=='B' || str[i]=='C' || str[i]=='D' || str[i]=='E' || str[i]=='F') == false) return false;
        i++;                       // increment to next character
    }
	// return result =0 not numeric !=0 is numeric
	if (ret == false) return false;
	if (str[7] != 'A') return false;
	if (str[8] != 'A') return false;
	return true;
}


bool ParserYaml::esTipoValido(std::string str){
	if ((str.compare("rec")==0) || (str.compare("tri")==0) || (str.compare("pent")==0) || (str.compare("hexa")==0) || (str.compare("circ")==0)) return true;
	return false;


}
bool ParserYaml::validarGuardar(std::string str,bool fNombre,bool fId,bool fEscala,bool fX,bool fY,bool fRot,bool fMasa,bool fAlto,bool fAncho,bool fEstatico,bool fColor,bool fRadio){
	
	if ((str.compare("rec")==0) && (fEscala || fRadio) ) return false;
	if ((str.compare("rec")==0) && fId && fNombre && fX && fY && fRot && fMasa && fAlto && fAncho && fEstatico && fColor) return true;
	if ((str.compare("tri")==0) && (fAlto || fAncho || fRadio)) return false;
	if ((str.compare("tri")==0) && fId && fNombre && fX && fY && fEscala && fRot && fMasa && fEstatico && fColor) return true;
	if ((str.compare("pent")==0) && (fAlto || fAncho || fRadio)) return false;
	if ((str.compare("pent")==0) && fId && fNombre && fX && fY && fEscala && fRot && fMasa && fEstatico && fColor) return true;
	if ((str.compare("hexa")==0) && (fAlto || fAncho || fRadio)) return false;
	if ((str.compare("hexa")==0) && fId && fNombre && fX && fY && fEscala && fRot && fMasa && fEstatico && fColor) return true;
	if ((str.compare("circ")==0) && (fAlto || fAncho))return false;	
	if ((str.compare("circ")==0) && fId && fNombre && fX && fY && fEscala && fRot && fMasa && fEstatico && fColor && fRadio) return true;	

	return false;
}

void ParserYaml::loggearErrGuardar(std::string str,bool fNombre,bool fId,bool fEscala,bool fX,bool fY,bool fRot,bool fMasa,bool fAlto,bool fAncho,bool fEstatico,bool fColor,bool fRadio,YAML::Mark mark){
	if (str.compare("rec")==0){
		if (!fId)Log::i(PARSER,"Atributo ID faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::i(PARSER,"Atributo TIPO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::i(PARSER,"Atributo X faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fY) Log::i(PARSER,"Atributo Y faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fRot) Log::i(PARSER,"Atributo ROT faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fMasa) Log::i(PARSER,"Atributo MASA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fAlto) Log::i(PARSER,"Atributo ALTO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fAncho) Log::i(PARSER,"Atributo ANCHO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEstatico) Log::i(PARSER,"Atributo ESTATICO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fColor) Log::i(PARSER,"Atributo COLOR faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));

		if (fEscala) Log::i(PARSER,"Atributo ESCALA sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fRadio) Log::i(PARSER,"Atributo RADIO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
	}
	else if (str.compare("tri")==0){
		if (!fId)Log::i(PARSER,"Atributo ID faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::i(PARSER,"Atributo TIPO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::i(PARSER,"Atributo X faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fY) Log::i(PARSER,"Atributo Y faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEscala) Log::i(PARSER,"Atributo ESCALA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fRot) Log::i(PARSER,"Atributo ROT faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fMasa) Log::i(PARSER,"Atributo MASA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEstatico) Log::i(PARSER,"Atributo ESTATICO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fColor) Log::i(PARSER,"Atributo COLOR faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		
		if (fAlto) Log::i(PARSER,"Atributo ALTO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fAncho) Log::i(PARSER,"Atributo ANCHO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fRadio) Log::i(PARSER,"Atributo RADIO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
	}
	else if (str.compare("pent")==0){

		if (!fId)Log::i(PARSER,"Atributo ID faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::i(PARSER,"Atributo TIPO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::i(PARSER,"Atributo X faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fY) Log::i(PARSER,"Atributo Y faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fRot) Log::i(PARSER,"Atributo ROT faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fMasa) Log::i(PARSER,"Atributo MASA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEstatico) Log::i(PARSER,"Atributo ESTATICO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEscala) Log::i(PARSER,"Atributo ESCALA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fColor) Log::i(PARSER,"Atributo COLOR faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));

		if (fAlto) Log::i(PARSER,"Atributo ALTO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fAncho) Log::i(PARSER,"Atributo ANCHO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fRadio) Log::i(PARSER,"Atributo RADIO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));

	}
	else if (str.compare("hexa")==0){

		if (!fId)Log::i(PARSER,"Atributo ID faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::i(PARSER,"Atributo TIPO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::i(PARSER,"Atributo X faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fY) Log::i(PARSER,"Atributo Y faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fRot) Log::i(PARSER,"Atributo ROT faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fMasa) Log::i(PARSER,"Atributo MASA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEstatico) Log::i(PARSER,"Atributo ESTATICO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEscala) Log::i(PARSER,"Atributo ESCALA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fColor) Log::i(PARSER,"Atributo COLOR faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));

		if (fAlto) Log::i(PARSER,"Atributo ALTO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fAncho) Log::i(PARSER,"Atributo ANCHO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fRadio) Log::i(PARSER,"Atributo RADIO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));

	}
	else if (str.compare("circ")==0){
		if (!fId)Log::i(PARSER,"Atributo ID faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::i(PARSER,"Atributo TIPO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::i(PARSER,"Atributo X faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fY) Log::i(PARSER,"Atributo Y faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fRot) Log::i(PARSER,"Atributo ROT faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fMasa) Log::i(PARSER,"Atributo MASA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEstatico) Log::i(PARSER,"Atributo ESTATICO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fColor) Log::i(PARSER,"Atributo COLOR faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fEscala) Log::i(PARSER,"Atributo ESCALA faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (!fRadio) Log::i(PARSER,"Atributo RADIO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));

		if (fAlto) Log::i(PARSER,"Atributo ALTO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
		if (fAncho) Log::i(PARSER,"Atributo ANCHO sobrante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
	}
	else if (str.compare("no init")==0){
		if (!fNombre)Log::i(PARSER,"Atributo TIPO faltante en objeto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
	}
	else Log::i(PARSER,"Atributo TIPO incorrecto en linea: %d, columna: %d, descartando objeto.",(mark.line + 1),(mark.column + 1));
}

bool ParserYaml::estaticoValido(std::string str){
	if (str.compare("si") == 0) return true;
	if (str.compare("no") == 0) return true;
	return false;
}

bool ParserYaml::esImagen(std::string str){
	std::string ext(str,str.length()-4,4);
	if (ext.compare(".jpg") == 0) return true;
	if (ext.compare(".bmp") == 0) return true;
	if (ext.compare(".png") == 0) return true;
	return false;
}

bool ParserYaml::esArmaTipoValido(std::string str){
	if (str.compare("Bazooka") == 0) return true;
	if (str.compare("Grenade") == 0) return true;
	if (str.compare("Dynamite") == 0) return true;
	if (str.compare("Donkey") == 0) return true;
	if (str.compare("AirStrike") == 0) return true;
	if (str.compare("Holy") == 0) return true;
	if (str.compare("Sheep") == 0) return true;
	if (str.compare("Suicide") == 0) return true;
	if (str.compare("Kick") == 0) return true;
	if (str.compare("Parrot") == 0) return true;
	if (str.compare("Automissil") == 0) return true;

	return false;
}
bool ParserYaml::esArmaHabilitadoValido(std::string str){
	if (str.compare("si") == 0) return true;
	if (str.compare("no") == 0) return true;
	return false;
}




std::string ParserYaml::getColorById(std::string id){
	  int i;
      for (i = 0; i<this->getCantElem(); i++) 
	  {
        if (id.compare(this->getElemId(i)) == 0) 
			return (this->getElemColor(i));	
      }
	  Log::i(PARSER,"Color del elemento id: %d no encontrado", i-1);
	  return "";
}



void ParserYaml::cargarArmas(const YAML::Node& nodeVect,std::vector <stArma>& armaVect){
	bool fTipo = false;
	bool fHabil = false;
	armaVect.clear();
	for (unsigned i=0; i<nodeVect.size();i++){
		stArma arma;
		const YAML::Node& node = nodeVect[i];
		YAML::Mark mark1 = node.GetMark();
		
		for(YAML::Iterator it=node.begin();it!=node.end();++it){			
			std::string key = this->yamlNodeToString(it.first());
			YAML::Mark mark = it.first().GetMark();

			if (key.compare("tipo")==0)
				label(arma.tipo,fTipo,ArmTipoValido,key,it.second(),mark.line,mark.column);
			else if (key.compare("habilitado")==0)
				label(arma.habilitado,fHabil,ArmHabilitado,key,it.second(),mark.line,mark.column);
			else {
				Log::e(PARSER,"%s atributo incorrecto en linea: %d, columna: %d",key.c_str(),(mark.line + 1),(mark.column + 1));
			}
		}
			if (fTipo && fHabil)
				armaVect.push_back(arma);

			if (!fTipo)Log::i(PARSER,"Atributo TIPO faltante en arma en linea: %d, columna: %d, descartando arma.",(mark1.line + 1),(mark1.column + 1));
			if (!fHabil)Log::i(PARSER,"Atributo HABILITADO faltante en arma en linea: %d, columna: %d, descartando arma.",(mark1.line + 1),(mark1.column + 1));;

			fTipo = false;
			fHabil = false;

		
	}

}





ParserYaml* ParserYaml::pInstance = NULL;