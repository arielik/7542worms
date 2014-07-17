#include "Action.h"
#include <algorithm>
#include "..\..\..\utils\Log.h"

Action* Action::action = NULL;

Action::Action(void){
	last = a = NONE;
}

void Action::removeAll(){
	objects.clear();

}

Action::~Action(void){}

Action* Action::getInstance(){
	if(!action){
		action = new Action();
	}
	return action;
}

void Action::add(OnActionListener * obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Action::remuve(OnActionListener * obj){
	list<OnActionListener*>::iterator it;
	list<OnActionListener*>::iterator itDrop;
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

void Action::notify(){
	list<OnActionListener*>::iterator it;
	ActionEvent a;
	//Log::e("Erik, Notifico accion menu");
	a.action = this->a;
	a.factor = this->factor;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnAction(a);
	}
}

void Action::setEvent(ActionKey a){
	this->a = a;
}

void Action::setLastEvent(ActionKey a){
	this->last = a;
}

void Action::setAim(int xAim, int yAim){
	this->xAim = xAim;
	this->yAim = yAim;
}
void Action::setFactor(int factor){
	this->factor = factor;
}

bool Action::newEvent(){
	bool result = true;
	if(last == a){
		result = false;
	}
	else{
		last = a;
	}
	return result;
}

bool Action::isRegistered(OnActionListener * obj){
	return (find(objects.begin(),
				objects.end(), 
				obj) != objects.end());
}