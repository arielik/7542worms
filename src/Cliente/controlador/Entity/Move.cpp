#include "Move.h"
#include <algorithm>

Move* Move::move = NULL;

Move::Move(void){
	x  = 0, y  = 0,
	xp = 0, yp = 0;
}

Move::~Move(void){}


void Move::removeAll(){
	objects.clear();

}


Move* Move::getInstance(){
	if(!move){
		move = new Move();
	}
	return move;
}

void Move::add(OnMovementListener* obj){
	if(!isRegistered(obj)){
		objects.push_back(obj);
	}
}

void Move::remuve(OnMovementListener* obj){
	list<OnMovementListener*>::iterator it;
	list<OnMovementListener*>::iterator itDrop;
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

bool Move::newEvent(){
	bool result = true;
	if((x == xp) && (y == yp)){
		result = false;
	}
	else{
		xp = x, yp = y;
	}
	return result;
}

void Move::notify(){
	list<OnMovementListener*>::iterator it;
	MovementEvent m;
	//Log::d("(%d,%d)\n", this->x, this->y);
	m.x = this->x, m.y = this->y;
	it = objects.begin();
	for(; it != objects.end(); it++){
		(*it)->OnMovement(m);
	}
}

bool Move::isRegistered(OnMovementListener * obj){
	return (find(objects.begin(),
			objects.end(), 
			obj) != objects.end());
}