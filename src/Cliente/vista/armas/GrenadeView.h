#pragma once

#ifndef __GRENADE_VIEW_H__
#define __GRENADE_VIEW_H__

#include "..\ProjectileView.h"


class GrenadeView: public ProjectileView
{

public:
	GrenadeView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~GrenadeView(void);

};

#endif /** __GRENADE_VIEW_H__ **/