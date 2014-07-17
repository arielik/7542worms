#include "GrenadeView.h"


GrenadeView::GrenadeView(int id)
	: ProjectileView(id)
{
}


GrenadeView::~GrenadeView(void)
{
}


void GrenadeView::clean()
{

}
	
void GrenadeView::update() 
{
	this->currentSprite->update();

}

void GrenadeView::draw(SDLScreen & screen)
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


void GrenadeView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
