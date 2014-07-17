#include "Activity.h"


Activity::Activity(SDLScreen & screen): m_screen(screen)
{
	this->aView = 0;
}

Activity::~Activity(void)
{

}


void Activity::update() 
{
	this->aView->update();	
}
void Activity::render() 
{
	this->clear();

	//m_screen.setTarget(1);
	this->aView->draw(m_screen);	

	this->m_screen.render();
}

void Activity::clear()
{
	this->m_screen.clear();
}

void Activity::stop()
{
	
}

void Activity::setContentView(ViewGroup * newView)
{
	this->aView = newView;
}

