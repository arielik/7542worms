#pragma once
#ifndef __ELLIPSE_VIEW_H_
#define __ELLIPSE_VIEW_H_

#include "../FigureView.h"
class EllipseView : 	public FigureView
{
private:
	int radioX;
	int radioY;

public:
	EllipseView(std::string  color);

	int getRadioX() {return radioX;}
	void setRadioX(int radioX) {this->radioX = radioX;}

	int getRadioY() {return radioY;}
	void setRadioY(int radioY) {this->radioY = radioY;}

	void draw(SDLScreen & screen);

	void updateRadius(float radiusModel);

	/**
	* Update Figure view from DomainView object
	*/
	void update(GameElement* domainElement);

	/**
	* Update Figure view from position domains
	*/
	void updatePositions(std::pair<float, float> positions);

	~EllipseView(void);
};

#endif /** __ELLIPSE_VIEW_H_ */

