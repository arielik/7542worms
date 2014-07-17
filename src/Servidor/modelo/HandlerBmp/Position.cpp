#include "Position.h"


Position::Position(Position* aPosition)
{
    this->posX = aPosition->getX();
    this->posY = aPosition->getY();
}

Position::Position(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

int Position::getX()
{
    return this->posX;
}

int Position::getY()
{
    return this->posY;
}

void Position::setX(int posX)
{
    this->posX=posX;
}

void Position::setY(int posY)
{
    this->posY=posY;
}

//True: esta posicion esta en una fila menor ó en la misma fila pero en una columna menor
bool Position::operator<(Position* anotherPosition)
{
    if (this->getX() < anotherPosition->getX() )
    {
        return true;
    }
    else if(this->getX() > anotherPosition->getX() )
    {
        return false;
    }
    else
    {
        if(this->getY() <= anotherPosition->getY())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Position::operator==(Position* anotherPosition)
{
    return ( (this->getX() == anotherPosition->getX()) && (this->getY() == anotherPosition->getY()) );
}

//True: aPosition esta en una fila menor ó en la misma fila pero en una columna menor que anotherPosition
bool Position::lessPosX(Position* aPosition, Position* anotherPosition)
{
 return (*aPosition<anotherPosition);
}

//True: aPosition esta en una columna menor ó en la misma columna pero en una fila menor que anotherPosition
bool Position::lessPosY(Position* aPosition, Position* anotherPosition)
{
     if (aPosition->getY() < anotherPosition->getY() )
    {
        return true;
    }
    else if(aPosition->getY() > anotherPosition->getY() )
    {
        return false;
    }
    else
    {
        if(aPosition->getX() <= anotherPosition->getX())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Position::samePos(Position* aPosition, Position* anotherPosition)
{
return( (*aPosition)==anotherPosition);
}


Position::~Position()
{

}

