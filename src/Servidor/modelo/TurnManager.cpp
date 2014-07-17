#include "TurnManager.h"

TurnManager::TurnManager(int nrPlayers):
	maxPlayers(nrPlayers){

	this->indicator = NOT_YET_ASSIGNED;

}

std::string TurnManager::getCurrentPlayerTurn(){
	if ( this->indicator == NOT_YET_ASSIGNED ){
		this->indicator = 0;
	}
	return this->players[indicator]; 

}


void TurnManager::addPlayer(std::string player){
	this->players.push_back(player);
}

void TurnManager::removePlayer(std::string player){

	for ( std::vector<std::string>::iterator it = players.begin(); it != players.end(); ++it){
		if ( !it->compare(player) ){
			players.erase(it);
			return;
		}
	
	}



}



std::string TurnManager::getNextPlayerTurn(){
	if ( this->indicator == NOT_YET_ASSIGNED ){
		this->indicator = rand() % this->maxPlayers;
		return this->players[indicator];
	}
	int newPos = this->indicator + 1;
	this->indicator = newPos % this->maxPlayers;
	//printf("\nTurn for:  %s",this->players[indicator].c_str());
	return this->players[indicator];
}


TurnManager::TurnManager(){

}

TurnManager::~TurnManager(){

}


