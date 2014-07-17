#pragma once
#ifndef __GAME_VIEW_BUILDER_H__
#define __GAME_VIEW_BUILDER_H__
#include "SkyView.h"
#include "ViewGroup.h"
#include "GameView.h"
#include "FigureViewGroup.h"
#include "ExplosionViewGroup.h"
#include "ExplosionView.h"
#include "WaterView.h"
#include "figuras/RectangleView.h"
#include "figuras/PentagonView.h"
#include "figuras/HexagonView.h"
#include "figuras/PolygonView.h"
#include "figuras/CircleView.h"
#include "figuras/EllipseView.h"
#include "figuras/TriangleView.h"
#include "TerrainView.h"
#include "WormView.h"
#include "ProjectileView.h"
#include "MenuWeaponView.h"
#include "WaterViewImg.h"
#include "armas/GrenadeView.h"
#include "armas/HolyView.h"
#include "armas/BazookaView.h"
#include "armas/DynamiteView.h"
#include "armas/DonkeyView.h"
#include "armas/AirStrikeView.h"
#include "armas/BananaView.h"
#include "armas/SheepView.h"
#include "PlayerProgressView.h"
#include "EartView.h"
#include "SDLScreen.h"
#include "SpriteConfigurator.h"
#include "../../utils/Util.h"
#include "../../utils/Constantes/Constantes.h"
#include "../controlador/GameController.h"
#include "../modelo/GameDomain.h"

class GameViewBuilder 
{
	
	GameView* gameView;
	SDLScreen * screen;
	std::string playerID;
	GameDomain* domain;

public:

	GameDomain* getDomain(){ return this->domain;}

	GameViewBuilder(GameDomain* domain, SDLScreen * screen);
	~GameViewBuilder(void);

	std::string getPlayerID() { return this->playerID; }

	WormView* createWorm(GameElement * domainElement);

	ProjectileView* createBullet(GameElement * domainElement, int type);

	ExplosionView* createExplosion(float x, float y, int radio);

	void setPlayerID(std::string  playerID){ this->playerID = playerID; }
	
	void buildContainer();

	void buildProjectileContainer();

	void buildExplosionContainter();

	void buildSky();

	void buildFigures();

	void buildWater();

	void buildTerrain();

	void buildCharacters();

	void buildEart();

	void buildStateBar();

	void buildPlayerProgress();

	void buildPower(GameController* cController);

	void buildTimer();

	void buildMenuWeapon();

	void buildWaterImg();

	void buildWaterSurfImg();

	GameView* getGameView() { return this->gameView;} 

};

#endif /**__GAME_VIEW_BUILDER_H__*/