#include "DataBmp32.h"


DataBmp32::DataBmp32(char* data,int row_padded, int height,int width):DataBmp(data,row_padded,height,width)
{
	loadMatrix(data,row_padded,height,width);
}

DataBmp32::~DataBmp32()
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
void DataBmp32::loadMatrix(char* data,int row_padded, int height,int width)
{
	char tmp;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width*4; j += 4)
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
			int alpha=(int)data[j +row_padded*i + 3];
			unsigned int val=colorVal(red,green,blue,alpha);
			if(val==2) //es transparente
			{
				(*bitmap)[height-1-i]->push_back(true);
				///***********************
				//Avisar en el log el color encontrado
			}
			else //color
			{
				if((posValid(height-i, j/4) && getBit(height-i,j/4)==true) )//Si el bit debajo es transparente, pongo un transparente
				{
					(*bitmap)[height-1-i]->push_back(true);
				}else //color
				{
					(*bitmap)[height-1-i]->push_back(false);
					setBlackPosition(height-1-i,j/4);

				}
			}//endif valor del color
		}//end for recorrido columnas
	}//end for recorrido de filas
}


