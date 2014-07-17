#pragma once

#ifndef __FIGURE_VIEW_GROUP_H__
#define __FIGURE_VIEW_GROUP_H__
#include <list>
#include "FigureView.h"
class FigureViewGroup : public FigureView
{
private:
	int mWidth;
	int mHeight;

	std::map<int, FigureView*> mapViews;

	std::list<FigureView*> views;

public:
	FigureViewGroup(int x, int y, int width, int height);

	/**
	* Find a figure view by id
	* @return aFigureView 
	*/
	FigureView* findById(int idElement);

	/**
	* Add a view
	*/
	void add(FigureView* aView);

	/**
	* Clean every view
	*/
	void clean();
	
	/**
	* Draw each view
	*/
	void draw(SDLScreen & screen);

	void setHeight(int height) {mHeight=height;}
	void setWidth(int width) {mWidth=width;}

	int getHeight() {return mHeight;}
	int getWidth() {return mWidth;}

	~FigureViewGroup(void);
};


#endif /** __FIGURE_VIEW_GROUP_H__ */