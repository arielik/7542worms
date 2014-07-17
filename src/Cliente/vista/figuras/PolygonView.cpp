#include "PolygonView.h"

PolygonView::PolygonView(std::string  color) : FigureView(0, 0, color, 0)
{
	vertexX = 0;
	vertexY = 0;
}


PolygonView::PolygonView(int x, int y, std::string  color, int rotation)
								: FigureView(x,y,color,rotation)
{
	vertexX = 0;
	vertexY = 0;
}

void PolygonView::addPoint(int x, int y)
{
	if (vertexX) 
		delete [] vertexX;
	if (vertexY) 
		delete [] vertexY;

	tPoint newPoint;
	newPoint.x = x;
	newPoint.y = y;
	m_points.push_back(newPoint);

	vertexX = new Sint16[m_points.size()];
	vertexY = new Sint16[m_points.size()];
	
	std::list<tPoint>::iterator  it;

	int index=0;
	for (it = m_points.begin(); it != m_points.end(); ++it)  
	{
		vertexX[index] = (*it).x;
		vertexY[index] = (*it).y;
		index++;
	}
}

void PolygonView::draw(SDLScreen & screen) 
{
	TextureManager::Instance().drawPolygon(screen.getRenderer(),
				vertexX,
				vertexY,
				m_points.size(),
				this->getColorCod(),
				this->getBorderColorCod());

}

PolygonView::~PolygonView(void)
{
	if (vertexX) delete [] vertexX;
	if (vertexY) delete [] vertexY;
	vertexX = 0;
	vertexY = 0;

}
