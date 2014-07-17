#pragma once

#ifndef TerrainProcessor_H_
#define TerrainProcessor_H_

#include "HandlerBmp/ContourBmp.h"
#include "HandleContour.h"
#include "../../libs/Box2D/Box2D.h"
#include"../../utils/ParserYaml.h"
#include "Physics\Body.h"

#include <cstdio>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <boost/math/constants/constants.hpp>

namespace bg = boost::geometry;
typedef boost::geometry::model::point<float, 2, boost::geometry::cs::cartesian> point;
typedef boost::geometry::model::polygon<point, false, false> poly_t;

using namespace server_model_handle;
using namespace std;
class TerrainProcessor
{

private:
	b2Vec2 transformBmpToBox2D(b2Vec2 vertex, int height, int width);
	list< list< pair<float,float> > >* aListOfPolygons;
	void makeDefaultTerrain(b2World* m_world,int waterLevel);
	list<pair<int,int>> * rangeTerrainOverWater;
	pair<int,int> maxPointTerrain;
	int height;
	int width;
	

public:
	TerrainProcessor();

	void  process(b2World* mworld, char* path,float epsilon, int scale,int waterLevel, bool chained, std::vector<b2Body*>* myTerrain, std::list<poly_t*>* myPol);

	TerrainProcessor(b2World* m_world, char* path,float epsilon, int scale, int waterLevel);
	list< list< pair<float,float> > > * getListOfPolygons();
	~TerrainProcessor(void);

	vector<b2Vec2> getChains(vector<b2Vec2> lista, float epsilon, int scale, int &height, int& width, int waterLevel);


	vector<vector<b2Vec2>> 
	    getPolygonConvex(vector<b2Vec2> contour, float epsilon, int scale, int& height, int& width,int waterLevel);
	static void getRandomPosition(int* x,int* y);
	list<pair<int,int>> * getRangeTerrainOverWater();
	pair<int,int> getMaxPointTerrain();
	int getHeight();
	int getWidth();
};

#endif