#pragma once

#ifndef __BANANA_VIEW_H__
#define __BANANA_VIEW_H__

#include "..\ProjectileView.h"


class BananaView: public ProjectileView
{

public:
	BananaView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~BananaView(void);

};

#endif /** BananaView **/