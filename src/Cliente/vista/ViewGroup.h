#pragma once

#ifndef __VIEW_GROUP_H__
#define __VIEW_GROUP_H__
#include <list>
#include "View.h"
class ViewGroup : 	public View
{
private:
	int mWidth;
	int mHeight;

	std::list<View*> views;

public:
	ViewGroup(int x, int y, int width, int height);

	/**
	* Add a view
	*/
	void add(View* aView);

	/**
	* Clean every view
	*/
	void clean();
	
	/**
	* Update each view
	*/
	void update();
	
	/**
	* Draw each view
	*/
	void draw(SDLScreen & screen);

	void setHeight(int height) {mHeight=height;}
	void setWidth(int width) {mWidth=width;}

	int getHeight() {return mHeight;}
	int getWidth() {return mWidth;}

	~ViewGroup(void);
};


#endif /** __VIEW_GROUP_H__ */