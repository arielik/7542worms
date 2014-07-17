#include "RectangleView.h"


RectangleView::RectangleView(std::string  color): FigureView(0,0,color,0)
{
	init();
}
void RectangleView::init()
{
	vertexA.x = 0;
	vertexA.y = 0;
	vertexB.x = 0;
	vertexB.y = 0;
	vertexC.x = 0;
	vertexC.x = 0;
	vertexD.y = 0;
	vertexD.y = 0;
}

/**DEPRECATED*/
RectangleView::RectangleView(int x, int y, int width, int height, std::string  color, int rotation):
								FigureView(x,y,color,rotation)
{
	this->setWidth(width);
	this->setHeight(height);
	init();
}


RectangleView::~RectangleView(void)
{
}


void RectangleView::draw(SDLScreen & screen)
{
	vertexX[0] = vertexA.x;
	vertexX[1] = vertexB.x;
	vertexX[2] = vertexC.x;
	vertexX[3] = vertexD.x;
	vertexY[0] = vertexA.y;
	vertexY[1] = vertexB.y;
	vertexY[2] = vertexC.y;
	vertexY[3] = vertexD.y;
	TextureManager::Instance().drawPolygon(screen.getRenderer(),
				vertexX,
				vertexY,
				4,
				this->getColorCod(),
				this->getBorderColorCod());
}

void RectangleView::update(GameElement* domainElement)
{
	this->updateVertex(domainElement->getVertex());
}

void RectangleView::updateVertex(std::list<std::pair<float,float>> & theVertex)
{
	std::list<std::pair<float,float>>::iterator itVertex;
	int vertexIndex = 1;
	for ( itVertex = theVertex.begin();	itVertex != theVertex.end(); ++itVertex) 
	{
		tPoint sdlPoint = Util::convertPointUL2PXSDL(itVertex->first, itVertex->second);
		int x = sdlPoint.x;
		int y = sdlPoint.y;
		Log::t("Vertex Rectangulo id:%d pos:[%d, %d]", vertexIndex, x, y);
 
		switch (vertexIndex)
		{
			case 1:
				this->setVertexA(x, y);
				break;
			case 2:
				this->setVertexB(x, y);
				break;
			case 3:
				this->setVertexC(x, y);
				break;
			case 4:
				this->setVertexD(x, y);
				break;
		}
		vertexIndex++;
	}

}

void RectangleView::setVertexA(int x, int y)
{
	this->vertexA.x = x;
	this->vertexA.y = y;
}
void RectangleView::setVertexB(int x, int y)
{
	this->vertexB.x = x;
	this->vertexB.y = y;
}
void RectangleView::setVertexC(int x, int y)
{
	this->vertexC.x = x;
	this->vertexC.y = y;
}

void RectangleView::setVertexD(int x, int y)
{
	this->vertexD.x = x;
	this->vertexD.y = y;
}
