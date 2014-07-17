#include "DataBmp.h"
#include <iostream>
#include "Position.h"



DataBmp::DataBmp()
{
}


//El constructor de la clase recibe:
//data: el bloque de datos del archivo bmp Pre:el tamanio debe ser de minimo width*3*row_padded
//row_padded: el tamaño de las filas guardadas en el bloque
//height y width sacada del archivo .bmp.
//Pos1: Instancia 3 listas a saber
// -whitePositions: contiene las posiciones blancas (bool=true=1) del bitmap (y las corregidas por ser de color)
// -blackPositions: contiene las posiciones negras (bool=false=0) del bitmap (y las corregidas por ser de color)
// -invalidPixels: contiene las posiciones que no son negras ni blancas del bitmap.
//Pos2: Instancia una matriz de bool, con valores false y luego carga los datos del bitmap en ella:
// -Pixels Blancos: bool=true=1
// -Pixels Negros: bool=false=0
DataBmp::DataBmp(char* data,int row_padded, int height,int width)
{
    this->height=height;
    this->width=width;
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
}

//Pos:
// return 0:black
// return 1:white
// return 2:transparent
// return 3:color
unsigned int DataBmp::colorVal(int red, int green, int blue, int alpha)
{
	if(alpha==0)
	{
		return 2;
	}

    if(red==0 && green==0 && blue==0) //black
    {
        return 0;
    }
    else if(red==255 && green==255 && blue==255) //white
    {
        return 1;
    }
    else //color
    {
        return 3;
    }
}

//Resuelve los píxels de color
void DataBmp::resetInvalidPixels()
{
    list<PixelBmp*>* aPixelList = this->getInvalidPixels();
    list<PixelBmp*>::iterator itPixels = aPixelList->begin();

    while(itPixels != aPixelList->end())
    {
        int posXInvalido=(*itPixels)->getPosition()->getX();
        int posYInvalido=(*itPixels)->getPosition()->getY();

        if(posXInvalido == 0) //borde superior pongo color blanco
        {
            setBit(posXInvalido,posYInvalido,1); //blanco
            setWhitePosition(posXInvalido,posYInvalido);
        }
        else //if(posXInvalido == this->height-1) //en el medio pongo el mismo que el de arriba
        {
            bool val=getBit(posXInvalido-1,posYInvalido);
            if(val)
            {
                setWhitePosition(posXInvalido,posYInvalido);
            }
            else
            {
                setBlackPosition(posXInvalido,posYInvalido);
            }
            setBit(posXInvalido,posYInvalido,val);
        }/*
        else
        {
            setBit(posXInvalido,posYInvalido,getBit(posXInvalido-1,posYInvalido)); //pongo el mismo que el de arriba
        }*/
        itPixels++;
    }
    this->deletePixelList(aPixelList);
}




//Devuelve una copia de la lista de posiciones blancas ordenada por filas. Se debe liberar la memoria despues de utilizar la lista
list<Position*>* DataBmp::getWhitePositions()
{
    list<Position*>* aWhitePositionsList = new list<Position*>();
    whitePositions->sort(Position::lessPosX);
    list<Position*>::iterator itList = whitePositions->begin();

    while(itList != whitePositions->end())
    {
        Position* aPositionToCopy = *itList;
        Position* newPosition = new Position(aPositionToCopy->getX(), aPositionToCopy->getY() );
        aWhitePositionsList->push_back(newPosition);
        itList++;
    }
    return aWhitePositionsList;
}

//Devuelve una copia de la lista de posiciones negras ordenada por filas. Se debe liberar la memoria despues de utilizar la lista
list<Position*>* DataBmp::getBlackPositions()
{
    list<Position*>* aBlackPositionsList = new list<Position*>();
    blackPositions->sort(Position::lessPosY);
    list<Position*>::iterator itList = blackPositions->begin();

    while(itList != blackPositions->end())
    {
        Position* aPositionToCopy = *itList;
        Position* newPosition = new Position(aPositionToCopy->getX(), aPositionToCopy->getY() );
        aBlackPositionsList->push_back(newPosition);
        itList++;
    }
    return aBlackPositionsList;
}

