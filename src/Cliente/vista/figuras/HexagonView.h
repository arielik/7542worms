#pragma once
#include "../FigureView.h"
#ifndef __HEXAGON_VIEW_H_
#define __HEXAGON_VIEW_H_

class HexagonView :
	public FigureView
{
private:
	static const int countPoint = 6;
	tPoint vertexA;
	tPoint vertexB;
	tPoint vertexC;
	tPoint vertexD;
	tPoint vertexE;
	tPoint vertexF;

	Sint16 vertexX[countPoint];
	Sint16 vertexY[countPoint];

	void init();
public:
	HexagonView(std::string  color);
	HexagonView(int x, int y, std::string  color, int rotation);
	void draw(SDLScreen & screen);

	void setVertexA(int x, int y);
	void setVertexB(int x, int y);
	void setVertexC(int x, int y);
	void setVertexD(int x, int y);
	void setVertexE(int x, int y);
	void setVertexF(int x, int y);

	tPoint getVertexA(){return this->vertexA;}

	tPoint getVertexB(){return this->vertexB;}

	tPoint getVertexC(){return this->vertexC;}

	tPoint getVertexD(){return this->vertexD;}

	tPoint getVertexE(){return this->vertexE;}

	tPoint getVertexF(){return this->vertexE;}

	void update(GameElement* domainElement);

	void updateVertex(std::list<std::pair<float,float>> & theVertex);

	~HexagonView(void);

};

#endif /**__HEXAGON_VIEW_H_*/