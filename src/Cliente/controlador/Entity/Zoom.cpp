#include "Zoom.h"
#include <algorithm>


Zoom* Zoom::zoom = NULL;

Zoom::Zoom(void){}

Zoom::~Zoom(void){}

Zoom* Zoom::getInstance(){
	if(!zoom){
		zoom = new Zoom();
	}
	return zoom;
}

void Zoom::removeAll(){
	objects.clear();

}

void Zoom::add(OnZoomListener* obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Zoom::remuve(OnZoomListener* obj){
	list<OnZoomListener*>::iterator it;
	list<OnZoomListener*>::iterator itDrop;
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

void Zoom::notify(){
	list<OnZoomListener*>::iterator it;
	ZoomEvent z;
	z.y = this->y;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnZoom(z);
	}
}

void Zoom::setEvent(int y){
	this->y = y;
}

bool Zoom::isRegistered(OnZoomListener * obj){
	return (find(objects.begin(),
			objects.end(), 
			obj) != objects.end());
}
