#include "TriangleView.h"


TriangleView::TriangleView(std::string  color) : FigureView(0,0,color,0)
{
	this->setVertexA(0,0);
	this->setVertexB(0,0);
	this->setVertexC(0,0);
}


TriangleView::TriangleView(int x, int y, std::string  color, int rotation)
									: FigureView(x,y,color,rotation)
{
	this->setVertexA(0,0);
	this->setVertexB(0,0);
	this->setVertexC(0,0);
}


TriangleView::~TriangleView(void)
{
}

void TriangleView::draw(SDLScreen & screen)
{
	vertexX[0] = vertexA.x;
	vertexX[1] = vertexB.x;
	vertexX[2] = vertexC.x;
	vertexY[0] = vertexA.y;
	vertexY[1] = vertexB.y;
	vertexY[2] = vertexC.y;
	
	TextureManager::Instance().drawPolygon(screen.getRenderer(),
				vertexX,
				vertexY,
				3,
				this->getColorCod(),
				this->getBorderColorCod());
}



void TriangleView::update(GameElement* domainElement)
{
	this->updateVertex(domainElement->getVertex());
}

void TriangleView::updateVertex(std::list<std::pair<float,float>> & theVertex)
{
	std::list<std::pair<float,float>>::iterator itVertex;
	int vertexIndex = 1;
	for ( itVertex = theVertex.begin();	itVertex != theVertex.end(); ++itVertex) 
	{
		tPoint sdlPoint = Util::convertPointUL2PXSDL(itVertex->first, itVertex->second);
		int x = sdlPoint.x;
		int y = sdlPoint.y;

		Log::t("Vertex Triangulo id:%d pos:[%d, %d]", vertexIndex, x, y);
 
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
		}
		vertexIndex++;
	}

}



void TriangleView::setVertexA(int x, int y)
{
	this->vertexA.x = x;
	this->vertexA.y = y;
}
void TriangleView::setVertexB(int x, int y)
{
	this->vertexB.x = x;
	this->vertexB.y = y;
}
void TriangleView::setVertexC(int x, int y)
{
	this->vertexC.x = x;
	this->vertexC.y = y;
}



