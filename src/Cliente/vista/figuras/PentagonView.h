#pragma once
#include "../FigureView.h"
#ifndef __PENTAGON_VIEW_H_
#define __PENTAGON_VIEW_H_

class PentagonView :
	public FigureView
{
private:
	static const int countPoint = 5;
	tPoint vertexA;
	tPoint vertexB;
	tPoint vertexC;
	tPoint vertexD;
	tPoint vertexE;

	Sint16 vertexX[countPoint];
	Sint16 vertexY[countPoint];

	void init();
public:
	PentagonView(std::string  color);
	PentagonView(int x, int y, std::string  color, int rotation);
	void draw(SDLScreen & screen);

	void setVertexA(int x, int y);
	void setVertexB(int x, int y);
	void setVertexC(int x, int y);
	void setVertexD(int x, int y);
	void setVertexE(int x, int y);

	tPoint getVertexA(){return this->vertexA;}

	tPoint getVertexB(){return this->vertexB;}

	tPoint getVertexC(){return this->vertexC;}

	tPoint getVertexD(){return this->vertexD;}

	tPoint getVertexE(){return this->vertexE;}

	void update(GameElement* domainElement);

	void updateVertex(std::list<std::pair<float,float>> & theVertex);

	~PentagonView(void);

};

#endif /**__PENTAGON_VIEW_H_*/