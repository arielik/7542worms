#ifndef DataBmp_H
#define DataBmp_H

#include <list>
#include <vector>

#include "PixelBmp.h"


using namespace std;

class DataBmp
{
protected:
	list<Position*>* whitePositions;
	list<Position*>* blackPositions;
	list<PixelBmp*>* invalidPixels;
	vector<vector<bool>*>* bitmap;
	int height;
	int width;
	void resetInvalidPixels();
	virtual void loadMatrix(char* data,int row_padded=0, int height=0, int width=0)=0;
	unsigned int colorVal(int red,int green,int blue, int alpha);

public:
	DataBmp(char* data,int row_padded, int height,int width);
	DataBmp();

	list<Position*>* getWhitePositions();
	list<Position*>* getBlackPositions();
	list<PixelBmp*>* getInvalidPixels();
	void setWhitePosition(int posX,int posY);
	void setBlackPosition(int posX,int posY);
	bool setBit(int posX, int posY, bool color);
	bool getBit(int posX, int posY);
	int getHeight();
	int getWidth();

	bool posValid(int posX, int posY);
	void deleteMatrix(vector<vector<bool>*>* aBitmap);
	static void deletePositionList(list<Position*> * aListToDelete);
	static void deletePixelList(list<PixelBmp*> * aListToDelete);
	void showBitmap();
	virtual ~DataBmp();

protected:


};

#endif // DataBmp_H
