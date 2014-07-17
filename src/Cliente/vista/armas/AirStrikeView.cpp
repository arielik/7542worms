#include "AirStrikeView.h"


AirStrikeView::AirStrikeView(int id)
	: ProjectileView(id)
{
	SoundManager::Instance().pAIRSTRIKE();
}


AirStrikeView::~AirStrikeView(void)
{
}


void AirStrikeView::clean()
{

}
	
void AirStrikeView::update() 
{
	if (this->detonated) {
		this->currentSprite->update();
	} else {
		this->currentSprite->setCurrentRow(17);
	}
}

void AirStrikeView::draw(SDLScreen & screen)
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


void AirStrikeView::detonate()
{
	currentSprite = &this->spriteExplosion;
	this->detonated = true;
	SoundManager::Instance().pEXPLOSION1();
}
