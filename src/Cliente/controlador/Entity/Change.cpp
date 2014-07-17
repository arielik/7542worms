#include "Change.h"
#include <algorithm>
#include "..\..\..\utils\Log.h"

Change* Change::change = NULL;

Change::Change(void){
	x  = 0, y  = 0,
	xp = 0, yp = 0;
	stateBar =
	coordenate =
	aimEnter = false;
}

void Change::removeAll(){
	objects.clear();

}

Change::~Change(void){}

Change* Change::getInstance(){
	if(!change){
		change = new Change();
	}
	return change;
}


bool Change::newEvent(){
	bool result = true;
	if((x == xp) && (y == yp)){
		result = false;
	}
	else{
		xp = x, yp = y;
	}
	return result;
}


void Change::add(OnChangeListener * obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Change::remuve(OnChangeListener * obj){
	list<OnChangeListener*>::iterator it;
	list<OnChangeListener*>::iterator itDrop;
	it = objects.begin();
	itDrop = objects.end();
	for(; it != objects.end(); it++){
		if((*it) == obj){
			itDrop = it;
			break;
		}
	}
	if(itDrop != objects.end()){
		objects.erase(itDrop);
	}
}

void Change::notify(){
	list<OnChangeListener*>::iterator it;
	ChangeEvent co;
	co.x = x, co.y = y;
	co.factor = this->factor;
	co.setStateBar(this->stateBar);
	co.setCoordenate(this->coordenate);
	co.setAimEnter(this->aimEnter);
	co.aimMove = this->aimMove;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnChange(co);
	}
}

bool Change::isStateBar(){
	return stateBar;
}

bool Change::isAimEnter(){
	return aimEnter;
}

bool Change::isCoordenate(){
	return coordenate;
}


void Change::setAimEnter(bool aimEnter){
	this->aimEnter = aimEnter;
}

void Change::setFactor(int factor){
	this->factor = factor;
}


void Change::setAimMove(AimMove aimMove){
	this->aimMove = aimMove;
}

void Change::setStateBar(bool stateBar){
	this->stateBar = stateBar;
}

void Change::setCoordenate(bool coordenate){
	this->coordenate = coordenate;
}




void Change::setEvent(int x, int y){
	this->x = x, this->y = y;
}


bool Change::isRegistered(OnChangeListener * obj){
	return (find(objects.begin(),
			objects.end(), 
			obj) != objects.end());
}
