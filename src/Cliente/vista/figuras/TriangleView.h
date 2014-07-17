#pragma once
#include "../FigureView.h"
#ifndef __TRIANGLE_VIEW_H_
#define __TRIANGLE_VIEW_H_

class TriangleView :
	public FigureView
{
private:

	tPoint vertexA;
	tPoint vertexB;
	tPoint vertexC;

	Sint16 vertexX[3];
	Sint16 vertexY[3];

public:
	TriangleView(std::string  color);
	TriangleView(int x, int y, std::string  color, int rotation);
	void draw(SDLScreen & screen);

	void setVertexA(int x, int y);
	void setVertexB(int x, int y);
	void setVertexC(int x, int y);

	tPoint getVertexA(){return this->vertexA;}

	tPoint getVertexB(){return this->vertexB;}

	tPoint getVertexC(){return this->vertexC;}

	void update(GameElement* domainElement);

	void updateVertex(std::list<std::pair<float,float>> & theVertex);

	~TriangleView(void);

};

#endif /**__TRIANGLE_VIEW_H_*/