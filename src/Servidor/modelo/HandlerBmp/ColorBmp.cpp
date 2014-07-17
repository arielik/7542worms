#include "ColorBmp.h"

//Copy Constructor
ColorBmp::ColorBmp(ColorBmp* aColor)
{
    red=aColor->getRed();
    green=aColor->getGreen();
    blue=aColor->getBlue();
    alpha=aColor->getAlpha();
}


ColorBmp::ColorBmp()
{

}

int ColorBmp::getRed()
{
return this->red;
}

int ColorBmp::getGreen()
{
return this->green;
}

int ColorBmp::getBlue()
{
return this->blue;
}

int ColorBmp::getAlpha()
{
return this->alpha;
}

bool ColorBmp::operator==(ColorBmp* anotherColor)
{
return (this->red==anotherColor->getRed() && this->green==anotherColor->getGreen() && this->blue==anotherColor->getBlue() && this->alpha==anotherColor->getAlpha());
}

ColorBmp::~ColorBmp()
{

}
