#pragma once
#ifndef __CIRCLE_VIEW_H_
#define __CIRCLE_VIEW_H_

#include "../FigureView.h"
class CircleView : 	public FigureView
{
private:
	int radio;

	

public:
	CircleView(std::string  color);

	int getRadio() {return radio;}
	void setRadio(int radio) {this->radio = radio;}

	void draw(SDLScreen & screen);

	/**
	* Update Figure view from DomainView object
	*/
	void update(GameElement* domainElement);

	/**
	* Update Figure view from position domains
	*/
	void updatePositions(std::pair<float, float> positions);

	~CircleView(void);
};

#endif /** __CIRCLE_VIEW_H_ */

