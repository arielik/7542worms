#include "ViewGroup.h"


ViewGroup::ViewGroup(int x, int y, int width, int height)
								: View(x, y)
{
	this->setWidth(width);
	this->setHeight(height);
}


ViewGroup::~ViewGroup(void)
{
	std::list<View*>::iterator it;
	for (it = views.begin(); it != views.end(); ++it) 
	{
		delete (*it);
	}
	views.clear();
}

void ViewGroup::add(View* aView)
{
	if (aView!=NULL) {
		this->views.push_back(aView);
		aView->setParent(this);
	}
}

void ViewGroup::clean()
{
	std::list<View*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->clean();
	}
}
	
void ViewGroup::update()
{
	std::list<View*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->update();
	}
}
	
void ViewGroup::draw(SDLScreen & screen)
{
	std::list<View*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->draw(screen);
	}
}
