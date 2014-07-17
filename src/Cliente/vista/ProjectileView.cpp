#include "ProjectileView.h"


ProjectileView::ProjectileView(int id)
	: View(0, 0), id(id), detonated(false), flip(SDL_FLIP_NONE), drowned(false)
{
	currentSprite = &this->spriteBullet;
	this->widhtLife100 = 25;
	this->widhtLifeCurrent = 25;
	this->lifeInitial = 0;
	this->currentLife = 0; //segundos
	this->enableScroll();
}


ProjectileView::~ProjectileView(void)
{
}


void ProjectileView::clean()
{

}

void ProjectileView::update(GameElement* domainElement)
{
	std::pair<float, float> pointUL = domainElement->getPosition();
	tPoint pointSDL = TextureManager::Instance().convertPointUL2PXSDL(pointUL.first, pointUL.second);
	this->setX(pointSDL.x);
	this->setY(pointSDL.y);
	Log::t("ProjectileView::update accion %s", Util::actionString(domainElement->action).c_str());
	if (domainElement->action == EXPLOSION && !this->detonated) {
		
		this->detonate();
	} else if (domainElement->action == MISSIL_FLYING_RIGHT) {
		this->flip = SDL_FLIP_NONE;
	} else if (domainElement->action == MISSIL_FLYING_LEFT) {
		this->flip = SDL_FLIP_HORIZONTAL;
	} else if (domainElement->action == MISSIL_DELETED) {
		Log::i("ProjectileView:: MISSIL DELETE %d", domainElement->getId());
		this->drowned = true;
	}

	this->calcRemainTime(domainElement->getLife());
}

void ProjectileView::calcRemainTime(int domainLife){
	if (domainLife < this->currentLife) {

		float lifePorcentaje = (float)(domainLife * 100) / (float)(this->getLifeInitial());

		this->widhtLifeCurrent = (int)((lifePorcentaje * (float)this->widhtLife100) / 100.0f);
		if (this->widhtLifeCurrent > this->widhtLife100) {
			this->widhtLifeCurrent = this->widhtLife100;
		}
		if (this->widhtLifeCurrent <= 0) {
			this->widhtLifeCurrent = 1;
		}
		this->currentLife = domainLife;
	}
}
	
void ProjectileView::update() 
{
	this->currentSprite->update();

}

// solo para los sprite
bool ProjectileView::isDetonateDone()
{
	return (detonated && currentSprite->isLastFrame());
}

// solo para los sprite
int ProjectileView::getXCenter()
{
	return this->getX()-(currentSprite->getWidth()/2);
}


int ProjectileView::getYCenter()
{
	return this->getY()-(currentSprite->getHeight()/2);
}

void ProjectileView::detonate()
{
}

void ProjectileView::detonateParcial() {
	this->detonatedParcial = true;
	currentSprite = &this->spriteExplosion;
	SoundManager::Instance().pEXPLOSION1();
}

int ProjectileView::getLifeInitial() { 
	return this->lifeInitial;
} 
void ProjectileView::setLifeInitial(int life) {
	this->lifeInitial = life;
	this->currentLife = life; //segundos
}