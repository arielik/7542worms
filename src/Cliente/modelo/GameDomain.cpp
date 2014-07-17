#include "GameDomain.h"

GameDomain::GameDomain(){
}
		
GameDomain::~GameDomain(void){
	//TODO: Liberar game element?
}

void GameDomain::updateElement(int id, float posX, float posY){
	std::map<int,GameElement>::iterator it;

	it = this->domainElements.find(id);
	if ( it != this->domainElements.end() ){
		this->domainElements[id].setPosition(std::make_pair(posX,posY));
	}
}

bool GameDomain::existElement(int id){
	std::map<int,GameElement>::iterator it;

	it = this->domainElements.find(id);
	if ( it != this->domainElements.end() ){
		return true;
	}
	return false;
}

void GameDomain::removeElement(int id) {
	if (existElement(id)) {
		this->domainElements.erase(id);
	} else {
		Log::e("GameDomain::removeElement no existe id %d", id);
	}
}

void GameDomain::updateElement(int id, float posX, float posY, Movement action, int life, int weaponid){
	std::map<int,GameElement>::iterator it;

	it = this->domainElements.find(id);

	if ( it != this->domainElements.end() ){
		this->domainElements[id].setPosition(std::make_pair(posX,posY));
		this->domainElements[id].setAction(action);
		this->domainElements[id].setLife(life);
		this->domainElements[id].setWeapon(weaponid);
		//Log::i("GameDomain::updateElement: Actualizado worm id %d con weapon id %d", id, weaponid);
	} else {
		Log::e("GameDomain::updateElement: No se pudo actualizar el worm id %d", id);
	}

}

void GameDomain::setPlayerState(Player p, StateConn c, unsigned long color){
	this->playersPlaying[p] = std::make_pair(c,color);
}

void GameDomain::updatePlayerState(Player p, StateConn c)
{
	std::map<Player,std::pair<StateConn,int>>::iterator it;
	it = this->playersPlaying.find(p);
	if (it != this->playersPlaying.end()) {
		unsigned long color = this->playersPlaying[p].second;
		this->playersPlaying[p] = std::make_pair(c,color);	
	}
}