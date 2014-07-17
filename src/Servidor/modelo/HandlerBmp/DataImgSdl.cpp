#include "DataImgSdl.h"


DataImgSdl::DataImgSdl(char* path)
{
	this->surface = IMG_Load(path);
	this->height=surface->h;
    this->width=surface->w;

    whitePositions = new list<Position*> ();
    blackPositions = new list<Position*> ();
    invalidPixels = new list<PixelBmp*>();

    //Se inicializa el bitmap con bool de valor falso(apagado =black)
    bitmap = new vector<vector<bool>*>();
    vector<vector<bool>*>* row = bitmap;
    vector<bool>* column;
    for(int i=0; i<height; i++)
    {
        row->push_back(new vector<bool>());
    }
	loadMatrix(path);
}


DataImgSdl::DataImgSdl()
{

}


DataImgSdl::~DataImgSdl()
{

}

//Pre:el tamanio de DATA debe ser de minimo width*3*row_padded
//Se lee la data con los bits de colores. Se sabe que la informacion esta organizada de la siguiente manera:
//++++++++++++++++
//+blue+green+red+ y esto ocupa 24 bits por píxel. y a su vez, cada fila tiene un tamanio de row_padded bytes
//++++++++++++++++
//Todo bit blanco o negro se ingresa al atributo 'bitmap', y a las listas de color según corresponda
//Si el bit es de color, se lo agrega a la lista de pixeles invalidos. Al final de la lectura de DATA se corrigen estos
//píxeles en el bitmap y en las listas de píxeles blancos y negros. (no se eliminan de la lista de invalidos)
/***Chequear que no queden "cuevas"***/
void DataImgSdl::loadMatrix(char* fileName,int row_padded, int height,int width)
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
	
	//carga de bits a la matriz
	for(int i = this->height-1; i >=0; i--)
	{
		for(int j = 0; j < this->width; j++)
		{
			int alpha=getAlpha(pixels,i,j);
			if( (alpha==0) || (posValid(i+1, j) && getBit(i+1,j)==true) )//es transparente //Si el bit debajo es transparente, pongo uno transparente
			{
				(*bitmap)[i]->push_back(true);
			}
			else //color
			{
					(*bitmap)[i]->push_back(false);
					setBlackPosition(i,j);
			}//endif valor del color
		}//end for recorrido columnas
	}//end for recorrido de filas
}


int DataImgSdl::getAlpha(Uint32 *pixels,int x, int y )
{

    
    //Get the requested pixel
    Uint32 pixel =(pixels[ ( x * surface->w ) + y ]);

	SDL_PixelFormat *fmt;
Uint32 temp;
Uint8 alpha;

fmt = surface->format;
SDL_LockSurface(surface);
SDL_UnlockSurface(surface);

/* Get Alpha component */
temp = pixel & fmt->Amask;  /* Isolate alpha component */
temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */

return (Uint8)temp;
}



ColorRgb *DataImgSdl::getPixel(Uint32 *pixels,int x, int y )
{

    
    //Get the requested pixel
    Uint32 pixel =(pixels[ ( x * surface->w ) + y ]);

	SDL_PixelFormat *fmt;
Uint32 temp;
Uint8 red, green, blue, alpha;

fmt = surface->format;
SDL_LockSurface(surface);
SDL_UnlockSurface(surface);

/* Get Red component */
temp = pixel & fmt->Rmask;  /* Isolate red component */
temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
red = (Uint8)temp;

/* Get Green component */
temp = pixel & fmt->Gmask;  /* Isolate green component */
temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
green = (Uint8)temp;

/* Get Blue component */
temp = pixel & fmt->Bmask;  /* Isolate blue component */
temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
blue = (Uint8)temp;

/* Get Alpha component */
temp = pixel & fmt->Amask;  /* Isolate alpha component */
temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
alpha = (Uint8)temp;

ColorRgb *colors=new ColorRgb(red,green,blue,alpha);
return colors;
}
	
