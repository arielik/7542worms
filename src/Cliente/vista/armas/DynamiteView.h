#pragma once

#ifndef __DYNAMITE_VIEW_H__
#define __DYNAMITE_VIEW_H__

#include "..\ProjectileView.h"


class DynamiteView: public ProjectileView
{

public:
	DynamiteView(int id);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void detonate();

	~DynamiteView(void);

};

#endif /** __DYNAMITE_VIEW_H__ **/