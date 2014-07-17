#include "Shape.h"

Shape::Shape(){

}

Shape::Shape(int x, int y,
	int width, int height){
	this->x = x; this->y = y;
	this->width = width;
	this->height = height;
}

Shape::~Shape(){}

pair<int, int> Shape::getPosition(){
	return pair<int, int>(x, y);
}

pair<int, int> Shape::getDimension(){
	return pair<int, int>(width, height);
}


