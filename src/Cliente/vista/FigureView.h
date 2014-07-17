#pragma once
#ifndef __FIGURE_VIEW_H_
#define __FIGURE_VIEW_H_
#include "View.h"
#include "TextureManager.h"
#include "../../Servidor/modelo/GameElement.h"

class FigureView : 	public View
{
private:
	int mRotation;

	int id;

public:
	int getRotation() {return mRotation;}
	void setRotation(int rotation) {mRotation = rotation;}
	FigureView(int x, int y, std::string  color, int rotation);
	~FigureView(void);


	virtual void update(GameElement* domainElement);

	void setId(int id) {this->id = id;}
	int getId() { return id;}

	virtual std::string toString();
};



#endif /* defined(__FIGURE_VIEW_H_) */

