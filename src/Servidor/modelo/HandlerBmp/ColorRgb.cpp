#include "ColorRgb.h"

//Create an instance of ColorRgb
//If the colors values are not valid, it throw an integer exception:
//val 0: Red is out of valid value range.
//val 1: Green is out of valid value range.
//val 2: Blue is out of valid value range.
//val 3: Alpha is out of valid value range.
ColorRgb::ColorRgb(int red, int green, int blue, int alpha)
{
this->red=red;
this->green=green;
this->blue=blue;
this->alpha=alpha;

}


ColorRgb::~ColorRgb()
{

}