//Devuelve una copia de la lista de Píxels invalidos ordenada por columnas. Se debe liberar la memoria despues de utilizar la lista
list<PixelBmp*>* DataBmp::getInvalidPixels()
{
    list<PixelBmp*>* aPixelList = new list<PixelBmp*>();
    invalidPixels->sort(PixelBmp::lessPosY);
    list<PixelBmp*>::iterator itPixel = invalidPixels->begin();

    while(itPixel != invalidPixels->end())
    {
        PixelBmp* aPixelToCopy = *itPixel;
        Position* aPositionToCopy =aPixelToCopy->getPosition();
        ColorBmp* aColorToCopy =aPixelToCopy->getColor();
        PixelBmp* newPixel = new PixelBmp(new Position(aPositionToCopy), new ColorBmp(aColorToCopy) );
        aPixelList->push_back(newPixel);
        itPixel++;
    }
    return aPixelList;
}

//Se instancia y se agrega una nueva posicion en la lista de posiciones blancas
void DataBmp::setWhitePosition(int posX,int posY)
{
    Position* aPosition = new Position(posX,posY);
    this->whitePositions->push_back(aPosition);
}

//Se instancia y se agrega una nueva posicion en la lista de posiciones negras
void DataBmp::setBlackPosition(int posX,int posY)
{
    Position* aPosition = new Position(posX,posY);
    this->blackPositions->push_back(aPosition);
}

//Pos: Se devuelve "False" en caso que las posiciones esten fuera del rango width y height
bool DataBmp::setBit(int posX, int posY, bool color)
{
    if(posValid(posX,posY))
    {
        vector<vector<bool>*>* fila = bitmap;
        vector<bool>* columna =(*fila)[posX];
        (*columna).at(posY)=color;
        return true;
    }
    else
    {
        return false;
    }
}

//Pre: las posiciones deben ser validas (no fuera del rango de ancho y alto del bitmap)
bool DataBmp::getBit(int posX, int posY)
{
    vector<vector<bool>*>* fila = bitmap;
    vector<bool>* columna =(*fila)[posX];
    return (*columna).at(posY);
}

int DataBmp::getHeight()
{
    return this->height;
}

int DataBmp::getWidth()
{
    return this->width;
}

//Chequea que los valores se encuentren dentro del alto y ancho del bitmap
bool DataBmp::posValid(int posX, int posY)
{
    return (posX>=0 && posX<height && posY>=0 && posY<width);
}

//Libera la memoria dentro de un vector de vectores bool
void DataBmp::deleteMatrix(vector<vector<bool>*>* aBitmap)
{
    vector<vector<bool>*>* row = aBitmap;

    for(int i=0; i<this->height; i++)
    {
        vector<bool>* rowToDel = (*row)[i];
        delete rowToDel;
    }

    delete aBitmap;
}

//Libera la memoria de una lista de posiciones
void DataBmp::deletePositionList(list<Position*> * aListToDelete)
{
    list<Position*>::iterator itList = aListToDelete->begin();

    while(itList != aListToDelete->end())
    {
        Position* aPositionToDelete = *itList;
        delete aPositionToDelete;
        itList++;
    }
    delete aListToDelete;
}

//Libera la memoria de una lista de Píxeles, liberando así las posiciones y los colores del Píxel
void DataBmp::deletePixelList(list<PixelBmp*> * aListToDelete)
{
    list<PixelBmp*>::iterator itList = aListToDelete->begin();

    while(itList != aListToDelete->end())
    {
        PixelBmp* aPixelToDelete = *itList;
        delete aPixelToDelete;
        itList++;
    }
    delete aListToDelete;
}

//Muestra el valor del bitmap
//0:Black
//1:White
void DataBmp::showBitmap()
{
		cout<<endl;
		cout<<endl;
		cout<<"***********"<<endl;
        cout<<"Archivo BMP" <<endl;
		cout<<endl;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            cout<<getBit(i,j);
        }
        cout<<endl;
    }
}

DataBmp::~DataBmp()
{
    deleteMatrix(bitmap);
    deletePixelList(invalidPixels);
    deletePositionList(whitePositions);
    deletePositionList(blackPositions);
}
