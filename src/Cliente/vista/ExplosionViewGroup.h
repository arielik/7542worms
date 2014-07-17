#pragma once

#ifndef __EXPLOSION_VIEW_GROUP_H__
#define __EXPLOSION_VIEW_GROUP_H__
#include <list>
#include "ExplosionView.h"
class ExplosionViewGroup : public View
{
private:

	std::list<ExplosionView*> views;

public:
	ExplosionViewGroup(int x, int y);

	/**
	* Add a view
	*/
	void add(ExplosionView* aView);

	/**
	* Clean every view
	*/
	void clean();
	
	/**
	* Update every wormView
	*/
	void update();

	/**
	* Draw each view
	*/
	void draw(SDLScreen & screen);

	~ExplosionViewGroup(void);
};


#endif /** __FIGURE_VIEW_GROUP_H__ */