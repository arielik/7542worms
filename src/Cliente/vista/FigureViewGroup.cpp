#include "FigureViewGroup.h"


FigureViewGroup::FigureViewGroup(int x, int y, int width, int height)
								: FigureView(x, y,"",0)
{
	this->setWidth(width);
	this->setHeight(height);
}


FigureViewGroup::~FigureViewGroup(void)
{
	std::list<FigureView*>::iterator it;
	for (it = views.begin(); it != views.end(); ++it) 
	{
		delete (*it);
	}
	views.clear();
	mapViews.clear();
}

void FigureViewGroup::add(FigureView* aView)
{
	this->views.push_back(aView);
	this->mapViews[aView->getId()]=aView;
}

void FigureViewGroup::clean()
{
	std::list<FigureView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->clean();
	}
}
	

	
void FigureViewGroup::draw(SDLScreen & screen)
{
	std::list<FigureView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->draw(screen);
	}
}

FigureView* FigureViewGroup::findById(int idElement)
{
	if (mapViews.find(idElement) != mapViews.end())
	{
		return mapViews[idElement];
	} 
	else 
	{
		std::stringstream msg;
		msg<<"FigureView: not found view by id: "<<idElement;
		throw GameException(msg.str());
	}
}