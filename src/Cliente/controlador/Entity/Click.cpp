#include "Click.h"
#include <algorithm>

Click* Click::click = NULL;

Click::Click(void){}

Click::~Click(void){}

Click* Click::getInstance(){
	if(!click){
		click = new Click();
	}
	return click;
}


void Click::removeAll(){
	objects.clear();

}


void Click::add(OnClickListener * obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Click::remuve(OnClickListener * obj){
	list<OnClickListener*>::iterator it;
	list<OnClickListener*>::iterator itDrop;
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

void Click::notify(){
	list<OnClickListener*>::iterator it;
	ClickEvent c;
	c.x = x, c.y = y;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnClick(c);
	}
}

void Click::setEvent(int x, int y){
	this->x = x;
	this->y = y;
}


bool Click::isRegistered(OnClickListener * obj){
	return (find(objects.begin(),
			objects.end(), 
			obj) != objects.end());
}
