#ifndef CONTOURBMP_H
#define CONTOURBMP_H

#include "TerrainImg.h"

class ContourBmp
{
    public:
        ContourBmp(TerrainImg* aBmpFile);
        list< list<Position*> *>* getConnectedComponents(list<Position*>* aPositionList);
		list< list<Position*>* >* getConnectedComponentsOptimized();
		list< pair<int,int> >* getConnectedComponentsOptimized(int waterLevel);
        list< list<Position*> *>* getContour();
		pair<int,int> getMaxPointTerrain();
		void updateMaxPosition(int posX, int posY);
        static void deleteListOfListPositions(list< list<Position*>* >* aListOfListToDelete);
        virtual ~ContourBmp();
    protected:
    private:
		pair<int,int> maxPointTerrain;
        TerrainImg* aBmpFile;
        int getSquareValue(int pX, int pY);
        list<Position*> * getContour(list<Position*> * aConnectedComponent);
};

#endif // CONTOURBMP_H
