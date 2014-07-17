#include "ChangeEvent.h"

ChangeEvent::ChangeEvent(void){
	stateBar =
	coordenate =
	aimEnter = false;

}
ChangeEvent::~ChangeEvent(void){}

bool ChangeEvent::isAimEnter(){
	return aimEnter;
}

bool ChangeEvent::isStateBar(){
	return stateBar;
}


bool ChangeEvent::isCoordenate(){
	return coordenate;
}

void ChangeEvent::setFactor(int factor){
	this->factor = factor;
}

void ChangeEvent::setAimEnter(bool aimEnter){
	this->aimEnter = aimEnter;
}

void ChangeEvent::setStateBar(bool stateBar){
	this->stateBar = stateBar;
}

void ChangeEvent::setCoordenate(bool coordenate){
	this->coordenate = coordenate;
}
