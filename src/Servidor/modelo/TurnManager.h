#pragma once

#ifndef TURNMANAGER_H_
#define TURNMANAGER_H_

#define NOT_YET_ASSIGNED -1

#include <vector>
#include <string>

class TurnManager{

	private:
		std::vector<std::string> players;
		int indicator;
		int maxPlayers;

		

	public:
		TurnManager();
		~TurnManager();
		TurnManager(int nrPlayers);
		
		std::string getCurrentPlayerTurn();
		int getRegisteredPlayers(){ return this->players.size(); }
		void addPlayer(std::string player);
		void removePlayer(std::string player);
		std::string getNextPlayerTurn();


};

#endif