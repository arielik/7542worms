#pragma once
#ifndef __TERRAIN_VIEW__
#define __TERRAIN_VIEW__
#include "View.h"
#include "figuras/PolygonView.h"

class TerrainView :
	public View
{
	std::list<PolygonView*> viewParts;

public:
	TerrainView(std::string color);
	~TerrainView(void);
	void buildPart(std::list<tPoint> points);
	void draw(SDLScreen & screen);

};

#endif /* __TERRAIN_VIEW__ */
