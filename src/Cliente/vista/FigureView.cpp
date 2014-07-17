#include "FigureView.h"


FigureView::FigureView(int x, int y, std::string  color, int rotation) : View(x, y, color)
{
	this->mRotation = rotation;
}


FigureView::~FigureView(void)
{

}

std::string FigureView::toString()
{
	return "";
}

void FigureView::update(GameElement* domainElement)
{
}
