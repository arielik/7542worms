#include "Over.h"
#include <algorithm>

Over* Over::over = NULL;

Over::Over(void){}

Over::~Over(void){}

Over* Over::getInstance(){
	if(!over){
		over = new Over();
	}
	return over;
}

void Over::removeAll(){
	objects.clear();

}

void Over::add(OnScrollListener * obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Over::remuve(OnScrollListener * obj){
	list<OnScrollListener*>::iterator it;
	list<OnScrollListener*>::iterator itDrop;
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

void Over::notify(){
	list<OnScrollListener*>::iterator it;
	ScrollEvent s;
	s.xSpeed = x, s.ySpeed = y;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnScroll(s);
	}
}


void Over::setEvent(int x, int y){
	this->x = x, this->y = y;
}


bool Over::isRegistered(OnScrollListener * obj){
	return (find(objects.begin(),
			objects.end(), 
			obj) != objects.end());
}
