#ifndef COLORBMP_H_
#define COLORBMP_H_

using namespace std;

class ColorBmp{

protected:
int red;
int green;
int blue;
int alpha;

public:
ColorBmp(ColorBmp* aColor);
ColorBmp();
int getRed();
int getGreen();
int getBlue();
int getAlpha();
bool operator==(ColorBmp* anotherColor);
virtual ~ColorBmp();

};


#endif
