#pragma once

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include <SDL.h>
#include "RunGame.h"
#include "Contracts\OnClickListener.h"
#include "Contracts\OnMovementListener.h"
#include "Contracts\OnScrollListener.h"
#include "Contracts\OnZoomListener.h"
#include "Contracts\OnActionListener.h"
#include "Contracts\OnChangeListener.h"

class GameController{
	public:
		GameController(void);
		~GameController(void);
		void handlerEvent();
		bool isQuit();
		void destroy();
		void addListener(OnClickListener* c);
		void addListener(OnMovementListener* m);
		void addOnScrollListener(OnScrollListener* s);
		void addOnZoomListener(OnZoomListener* z);

		void remuveListener(OnClickListener* c);
		void remuveListener(OnMovementListener* m);
		void remuveListener(OnScrollListener* s);
		void remuveListener(OnZoomListener* z);


		void addOnClickListener(OnClickListener* c);
		void addOnMovementListener(OnMovementListener* m);
		void remuveOnMovementListener(OnMovementListener* m);
		void remuveOnClickListener(OnClickListener* c);
		void addOnActionListener(OnActionListener* a);
		void remuveOnActionListener(OnActionListener* a);


		void addOnChangeListener(OnChangeListener* coord);
		void remuveOnChangeListener(OnChangeListener* coord);

	private:
		RunGame* rg;
};

#endif 
