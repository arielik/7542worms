#include "GamePosition.h"
#include "..\..\utils\ParserYaml.h"
#include "..\..\utils\Util.h"

GamePosition* GamePosition::gp = NULL;

GamePosition::GamePosition(){
	deltaY = WORM_WIDTH;
	deltaX = WORM_HEIGHT;
	completed = false;
}

GamePosition::~GamePosition(){
}

GamePosition* GamePosition::getInstance(){
	if(!gp){
		gp = new GamePosition();
	}
	return gp;
}

bool GamePosition::isCompleted(){
	return completed;
}

void GamePosition::generate(int supreme, int width){
	int countHight,	countWidth;
	countWidth = (int)(width / deltaY);
	countHight = (int)(supreme / deltaX);
	this->fillPostion(countWidth, countHight);
}

void GamePosition::validPosition(list<pair<int,int>>* terrain){
	list<map<int, list<int>>::iterator> remove;
	list<map<int, list<int>>::iterator>::iterator itRemove;

	this->findPosInvalid(&remove,terrain);
	for(itRemove = remove.begin() ; 
		itRemove != remove.end(); 
		itRemove++){
			positions.erase((*itRemove));
	}

	remove.clear();
	this->findPosEmpty(&remove);

	for(itRemove = remove.begin() ; 
		itRemove != remove.end(); 
		itRemove++){
			positions.erase((*itRemove));
	}
	this->completed = true;
}


void GamePosition::getRandomPosition(int* x, int* y){
	map<int, list<int>>::iterator it;
	int size = positions.size();
	int index = 0;
	if(size){
		if(size > 1){
			it = this->getItemMap(Util::getRandom(1, size - 1));
		}else{
			it = this->getItemMap(Util::getRandom(1, size));
		}
		
		*y = it->first;
		*x = getX(&it->second);
		if(!it->second.size()){
			positions.erase(it);
		}
	}else{
		*x = -1;
		*y = -1;	
	}
}

int GamePosition::getX(list<int>* listX){
	list<int>::iterator it;
	int index = 0, result = 0;
	int size = listX->size();
	it = this->getItemList(Util::getRandom(1, size), listX);
	result = *it;
	listX->erase(it);
	return result;
}

void GamePosition::fillPostion(int countWidth, int countHight){
	list<int> listValues;
	int value = 0;
	for(int i = 0; i < countHight; i++){
		listValues.push_back(value);
		value += deltaX;
	}
	value = 0;
	for(int i = 0; i < countWidth; i++){
		positions.insert(pair<int, list<int>>(value, listValues));
		value += deltaY;
	}
}


void GamePosition::findPosEmpty(
	list<map<int, list<int>>::iterator>* remove){
	map<int, list<int>>::iterator it;
	for(it = positions.begin(); 
		it != positions.end(); 
		it++){
		if(!it->second.size()){
			remove->push_back(it);
		}
	}
}

void GamePosition::findPosInvalid(
	list<map<int, list<int>>::iterator>* remove,
	list<pair<int,int>>* terrain){
	map<int, list<int>>::iterator itPosition;
	map<int, list<int>>::iterator itAuxPosition;
	list<pair<int,int>>::iterator itTerrain;
	itAuxPosition = positions.begin();
	itTerrain = terrain->begin();
	int rankMin = 0, rankMax = 0;

	for(; 
		itTerrain != terrain->end(); 
		itTerrain++){
		rankMin = itTerrain->first;
		rankMax = itTerrain->second;
		for(itPosition = itAuxPosition; 
			itPosition != positions.end(); 
			itPosition++){
			if( itPosition->first < rankMin	){
				remove->push_back(itPosition);
			}
			else if(itPosition->first > rankMax){
				itAuxPosition = itPosition;
				break;
			}
		}
	}

	for(itPosition = itAuxPosition; 
		itPosition != positions.end(); 
		itPosition++){
		if(itPosition->first > rankMax){
			remove->push_back(itPosition);
		}
	}
}

map<int, list<int>>::iterator GamePosition::getItemMap(int index){
	map<int, list<int>>::iterator it;
	for(it = positions.begin();
		it != positions.end();
		it++){
		--index;
		if(!index){
			break;
		}
	}
	return it;
}

list<int>::iterator GamePosition::getItemList(int index, list<int>* alist){
	list<int>::iterator it;
	for(it = alist->begin();
		it != alist->end();
		it++){
		--index;
		if(!index){
			break;
		}
	}
	return it;
}

