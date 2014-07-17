#include "ExplosionView.h"


ExplosionView::ExplosionView(int x, int y)
	: View(x, y)
{
	currentSprite = &this->spriteExplosion;
	this->enableScroll();
	SoundManager::Instance().pEXPLOSION1();
}


ExplosionView::~ExplosionView(void)
{
}


void ExplosionView::clean()
{

}

	
void ExplosionView::update() 
{
	this->currentSprite->update();

}

void ExplosionView::draw(SDLScreen & screen)
{ 
	TextureManager::Instance().drawFrame(currentSprite->getImageId(), 
										this->getXCenter(), 
										this->getYCenter(), 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),
										false, 
										SDL_FLIP_NONE,
										true);

}

int ExplosionView::getXCenter()
{
	return this->getX()-(currentSprite->getWidth()/2);
}


int ExplosionView::getYCenter()
{
	return this->getY()-(currentSprite->getHeight()/2);
}


bool ExplosionView::isDone() {
	return (this->currentSprite->isLastFrame());
}