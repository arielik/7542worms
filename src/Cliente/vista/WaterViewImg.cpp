#include "WaterViewImg.h"
#include "TextureManager.h"

WaterViewImg::WaterViewImg():View(1,1){
}

WaterViewImg* WaterViewImg::FactoryWater(int Gap, float timmerChange,bool bBackground){
	WaterViewImg* wvi = new WaterViewImg(timmerChange, bBackground);
	wvi->loadWater(Gap);
	wvi->iniView();
	wvi->iniRender();
	return wvi;
}


void WaterViewImg::initialize(int Gap, float timmerChange,bool bBackground){
	this->timmerChange = timmerChange;
	this->bBackground = bBackground;
	this->Gap = 35;
	this->enableScroll();
	this->loadWater3(Gap);
	this->iniView();
	this->iniRender();
}

WaterViewImg* WaterViewImg::FactoryWater2(int Gap, float timmerChange,bool bBackground){
	WaterViewImg* wvi = new WaterViewImg(timmerChange, bBackground);
	wvi->loadWater2(Gap);
	wvi->iniView();
	wvi->iniRender();
	return wvi;
}

WaterViewImg::WaterViewImg(float timmerChange, bool bBackground):View(0,30){
	this->timmerChange = timmerChange;
	this->bBackground = bBackground;
	this->Gap = 35;
	this->enableScroll();
}

WaterViewImg::~WaterViewImg(){

}

void WaterViewImg::iniView(){
	this->it = water.begin();
}

void WaterViewImg::actionWater(){

}
void WaterViewImg::iniRender(){
	this->timer.start();
	bRender = true;
}

void WaterViewImg::controlRender(){
	float seg = timer.elapsed();
	if(seg > 0.5){
		this->iniRender();
	}
}

void WaterViewImg::draw(SDLScreen & screen){
	if(bBackground){
		this->drawbackground(screen);
	}
	this->drawSurf(screen);
}

void WaterViewImg::drawSurf(SDLScreen & screen){
	if(bRender){
		it++;
		if(it == water.end()){
			this->iniView();
		}
		bRender = false;
	}
	else{
		this->controlRender();
	}
	pair<int, int> point = it->second.getPosition();
	pair<int, int> dimen = it->second.getDimension();

	TextureManager::Instance().drawFrame(
								it->first, 
								this->getX(),//point.first, 
								this->getY() - this->Gap,//point.second,
								dimen.first, 
								dimen.second, 
								0, 0, 
								screen.getRenderer(),
								false, 
								SDL_FLIP_NONE,
								true);
}


void WaterViewImg::drawbackground(SDLScreen & screen){
	pair<int, int> point = backgroundWater.second.getPosition();
	pair<int, int> dimen = backgroundWater.second.getDimension();
	TextureManager::Instance().drawFrame(
											backgroundWater.first, 
											this->getX(),//point.first, 
											this->getY(),//point.second,
											dimen.first, 
											dimen.second, 
											0, 
											0, 
											screen.getRenderer(),
											false, 
											SDL_FLIP_NONE,
											true);
}

void WaterViewImg::loadWater(int Gap){
	int positionX, positionX1,
		positionY, positionX2,
		lebel, 
		width, width2,
		height, height2;
	pair<int, int> dimension;
	
	dimension = TextureManager::Instance().getDimension("eart");
	lebel = (int)(Util::string2float(ParserYaml::
		getInstance()->getEscenarioAgua()) 
							* ESCALA_UL2PX);
	
	positionX = 0;
	positionY = dimension.second - lebel + 8;
	width = dimension.first;
	height = lebel;

	water.insert(pair<string,Shape>("marea_1_1", 
		Shape(positionX, positionY - Gap, width, Gap)));
	water.insert(pair<string,Shape>("marea_1_2", 
		Shape(positionX, positionY - Gap, width, Gap)));
	water.insert(pair<string,Shape>("marea_1_3", 
		Shape(positionX, positionY - Gap, width, Gap)));
	water.insert(pair<string,Shape>("marea_1_4", 
		Shape(positionX, positionY - Gap, width, Gap)));

	this->setY(positionY);
	backgroundWater = pair<string,Shape>("FondoAgua", 
		Shape(positionX, positionY, width, height));

}

void WaterViewImg::loadWater2(int Gap){
	int positionX, positionX1,
		positionY, positionX2,
		lebel, 
		width, width2,
		height, height2;
	pair<int, int> dimension;
	
	dimension = TextureManager::Instance().getDimension("eart");
	lebel = (int)(Util::string2float(ParserYaml::
		getInstance()->getEscenarioAgua()) 
							* ESCALA_UL2PX);
	
	positionX = 0;
	this->Gap += Gap;
	positionY = dimension.second - lebel + 8 + 60;
	width = dimension.first;
	height = lebel;

	water.insert(pair<string,Shape>("marea_1_1", 
		Shape(positionX, positionY - Gap, width, 47)));
	water.insert(pair<string,Shape>("marea_1_2", 
		Shape(positionX, positionY - Gap, width, 47)));
	water.insert(pair<string,Shape>("marea_1_3", 
		Shape(positionX, positionY - Gap, width, 47)));
	water.insert(pair<string,Shape>("marea_1_4", 
		Shape(positionX, positionY - Gap, width, 47)));

	this->setY(positionY);
	backgroundWater = pair<string,Shape>("FondoAgua", 
		Shape(positionX, positionY, width, height));

}



void WaterViewImg::loadWater3(int Gap){
	int positionX, positionX1,
		positionY, positionX2,
		lebel, 
		width, width2,
		height, height2;
	pair<int, int> dimension;
	
	dimension = TextureManager::Instance().getDimension("eart");
	lebel = (int)(Util::string2float(ParserYaml::
		getInstance()->getEscenarioAgua()) 
							* ESCALA_UL2PX);
	
	positionX = 0;
	this->Gap += Gap;
	positionY = dimension.second - lebel - 5;
	width = dimension.first;
	height = lebel;

	water.insert(pair<string,Shape>("marea_1_1", 
		Shape(positionX, positionY - Gap, width, 47)));
	water.insert(pair<string,Shape>("marea_1_2", 
		Shape(positionX, positionY - Gap, width, 47)));
	water.insert(pair<string,Shape>("marea_1_3", 
		Shape(positionX, positionY - Gap, width, 47)));
	water.insert(pair<string,Shape>("marea_1_4", 
		Shape(positionX, positionY - Gap, width, 47)));

	this->setY(positionY);
	backgroundWater = pair<string,Shape>("FondoAgua", 
		Shape(positionX, positionY, width, height));

}
