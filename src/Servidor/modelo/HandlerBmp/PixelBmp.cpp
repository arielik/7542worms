#include "PixelBmp.h"

//Copy Constructor
PixelBmp::PixelBmp(Position* aPosition, ColorBmp* aColor)
{
    this->position=aPosition;
    this->color = aColor;
}

void PixelBmp::setPosition(Position* newPosition)
{
    this->position = newPosition;
}

void PixelBmp::setColor(ColorBmp* newColor)
{
    this->color=newColor;
}

ColorBmp* PixelBmp::getColor()
{
    return this->color;
}

Position* PixelBmp::getPosition()
{
    return this->position;
}

bool PixelBmp::operator<(PixelBmp* anotherPixelBmp)
{
    return ( *(this->getPosition())< anotherPixelBmp->getPosition());
}
//True:aPixelBmp esta en una columna menor ó por encima de anotherPixelBmp : False
bool PixelBmp::lessPosY(PixelBmp* aPixelBmp, PixelBmp* anotherPixelBmp)
{
    return( Position::lessPosY(aPixelBmp->getPosition(),anotherPixelBmp->getPosition()));
}

PixelBmp::~PixelBmp()
{
    delete this->color;
    delete this->position;
}
