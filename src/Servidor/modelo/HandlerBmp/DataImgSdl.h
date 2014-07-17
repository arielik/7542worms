#ifndef DataImgSdl_H
#define DataImgSdl_H

#include <list>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "DataBmp.h"
#include "ColorRgb.h"
#include "PixelBmp.h"


using namespace std;

class DataImgSdl : public DataBmp
{
private:

	SDL_Surface *surface;
	ColorRgb *getPixel(Uint32 *pixels,int x, int y );
	int getAlpha(Uint32 *pixels,int x, int y );
public:
	DataImgSdl(char* path);
	DataImgSdl();
	virtual ~DataImgSdl();

protected:
		void loadMatrix(char* data,int row_padded=0, int height=0, int width=0);


};

#endif // DataImgSdl_H
