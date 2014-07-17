#ifndef PixelBmp_H_
#define PixelBmp_H_

#include "ColorRgb.h"
#include "Position.h"

using namespace std;

class PixelBmp
{
private:
    Position* position;
    ColorBmp* color;

public:
    PixelBmp(Position* aPosition, ColorBmp* aColor);
    void setPosition(Position* newPosition);
    void setColor(ColorBmp* newColor);
    ColorBmp* getColor();
    Position* getPosition();
    bool operator<(PixelBmp* anotherPixelBmp);
    static bool lessPosY(PixelBmp* aPixelBmp, PixelBmp* anotherPixelBmp);
    ~PixelBmp();
};

#endif
