#pragma once

#ifndef __VIEWMOCK__
#define __VIEWMOCK__

#include "SDL.h"
#include <iostream>

using namespace std;

class ViewMock
{
public:
	ViewMock(void);
	~ViewMock(void);
	void createWorld(string title);

private:
	SDL_Window* viewMock;
};

#endif /*__VIEWMOCK__*/

