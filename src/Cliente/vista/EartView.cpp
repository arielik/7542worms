#include "EartView.h"


EartView::EartView(std::string imageId):View(0, 0), imageId(imageId)
{
	this->counter = 0;
}


EartView::~EartView(void)
{

}

void EartView::draw(SDLScreen & screen)
{
	if (this->counter > 10)
	{
		this->counter = 0;
		this->drawExplotion(50, 50, 2);
	}
	this->counter++;
	TextureManager::Instance().drawScrollableBackground(imageId, screen.getRenderer());
}

void EartView::drawExplotion(int x, int y, int radius)
{

	Uint32 pixel = 0x00000000;

	std::pair<int, int> dimension = TextureManager::Instance().getDimension(this->imageId);
	
	SDL_Rect scenario;
	scenario.x=0;
	scenario.y=0;
	scenario.w=dimension.first;
	scenario.h=dimension.second;

	SDL_Rect dimRectCircle;
	dimRectCircle.x=x-radius;
	dimRectCircle.y=y-radius;
	dimRectCircle.w=radius*2;
	dimRectCircle.h=radius*2;
	if (TextureManager::Instance().intersectRects(dimRectCircle, scenario)) {
		TextureManager::Instance().fillCircleOn(this->imageId, x, y, radius*2, pixel);
	}
	
}
