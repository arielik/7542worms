#ifndef __RUNGAME__
#define __RUNGAME__
#include <SDL.h>
#include "Entity/PartialScreen.h"
#include "../../utils/Log.h"
#include <vector>
#include "Entity/Over.h"
#include "Entity/Click.h"
#include "Entity/Zoom.h"
#include "Entity/Move.h"
#include "Entity/Change.h"
#include "Entity\Action.h"
#include "Contracts/Notifiable.h"
#include "Entity/CollectionEvent.h"
#include "..\..\utils\Timer.h"

using namespace std;

enum Screen {QUADRANT_1, QUADRANT_2, QUADRANT_3, QUADRANT_4,
			 QUADRANT_5, QUADRANT_6, QUADRANT_7, QUADRANT_8,
			 QUADRANT_9};

class RunGame{
	public:
		void call();
		bool isQuit();
		void destroy();
		void addCallFromSDL();
		void addCallFromOver();
		static RunGame* getInstance();

	private:
		RunGame(void);
		~RunGame(void);
		int oldTime, newTime, factor;
		Timer timer;
		bool quit;
		const Uint8* m_keys;
		void handleEvents(SDL_Event* e);
		bool isValidKey(SDL_Event* e);
		bool isKeyPress(SDL_Event* e, SDL_Scancode sc);
		void execute(SDL_Event* e, const Uint8* keys);
		static RunGame* runGame;
		void updateMouse();
		void iniEvent();
		PartialScreen* callScreen;
		void detectMouse();
		void loadQuadrantFactory();
		vector<PartialScreen*> screems;
		Side GetCursorLook(int xr, int yr);
		void detectWheel(SDL_Event* e);
		void detectClick();
		void detectClickLeft();
		void detectClickRight();
		void detectChange();
		void detectMovem(SDL_Event* e);
		void detectMovementAim();
		void detectMovem(Move* mv, int value, SDL_Event* e);
		int getFactor(float time);
		int WIDTH, HIGHT;
		CollectionEvent listEvent;
		bool isTimerRun;
};

#endif