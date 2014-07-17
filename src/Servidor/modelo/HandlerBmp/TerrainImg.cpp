#include "TerrainImg.h"


TerrainImg::TerrainImg(char* path)
{

	int width;
	int height;
	int row_padded;
	char* data;

	if(validarArchivo(path))
	{

		if (esUnBmp(path))
		{
			// obtain file size:
			fseek (fileBmp , 0 , SEEK_END);
			long lSize = ftell (fileBmp);
			rewind (fileBmp);


			char info[30];
			fread(info, sizeof(char), 30, fileBmp); // read the 54-byte header

			// extract image height and width from header
			long offset =*(int*) &info[10];
			width = *(int*)&info[18];
			height = *(int*)&info[22];
			short bitsPerPixel =*(short*)&info[28];


			char* diffOffset = new char[offset-30];
			fread(diffOffset, sizeof(char), offset-30, fileBmp);
			delete[] diffOffset;


			if(bitsPerPixel==24) //bitmap de 24 bits por pixel
			{
				row_padded = (width*3 + 3) & (~3);
				data = new char[width*3*row_padded];
				fread(data, sizeof(char), row_padded*height, fileBmp);
				fclose(fileBmp);
				aDataBmp = new DataBmp24(data,row_padded,height,width);
			}
			else if (bitsPerPixel==32)  //bitmap de 32 bits por pixel
			{
				row_padded = (width*4 + 4) & (~4);
				data = new  char[width*4*row_padded];
				fread(data, sizeof(char), width*4*row_padded, fileBmp);
				fclose(fileBmp);
				aDataBmp = new DataBmp32(data,row_padded,height,width);
			}
		}else
		{

			aDataBmp = new DataImgSdl(path);
		}


	}else
	{
		aDataBmp=NULL;
		throw 20;
	}

}


bool TerrainImg::validarArchivo(char* path)
{
	fileBmp = fopen(path, "rb");
	if (fileBmp==NULL)
	{ 
		Log::e("Class Bmp.cpp: No existe el archivo. Se creará un bmp por default");
		return false;
	}

	return true;
}


bool TerrainImg::esUnBmp(char* path)
{
	int longitudPath= strlen(path);
	bool valido= 
		(path[longitudPath-4]=='.' &&
		path[longitudPath-3]=='b' &&
		path[longitudPath-2]=='m' &&
		path[longitudPath-1]=='p');
	return valido;
}


TerrainImg::~TerrainImg()
{
	delete aDataBmp;
}

bool TerrainImg::getBit(int posX, int posY)
{
	return aDataBmp->getBit(posX,posY);
}
list<Position*>* TerrainImg::getBlackPositions()
{
	return aDataBmp->getBlackPositions();
}

bool TerrainImg::posValid(int posX, int posY)
{
	return aDataBmp->posValid(posX,posY);
}
int TerrainImg::getHeight()
{
	return aDataBmp->getHeight();
}

int TerrainImg::getWidth()
{
	return aDataBmp->getWidth();
}

void TerrainImg::showBitmap()
{
	this->aDataBmp->showBitmap();
}
