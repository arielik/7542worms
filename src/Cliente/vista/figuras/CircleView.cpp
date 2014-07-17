#include "CircleView.h"


CircleView::CircleView(std::string  color): 
						FigureView(0,0,color,0)
{
	this->setRadio(10);
}


CircleView::~CircleView(void)
{
}

void CircleView::draw(SDLScreen & screen) 
{
	TextureManager::Instance().drawCircle(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadio(),
						this->getColorCod(),
						this->getBorderColorCod());
}

void CircleView::update(GameElement* domainElement)
{
	this->updatePositions(domainElement->getPosition());
}

void CircleView::updatePositions(std::pair<float, float> positions)
{

	std::pair<float, float> scale_factor = Util::getTransformFromU2PX();
	float factorX = scale_factor.first;
	float factorY = scale_factor.second;
			
	Log::t("Factor x y: [%f, %f]", factorX, factorY);

	int posX = positions.first * factorX;
	int posY = positions.second * factorY;
	
	this->setX(posX);
	this->setY(posY);
	Log::t("Posicion x y: [%dpx, %dpx]", posX, posY);
}

