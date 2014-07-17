#include "DataBmp24.h"


DataBmp24::DataBmp24(char* data,int row_padded, int height,int width):DataBmp(data,row_padded,height,width)
{
	    loadMatrix(data,row_padded,height,width);
}

DataBmp24::~DataBmp24()
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
void DataBmp24::loadMatrix(char* data,int row_padded, int height,int width)
{
    char tmp;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j+(row_padded*i)];
            data[j+(row_padded*i)] = data[j+(row_padded*i)+2];
            data[j+(row_padded*i)+2] = tmp;


            //carga de bits a la matriz
			char a=data[j+(row_padded*i)];
            int red=(int)data[j+(row_padded*i)];
            int green=(int)data[j +row_padded*i + 1];
            int blue=(int)data[j +row_padded*i + 2];
            unsigned int val=colorVal(red,green,blue,255);
            if(val==3) //tiene color
            {
                PixelBmp* aInvalidPixel = new PixelBmp(new Position(height-1-i,j/3), new ColorRgb(red,green,blue,255));
                invalidPixels->push_back(aInvalidPixel);
				(*bitmap)[height-1-i]->push_back(false);
				///***********************
				//Avisar en el log el color encontrado
            }
            else //blanco o negro
            {
					if( (val==1) || (posValid(height-i, j/3) && getBit(height-i,j/3)==true) )//Si el bit debajo es blanco, pongo un blanco
					{
					(*bitmap)[height-1-i]->push_back(true);
                    setWhitePosition(height-1-i,j/3);

					}else //negro
					{
					(*bitmap)[height-1-i]->push_back(false);
                    setBlackPosition(height-1-i,j/3);

					}
	
               //setBit(height-1-i,j/3,val);
            }
        }
    }
    //evaluar lista de bits invalidos
    resetInvalidPixels();
}


