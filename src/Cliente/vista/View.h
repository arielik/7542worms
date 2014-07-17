#pragma once
#ifndef __VIEW_H_
#define __VIEW_H_
#define DEFAULT_COLOR "0xFFFFFFFF"
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <sstream>
#include <iostream>
#include "SDLScreen.h"
#include "GameException.h"
#include "../../utils/Util.h"
#include "TextureManager.h"

class ViewGroup;
class View
{
	int x;
	int y;
	std::string color;
	std::string borderColor;
	
	ViewGroup* parent;

	Uint32 convertToInt(std::string aColor);

	bool scroll;
	
public:
	View(int x, int y, std::string color = DEFAULT_COLOR);

	virtual ~View(void);

	void setParent(ViewGroup* parent) { this->parent = parent; }

	ViewGroup* getParent() { return this->parent; }

	/** Set the view to initial state */
	virtual void clean();
	/** Update the view */
	virtual void update();
	/** Draw on screen */
	virtual void draw(SDLScreen & screen) = 0;

	std::string getColor() { return color;}
	std::string getBorderColor() { return borderColor;}

	Uint32 getColorCod();
	Uint32 getBorderColorCod();
	
	
	void setX(int x) {this->x = x;}
	void setY(int y) {this->y = y;}
	void setColor(std::string color) { this->color = color;}
	void setBorderColor(std::string color) { this->borderColor = color;}

	void swapEndian(Uint32 *colorCode);

	int getX();
	int getY();

	void enableScroll() {this->scroll = true;}
	void disableScroll() {this->scroll = false;}

};


#endif /* defined(__VIEW_H_) */