#include "ViewMock.h"


ViewMock::ViewMock(void)
{
	SDL_Init(SDL_INIT_VIDEO	| 
		     SDL_INIT_EVENTS| 
			 SDL_INIT_TIMER);
	viewMock = NULL;
}


ViewMock::~ViewMock(void)
{
	if(viewMock){
		SDL_DestroyWindow(viewMock);
	}
	SDL_Quit();
}

void ViewMock::createWorld(string title){
	viewMock = SDL_CreateWindow(title.c_str(),
						50, 50, 600, 400,
						SDL_WINDOW_SHOWN);
	return;
}

