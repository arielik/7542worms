#ifndef TerrainImg_H
#define TerrainImg_H


#include "DataBmp.h"
#include "DataBmp24.h"
#include "DataBmp32.h"
#include "DataImgSdl.h"
#include "../../../utils/Log.h"
#include <list>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class TerrainImg
{
private:
	FILE* fileBmp;
	DataBmp* aDataBmp;
	bool validarArchivo(char* path);
	bool esUnBmp(char* path);

public:
    TerrainImg(char* path);
	bool getBit(int posX, int posY);
	void showBitmap();
	int getHeight();
	int getWidth();
	bool posValid(int posX, int posY);
	list<Position*>* getBlackPositions();
	~TerrainImg();
};
#endif
