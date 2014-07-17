#include "CollectionEvent.h"

CollectionEvent::CollectionEvent(){

}

CollectionEvent::~CollectionEvent(){

}


void CollectionEvent::add(Notifiable* obj){
	map<Notifiable*, int>::iterator it;
	it = objects.find(obj);
	if(it != objects.end()){
		objects.erase(it);
	}
	objects.insert(pair<Notifiable*, int>(obj, 0));
}

void CollectionEvent::clear(){
	objects.clear();
}

void CollectionEvent::notify(){
	map<Notifiable*, int>::iterator it;
	for(it = objects.begin();
		it != objects.end();
		it++){
			(*it).first->notify();
	}
}
