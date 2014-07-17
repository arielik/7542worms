#pragma once

#ifndef __HOLY_VIEW_H__
#define __HOLY_VIEW_H__

#include "..\ProjectileView.h"


class HolyView: public ProjectileView
{

public:
	HolyView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~HolyView(void);

};

#endif /** __HOLY_VIEW_H__ **/