#ifndef POSITION_H_
#define POSITION_H_

using namespace std;


class Position
{
private:

int posX;
int posY;

public:
    Position(Position*  aPosition);
Position(int posX, int posY);

int getX();
int getY();
void setX(int posX);
void setY(int posY);

bool operator<(Position* anotherPosition);
bool operator==(Position* anotherPosition);
static bool lessPosX(Position* aPosition, Position* anotherPosition);
static bool lessPosY(Position* aPosition, Position* anotherPosition);
static bool samePos(Position* aPosition, Position* anotherPosition);

virtual ~Position();


};

#endif
