#include "DynamiteView.h"


DynamiteView::DynamiteView(int id)
	: ProjectileView(id)
{
}


DynamiteView::~DynamiteView(void)
{
}


void DynamiteView::clean()
{

}
	
void DynamiteView::update() 
{
	this->currentSprite->update();

}

void DynamiteView::draw(SDLScreen & screen)
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
	
		TextureManager::Instance().drawFillRect(screen.getRenderer(),rect, 255, 0, 0, 255,true);
	}

}


void DynamiteView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
