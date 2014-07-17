#ifndef __GAMEPLAYER__
#define __GAMEPLAYER__

#include "Entities\Worm.h"
#include "..\..\utils\Util.h"
#include <list>

using namespace std;

class GamePlayer{
public:
	GamePlayer(std::string playerID);
	GamePlayer(std::string playerID, int color);
	~GamePlayer();
	static GamePlayer* NewPlayerFactory(int prefId, int amountWorms);
	void setStateConn(StateConn sc);
	void add(Worm* w);
	std::vector<Worm*> getWorms(){ return this->worms;}
	void initPlayer(int prefId, int amountWorms, int height, int width);
	std::string playerID;
	StateConn getStatus(){ return this->state; }
	bool hasAnyWormAlive() { return ( !this->worms.empty() ) ? true : false; }
	void updateLife();
	int getLife() { return this->life; }
	int getColor() { return this->color; }

private:
	int life;
	int color;
	std::vector<Worm*> worms;
	StateConn state;
	pair<int,int> transformBmpToBox2D(pair<int,int> vertex, int height, int width);
};

#endif /*__GAMEPLAYER__*/
