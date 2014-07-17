#pragma once
#ifndef __POLYGON_VIEW_H_
#define __POLYGON_VIEW_H_
#include <list>
#include "../FigureView.h"
class PolygonView :	public FigureView
{
private:

	Sint16* vertexX;
	Sint16* vertexY;

	std::list<tPoint> m_points;

public:

	PolygonView(std::string  color);
	PolygonView(int x, int y, std::string  color, int rotation);

	void addPoint(int x, int y);

	void draw(SDLScreen & screen);


	~PolygonView(void);
};

#endif /**__POLYGON_VIEW_H_*/