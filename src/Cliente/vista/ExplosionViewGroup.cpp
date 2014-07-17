#include "ExplosionViewGroup.h"


ExplosionViewGroup::ExplosionViewGroup(int x, int y)
								: View(x, y)
{

}

ExplosionViewGroup::~ExplosionViewGroup(void)
{
	std::list<ExplosionView*>::iterator it;
	for (it = views.begin(); it != views.end(); ++it) 
	{
		delete (*it);
	}
	views.clear();
}

void ExplosionViewGroup::add(ExplosionView* aView)
{
	this->views.push_back(aView);
}

void ExplosionViewGroup::update()
{
	std::list<ExplosionView*> auxExplosion;

	std::list<ExplosionView*>::iterator itAux;
	for (itAux = this->views.begin(); itAux != this->views.end(); ++itAux) {
		if ((*itAux)->isDone()){
			delete (*itAux);
		} else {
			auxExplosion.push_back(*itAux);
		}
	}

	if (auxExplosion.size() <= this->views.size()) {
		this->views = auxExplosion;
	}

	std::list<ExplosionView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->update();
	}
}

void ExplosionViewGroup::clean()
{
	std::list<ExplosionView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->clean();
	}
}
	
void ExplosionViewGroup::draw(SDLScreen & screen)
{
	std::list<ExplosionView*>::iterator it;
	for (it = this->views.begin(); it != this->views.end(); ++it) {
		(*it)->draw(screen);
	}

	// TODO: ver cual eliminar
}
