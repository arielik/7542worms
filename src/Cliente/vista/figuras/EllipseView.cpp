#include "EllipseView.h"


EllipseView::EllipseView(std::string  color): 
						FigureView(0,0,color,0)
{
	this->setRadioX(10);
	this->setRadioY(15);
}


EllipseView::~EllipseView(void)
{
}

void EllipseView::draw(SDLScreen & screen) 
{
	TextureManager::Instance().drawEllipse(screen.getRenderer(),
						this->getX(),
						this->getY(),
						this->getRadioX(),
						this->getRadioY(),
						this->getColorCod(),
						this->getBorderColorCod());

}

void EllipseView::update(GameElement* domainElement)
{
	this->updatePositions(domainElement->getPosition());
}

void EllipseView::updateRadius(float radiusModel)
{
	Log::t("Escalamos radios del circulo");

	std::pair<float, float> scale_factor = Util::getTransformFromU2PX();
	float factorX = scale_factor.first;
	float factorY = scale_factor.second;
			
	Log::t("Radio circulo ANTES de escalar: %f", radiusModel);

	float radiusX = radiusModel * factorX;
	float radiusY = radiusModel * factorY;
	
	Log::t("Radio circulo DESPUES de escalar en x y: %f, %f", radiusX, radiusY);

	this->setRadioX(radiusX);
	this->setRadioY(radiusY);
}

void EllipseView::updatePositions(std::pair<float, float> positions)
{
	Log::t("Posicion del Elipse x y Modelo: [%fUL, %fUL]", positions.first, positions.second);
	tPoint sdlPoint = Util::convertPointUL2PXSDL(positions.first, positions.second);
	
	this->setX(sdlPoint.x);
	this->setY(sdlPoint.y);
	Log::t("Posicion del Elipse x y: [%dpx, %dpx]", sdlPoint.x, sdlPoint.y);
}

