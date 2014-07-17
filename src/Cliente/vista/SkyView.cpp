#include "SkyView.h"


SkyView::SkyView(std::string imageId)
				: View(0, 0), imageId(imageId)
{
	this->enableScroll();
}


SkyView::~SkyView(void)
{
}


void SkyView::clean()
{

}
	
void SkyView::update() 
{
	sprites["nuve"].update();
}

void SkyView::draw(SDLScreen & screen)
{
	TextureManager::Instance().drawBackground(imageId.c_str(),
								screen.getRenderer());

	Sprite* currentSprite = &sprites["nuve"];
	TextureManager::Instance().drawFrame("nuve", 
										getX() + 50, 
										getY() + 50, 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),
										false,
										SDL_FLIP_NONE,
										true);

	TextureManager::Instance().drawFrame("nuve", 
										getX() + 500, 
										getY() + 50, 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),
										false,
										SDL_FLIP_NONE,
										true);

	TextureManager::Instance().drawFrame("nuve", 
										getX() + 700, 
										getY() + 50, 
										currentSprite->getWidth(), 
										currentSprite->getHeight(), 
										currentSprite->getCurrentRow(), 
										currentSprite->getCurrentFrame(), 
										screen.getRenderer(),
										false,
										SDL_FLIP_NONE,
										true);

}
