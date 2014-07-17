#pragma once

#ifndef __VIEW_H__
#define __VIEW_H__
#include <list>
#include "ViewGroup.h"
#include "FigureView.h"
#include "EartView.h"
#include "SkyView.h"
#include "WaterView.h"
#include "ProjectileView.h"
#include "TimerView.h"
#include "PowerView.h"
#include "PlayerProgressView.h"
#include "TerrainView.h"
#include "StateBarView.h"
#include "WormView.h"
#include "MenuWeaponView.h"
#include "WaterViewImg.h"
#include "ElemViewGroup.h"
#include "ExplosionViewGroup.h"
#include <map>
#include <string>
#include "Weapon.h"
using std::map;
using std::string;

typedef ElemViewGroup<ProjectileView*> ProjectileViewGroup;
typedef ElemViewGroup<WormView*> WormViewGroup;

class GameView : 	public ViewGroup
{
private:
	map<int, FigureView*> figures;
	
	WormViewGroup * wormViewGroup;
	ProjectileViewGroup* projectileViewGroup;
	ExplosionViewGroup* explosionViewGroup;

	EartView* eart;
	SkyView* sky;
	WaterView* water;
	TerrainView* terrain;
	StateBarView* stateBar;
	MenuWeaponView* menuWeapon;
	WaterViewImg* waterImg;

	PlayerProgressView * pProgressView;
	PowerView* powerView;
	TimerView* timerView;

public:
	GameView(int x, int y, int width, int height);

	void putFigure(int id, FigureView* figure);

	void setWormContainer(WormViewGroup * wormViewGroup);
	WormViewGroup * getWormContainer() {return this->wormViewGroup;}

	void setProjectileContainer(ProjectileViewGroup * projectileViewGroup);
	ProjectileViewGroup* getProjectileContainer() {return this->projectileViewGroup;}

	void setExplosionContainer(ExplosionViewGroup * explosionViewGroup);
	ExplosionViewGroup* getExplosionContainer() {return this->explosionViewGroup;}

	void setEart(EartView* eart);
	void setSky(SkyView* sky);
	void setWater(WaterView* water);
	void setTerrain(TerrainView* terrain);
	void setStateBar(StateBarView* stateBar);
	void setMenuWeapon(MenuWeaponView* menuWeapon);
	void setWaterImg(WaterViewImg* waterImg);
	void setWaterSurfImg(std::list<WaterViewImg*> l);

	StateBarView* getStateBar() { return this->stateBar;}

	FigureView* findFigureById(int idElement);
	WormView* findWormById(int idElement);
	ProjectileView* findProjectileById(int idElement);

	void getDestroyEart(int x, int y, int radio);

	~GameView(void);

	void actionMenu();
	void offMenu();
	
	void allowPower();
	void denyPower();

	bool hasClickedMenu(SDL_Point clickPoint);
	bool hasClickedWeapon(SDL_Point clickPoint);
	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);
	Weapon* findWeaponById(int idWeapon);

	void freeProjectileView(int id);
	void freeWormView(int id);

	void setPlayerProgressView(PlayerProgressView * pProgressView);
	void setTimerView(TimerView * timerView);
	void setPowerView(PowerView * powerView);
	void printTimer(int second);
};


#endif /** __VIEW_GROUP_H__ */