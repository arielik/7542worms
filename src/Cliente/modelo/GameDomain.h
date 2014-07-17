#pragma once

#ifndef __GAMEDOMAIN_H__
#define __GAMEDOMAIN_H__


#include <string>
#include <vector>
#include <list>

#include "../../utils/Util.h"
#include "../../Servidor/modelo/GameElement.h"





class GameDomain{

	std::string playerID;


public:

	std::map<int,GameElement> domainElements;
	std::map<Player,int> playersLife;

	// Key: PlayerID, Elem: Pair<State,Color>
	std::map<Player,std::pair<StateConn,int>> playersPlaying;


	GameDomain();
	 ~GameDomain(void);

	 void setPlayerID(std::string playerID){ this->playerID = playerID; }
	 std::string getPlayerID(){ return this->playerID; }

	 void setPlayerLife(std::string playerId, int life){
		 this->playersLife[playerId] = life;
	 }

	 int getPlayerLife(std::string playerId){
		 return this->playersLife[playerId];
	 }

	 void printDomain(){

		 std::map<int,GameElement> copy = this->domainElements;
		 std::map<int,GameElement>::iterator it=copy.begin();
		 for( ; it != copy.end(); ++it)
			 Log::i("ID Map: %d, ID elem: %d",it->first,it->second.getId());
	 }

	 void addElementToDomain(GameElement element)
	 {
		 Log::i("\nAdded to domain wormid: %d",element.getId());
			this->domainElements.insert( std::make_pair(element.getId(),element) ); 
	 }

	 std::map<int,GameElement>* getDomainElements() { return &this->domainElements;}

	 void updateElement(int id, float x, float y);
	 void updateElement(int id, float x, float y, Movement action, int life, int weaponid);

	 StateConn getPlayerState(Player p){ return this->playersPlaying[p].first; }
	 unsigned long getPlayerColor(Player p){ return this->playersPlaying[p].second; }
	 void setPlayerState(Player p, StateConn c, unsigned long color);
	 void addPlayer(Player p, StateConn c, unsigned long color){
		this->playersPlaying[p] = std::make_pair(c,color);
	}

	 void updatePlayerState(Player p, StateConn c);

	 void updatePlayerStatus(Player p, StateConn st){
		 this->playersPlaying[p] = std::make_pair(st,this->playersPlaying[p].second);
	 }

	 bool existElement(int id);

	 void removeElement(int id);

	 std::map<Player,std::pair<StateConn,int>>* getPlayersPlaying() {return &this->playersPlaying;}

	 std::map<Player,int>* getPlayersLife() {return &this->playersLife;}
};

#endif
