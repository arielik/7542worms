#ifndef __GAMEPOSITION__
#define __GAMEPOSITION__
#include <map>
#include <list>
#include "..\..\utils\Constantes\Constantes.h"

using namespace std;

class GamePosition{
public:
	static GamePosition* getInstance();
	void generate(int supreme, int width);
	void validPosition(list<pair<int,int>>* terrain);
	void getRandomPosition(int* x, int* y);
	bool isCompleted();

	//std::map<int, std::pair<int,int>> validPos;
	//std::map<int,bool> usedPos;
	//std::pair<int,int> getValidPos();

private:
	int getX(list<int>* listX);
	int supreme, deltaX, deltaY;
	bool completed;
	list<pair<int, int>> terrain;
	map<int, list<int>> positions;
	static GamePosition* gp;

	GamePosition();
	~GamePosition();
	void fillPostion(int countWidth, int countHight);
	void findPosEmpty(list<map<int, list<int>>::iterator>* remove);
	void findPosInvalid(list<map<int, list<int>>::iterator>* remove,
	list<pair<int,int>>* terrain);
	map<int, list<int>>::iterator getItemMap(int index);
	list<int>::iterator getItemList(int index, list<int>* alist);

};
#endif
