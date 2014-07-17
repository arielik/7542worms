#pragma once

#ifndef __BAZOOKA_VIEW_H__
#define __BAZOOKA_VIEW_H__

#include "..\ProjectileView.h"


class BazookaView: public ProjectileView
{

public:
	BazookaView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~BazookaView(void);

};

#endif /** __BAZOOKA_VIEW_H__ **/