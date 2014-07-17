#include "BananaView.h"


BananaView::BananaView(int id)
	: ProjectileView(id)
{
}


BananaView::~BananaView(void)
{
}


void BananaView::clean()
{

}
	
void BananaView::update() 
{
	this->currentSprite->update();

}

void BananaView::draw(SDLScreen & screen)
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

	if (!this->detonated) {
		SDL_Rect rect;
		rect.x = this->getX()-10;
		rect.y = this->getY()-22;
		rect.w = this->widhtLifeCurrent;
		rect.h = 5;
		TextureManager::Instance().drawFillRect(screen.getRenderer(),rect,255, 0, 0, 255,true);
	}
	

}


void BananaView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
