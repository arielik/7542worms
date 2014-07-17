#include "WaterView.h"


WaterView::WaterView(int height, std::string  color)
							: View(0, 0, color)
{
	this->setHeight(height);
}


WaterView::~WaterView(void)
{

}


void WaterView::draw(SDLScreen & screen)
{
	int x1 = 0;
	int y1 = this->getParent()->getHeight() - this->getHeight();
	int x2 = this->getParent()->getWidth();
	int y2 = this->getParent()->getHeight();
	TextureManager::Instance().drawBox(screen.getRenderer(),
								x1, y1,
								x2, y2, this->getColorCod());
}

