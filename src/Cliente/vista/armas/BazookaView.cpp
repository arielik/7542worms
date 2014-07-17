#include "BazookaView.h"


BazookaView::BazookaView(int id)
	: ProjectileView(id)
{
}


BazookaView::~BazookaView(void)
{
}


void BazookaView::clean()
{

}
	
void BazookaView::update() 
{
	this->currentSprite->update();

}

void BazookaView::draw(SDLScreen & screen)
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
										this->flip,
										true);
}


void BazookaView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
