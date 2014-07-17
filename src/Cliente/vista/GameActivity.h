#pragma once
#ifndef __GAME_ACTIVITY_H_
#define __GAME_ACTIVITY_H_
#include <iostream>
#include "Activity.h"
#include "GameViewBuilder.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "ProjectileView.h"

#include "../../Servidor/modelo/GameLevel.h"
#include <SDL_rect.h>
#include "../../utils/Util.h"
#include "Camera.h"
#include "../Updater.h"
#include "Weapon.h"
#include "AimView.h"


enum CallClient {CALL_NULL,
	             CALL_MOVE, 
				 CALL_SHOOT, 
				 CALL_UNWEAPON,
				 CALL_WEAPON,
				 CALL_STOPWORM,
                 CALL_MOVEVIEW};
typedef struct {
	int id;
	float x;
	float y;
	int angle;
	int factor;
	tDirection dim;
	Movement moveView;
} ActionWorm;

class GameActivity : public Activity, 
					 public OnClickListener, 
					 public OnMovementListener,
					 public OnActionListener
{
private:

	GameController* cController;
	GameViewBuilder* builder;

	Updater updater;
	
	std::string playerId;

	/*para calcular el zoom*/
	void calcRectPosition(SDL_Rect& wormRect,WormView *aWorm);

	bool isMyTurn,
		 isRightAim,
		 isLeftAim;

	CallClient auxCallLog;
	
	int xHmissile, yHmissile;

	WeaponId idWeapon;

	AimView* aimView;

	std::vector<int> futureFree;
	std::vector<int> futureFreeWorm;

	bool afterShoot;
	void iniState();
	void actionMenu();
	void offMenu();
	bool isObjetive();
	void iniHmissile();
	void runGarbarageColector();
	void dettachWorm();
public:

	int wormIdDesSelected;
	int wormIdSelected;

	GameActivity(SDLScreen & screen, GameDomain* domain, GameController* cController, std::string playerId, Updater & updater);

	void buildView();

	void stop();

	void clear();

	void update();

	void onCreate();

	void setListeners(SDLScreen & screen);

	void OnClick(ClickEvent e);

	void OnMovement(MovementEvent e);

	void OnAction(ActionEvent e);

	void deselectPreviewsWorm();

	void deselectPreviewsWeapon();

	void doExplotion(float x, float y, float radio);

	void selectWorm(WormView* aWorm);

	bool hasClickedWorm(SDL_Point clickPoint);

	bool hasClickedMenu(SDL_Point clickPoint);
	
	bool hasClickedWeapon(SDL_Point clickPoint);

	int getWormIdSelected() {return this->wormIdSelected;}

	WormView* retrieveWormClicked(SDL_Point clickPoint);

	Weapon* retrieveWeaponClicked(SDL_Point clickPoint);

	void buildNewWorms(std::string playerID, int id, int x, int y) ;

	void buildProjectile(int idElement, float x, float y, int type, int life, Movement action);

	void buildExplosion( float x, float y, int type, int radio);

	bool isThisClientOwner(int wormId);

	bool isAlive(int wormId);

	void setMessageView(std::string msg);

	void showMessageError(std::string msg);

	void showMessageInfo(std::string msg);

	void otherTurn(std::string playerId);

	void endMyTurn();

	void beginMyTurn();

	void ActionResult(CallClient call, Playable* p, ActionWorm *aw);

	bool validateWormBeforeCall();

	bool validateWormAlive();

	bool validateWormLastWords();

	void allowPower();

	void denyPower();

	bool isWeaponWithOutPower();

	void printTimer(int second);

	void linkWormWithWeapon(SDL_Point clickPointScreen);
	void linkWorm(SDL_Point clickPoint);

	void ActionResultLog(CallClient call, Playable* p, ActionWorm *aw);

	~GameActivity(void);
};

#endif /* defined(__GAME_ACTIVITY_H_) */

