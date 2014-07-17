#pragma once

#ifndef __AIR_STRIKE_VIEW_H__
#define __AIR_STRIKE_VIEW_H__

#include "..\ProjectileView.h"


class AirStrikeView: public ProjectileView
{

public:
	AirStrikeView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~AirStrikeView(void);

};

#endif /** __AIR_STRIKE_VIEW_H__ **/