#include "PartialScreen.h"

PartialScreen::PartialScreen()
{
}


PartialScreen::~PartialScreen(void)
{
}
void PartialScreen::getSpeed(int* x, int* y){
	(*x) = (this->xlimit - this->x)*this->xDir;
	(*y) = (this->ylimit - this->y)*this->yDir;
}

PartialScreen* PartialScreen::Inside(int x, int y, Side s){
	list<PartialScreen*>::iterator it;
	PartialScreen* result = NULL,
	              *resultAux = NULL;
	if (((xFrom <= x) && (x <= xTo)) &&
		((yFrom <= y) && (y <= yTo)) ){
		result = this;
		for(it = screens.begin();
			it != screens.end();
			it++){
				resultAux = (*it)->Inside(x,y);
				if(resultAux != NULL){
					if(this->sharedDir(resultAux->id, s)){
						result = resultAux;
						break;
					}
				}
		}
	}
	return result;
}

bool PartialScreen::sharedDir(int id, Side s){
	map<int, Side>::iterator it;
	it = dir.find(id);
	if(it != dir.end()){
		if((*it).second == s){
			return true;
		}
	}
	return false;
}

PartialScreen* PartialScreen::Inside(int x, int y){
	PartialScreen* result = NULL;
	if (((xFrom <= x) && (x <= xTo)) &&
		((yFrom <= y) && (y <= yTo)) ){
			result = this;
	}
	return result;
}

void PartialScreen::addRelationScreen(PartialScreen *s){
	screens.push_back(s);
}
