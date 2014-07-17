#ifndef __SHAPE__
#define __SHAPE__

#include <map>

using namespace std;

class Shape{
public:
	Shape(int x, int y,
		int width, int height);
	Shape();
	~Shape();

	/*Summary: return (x, y)*/
	pair<int, int> getPosition();

	/*Summary: return (width, height)*/
	pair<int, int> getDimension();
private:
	int x, y, 
	width, height;
};

#endif
