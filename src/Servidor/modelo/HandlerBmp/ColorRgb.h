#ifndef COLORRGB_H_
#define COLORRGB_H_

#include "ColorBmp.h"

using namespace std;

class ColorRgb : public ColorBmp{
public:
ColorRgb(int red, int green, int blue, int alpha);
virtual ~ColorRgb();
};

#endif
