#include "TerrainView.h"


TerrainView::TerrainView(std::string color):View(0, 0, color)
{
}


TerrainView::~TerrainView(void)
{
	std::list<PolygonView*>::iterator it;
	for (it =viewParts.begin(); it != viewParts.end(); ++it) 
	{
		delete (*it);
	}
}

void TerrainView::buildPart(std::list<tPoint> points)
{
	std::list<tPoint>::iterator it;
	PolygonView* aPolygon = new PolygonView(this->getColor());
	for (it =points.begin(); it != points.end(); ++it) 
	{
		aPolygon->addPoint((*it).x, (*it).y);
	}
	
	viewParts.push_back(aPolygon);
	
}

void TerrainView::draw(SDLScreen & screen)
{
	std::list<PolygonView*>::iterator it;
	for (it =viewParts.begin(); it != viewParts.end(); ++it) 
	{
		(*it)->draw(screen);
	}
}
