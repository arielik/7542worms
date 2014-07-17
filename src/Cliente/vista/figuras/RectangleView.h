#pragma once

#ifndef __RECTANGLE_VIEW_H_
#define __RECTANGLE_VIEW_H_
#include "../FigureView.h"
#include <list>
class RectangleView :	public FigureView
{

private:
	int mWidth;
	int mHeight;


	Sint16 vertexX[4];
	Sint16 vertexY[4];

	tPoint vertexA;
	tPoint vertexB;
	tPoint vertexC;
	tPoint vertexD;

	void init();
public:

	void setHeight(int height) {mHeight=height;}
	void setWidth(int width) {mWidth=width;}

	int getHeight() {return mHeight;}
	int getWidth() {return mWidth;}

	void setVertexA(int x, int y);
	void setVertexB(int x, int y);
	void setVertexC(int x, int y);
	void setVertexD(int x, int y);
	tPoint getVertexA(){return this->vertexA;}
	tPoint getVertexB(){return this->vertexB;}
	tPoint getVertexC(){return this->vertexC;}
	tPoint getVertexD(){return this->vertexD;}

	/**
	* Update Figure view from DomainView object
	*/
	void update(GameElement* domainElement);

	/**
	* Update each vertex
	*/
	void updateVertex(std::list<std::pair<float,float>> & theVertex);


	void draw(SDLScreen & screen);

	/*** @param x y indicate the center of rectangle */
	RectangleView(std::string  color);

	RectangleView(int x, int y, int width, int height, std::string  color, int rotation);
	~RectangleView(void);

};

#endif /** __RECTANGLE_VIEW_H_ */