#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include "../../utils/ParserYaml.h"
#include "../../utils/PersistYaml.h"
#include "../../utils/Util.h"
#include "TerrainProcessor.h"
#include "GamePlayer.h"
#include "Exceptions\PlayerException.h"


using namespace server_model_exp;

class GameLevel {
	private:

		std::map<string, GamePlayer*> players;
		int amountUser;
		int amountWorms;
		int idUnique;
		int idColorUnique;


		void addUserIntoLevel(string user)
			throw(PlayerExp);
		

		int levelHeight;
		int levelWidth;
		float waterLevel;

		std::map<int,GameElement> modelElements;
		std::map<int, GameElement*> entities;
		TerrainProcessor* aTerrainProcessor;
		GameElement getEntity(int id);

		bool validElementPosition(int id);
		void destroyPlayers();


	public:
		GameLevel();
		virtual ~GameLevel();

		std::vector<b2Body*> myTerrain;
		std::list<poly_t*>* myPol;

		void destroyEntities();
		void updateElementPosition(int pos, int id, float x, float y, float angle);

		//Creates the level based on YAML parser data
		bool createLevel(GameLevel*);

		// Getters
		int getHeight();
		int getWidth();
		TerrainProcessor* getTerrain();

		// Setters
		void setHeight(int h);
		void setWidth(int w);
		void setTerrain( b2World* mworld, char* path,float epsilon, int scale,int waterLevel );

		//TODO @future - void removePlayer(GamePlayer *jugador);
		void addPlayer(string user, GamePlayer *pg);//TODO @future - void addPlayer(GamePlayer *jugador);
		GamePlayer *getPlayer(string user);
		
		// ESTE NO VA 
		std::map<int,GameElement> getModelElements();

		std::map<int, GameElement*> getEntities();
		
		GameElement* getEntityByID(int id){ return this->entities[id]; }

		void addEntity(GameElement *entidad);

		void removeEntity(int id);

		void setWaterLevel(float waterLevel){ this->waterLevel = waterLevel;};
		float getWaterLevel(){ return this->waterLevel;};


		//void entityUpdatePosition(int tileX, int tileY, int id);
		bool posicionOcupada(float x, float y);

		bool checkMapPosition(float x, float y);

		PlayerAccounting acceptPlayer(std::string playerID);

		void disconnectPlayer(std::string playerID);
		StateConn getPlayerStatus(std::string playerId);
		int getPlayerColor(std::string playerID);

		int getWormsFromPlayer(std::string playerId,Playable* p);
		void disconnectWormsFromPlayer(std::string playerId);
		void connectWormsFromPlayer(std::string playerId);

		int getAmountOfUsers(){ return this->players.size(); }

		std::map<string, GamePlayer*> getPlayers(){ return this->players; }

		//void doExplosion(b2Vec2 removalPosition, int removalRadius, b2World* mundo);
		//poly_t makeConvexRing(b2Vec2 position, float radius, int vertices);

		bool stopWormsFromPlayer(std::string playerId);

		int updateStep;

};
