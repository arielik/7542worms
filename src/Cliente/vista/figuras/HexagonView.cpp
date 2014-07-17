#include "HexagonView.h"


HexagonView::HexagonView(std::string  color) : FigureView(0,0,color,0)
{
	init();
}


HexagonView::HexagonView(int x, int y, std::string  color, int rotation)
									: FigureView(x,y,color,rotation)
{
	init();
}

void HexagonView::init()
{
	this->setVertexA(0,0);
	this->setVertexB(0,0);
	this->setVertexC(0,0);
	this->setVertexD(0,0);
	this->setVertexE(0,0);
	this->setVertexF(0,0);
}

HexagonView::~HexagonView(void)
{
}

void HexagonView::draw(SDLScreen & screen)
{
	vertexX[0] = vertexA.x;
	vertexX[1] = vertexB.x;
	vertexX[2] = vertexC.x;
	vertexX[3] = vertexD.x;
	vertexX[4] = vertexE.x;
	vertexX[5] = vertexF.x;

	vertexY[0] = vertexA.y;
	vertexY[1] = vertexB.y;
	vertexY[2] = vertexC.y;
	vertexY[3] = vertexD.y;
	vertexY[4] = vertexE.y;
	vertexY[5] = vertexF.y;
	
	TextureManager::Instance().drawPolygon(screen.getRenderer(),
				vertexX,
				vertexY,
				countPoint,
				this->getColorCod(),
				this->getBorderColorCod());
	/*filledPolygonColor(screen.getRenderer(),
				vertexX,
				vertexY,
				countPoint,
				this->getColorCod());

	polygonColor(screen.getRenderer(),
				vertexX,
				vertexY,
				countPoint,
				this->getBorderColorCod());*/
}



void HexagonView::update(GameElement* domainElement)
{
	this->updateVertex(domainElement->getVertex());
}

void HexagonView::updateVertex(std::list<std::pair<float,float>> & theVertex)
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
			case 6:
				this->setVertexF(x, y);
				break;
		}
		vertexIndex++;
	}

}



void HexagonView::setVertexA(int x, int y)
{
	this->vertexA.x = x;
	this->vertexA.y = y;
}
void HexagonView::setVertexB(int x, int y)
{
	this->vertexB.x = x;
	this->vertexB.y = y;
}
void HexagonView::setVertexC(int x, int y)
{
	this->vertexC.x = x;
	this->vertexC.y = y;
}

void HexagonView::setVertexD(int x, int y)
{
	this->vertexD.x = x;
	this->vertexD.y = y;
}

void HexagonView::setVertexE(int x, int y)
{
	this->vertexE.x = x;
	this->vertexE.y = y;
}

void HexagonView::setVertexF(int x, int y)
{
	this->vertexF.x = x;
	this->vertexF.y = y;
}
