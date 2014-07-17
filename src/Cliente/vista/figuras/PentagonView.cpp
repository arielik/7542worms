#include "PentagonView.h"


PentagonView::PentagonView(std::string  color) : FigureView(0,0,color,0)
{
	init();
}


PentagonView::PentagonView(int x, int y, std::string  color, int rotation)
									: FigureView(x,y,color,rotation)
{
	init();
}

void PentagonView::init()
{
	this->setVertexA(0,0);
	this->setVertexB(0,0);
	this->setVertexC(0,0);
	this->setVertexD(0,0);
	this->setVertexE(0,0);
}

PentagonView::~PentagonView(void)
{
}

void PentagonView::draw(SDLScreen & screen)
{
	vertexX[0] = vertexA.x;
	vertexX[1] = vertexB.x;
	vertexX[2] = vertexC.x;
	vertexX[3] = vertexD.x;
	vertexX[4] = vertexE.x;

	vertexY[0] = vertexA.y;
	vertexY[1] = vertexB.y;
	vertexY[2] = vertexC.y;
	vertexY[3] = vertexD.y;
	vertexY[4] = vertexE.y;

	TextureManager::Instance().drawPolygon(screen.getRenderer(),
				vertexX,
				vertexY,
				countPoint,
				this->getColorCod(),
				this->getBorderColorCod());
	
}



void PentagonView::update(GameElement* domainElement)
{
	this->updateVertex(domainElement->getVertex());
}

void PentagonView::updateVertex(std::list<std::pair<float,float>> & theVertex)
{
	std::list<std::pair<float,float>>::iterator itVertex;
	int vertexIndex = 1;
	for ( itVertex = theVertex.begin();	itVertex != theVertex.end(); ++itVertex) 
	{
		tPoint sdlPoint = Util::convertPointUL2PXSDL(itVertex->first, itVertex->second);
		int x = sdlPoint.x;
		int y = sdlPoint.y;

		Log::t("Vertex Pentagono index:%d pos:[%d, %d]", vertexIndex, x, y);
 
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
			case 5:
				this->setVertexE(x, y);
				break;
		}
		vertexIndex++;
	}

}



void PentagonView::setVertexA(int x, int y)
{
	this->vertexA.x = x;
	this->vertexA.y = y;
}
void PentagonView::setVertexB(int x, int y)
{
	this->vertexB.x = x;
	this->vertexB.y = y;
}
void PentagonView::setVertexC(int x, int y)
{
	this->vertexC.x = x;
	this->vertexC.y = y;
}

void PentagonView::setVertexD(int x, int y)
{
	this->vertexD.x = x;
	this->vertexD.y = y;
}

void PentagonView::setVertexE(int x, int y)
{
	this->vertexE.x = x;
	this->vertexE.y = y;
}


