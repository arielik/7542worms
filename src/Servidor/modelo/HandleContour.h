#pragma once

#ifndef __HANDLECONTOUR__
#define __HANDLECONTOUR__

#include <Box2D.h>
#include <vector>
#include "b2Separator.h"
#include <string>
#include <map>
#include "Exceptions\ContourException.h"

using namespace std;
using namespace server_model_exp;

namespace server_model_handle{
	class HandleContour{
	public:
		HandleContour();
		~HandleContour();
		
		vector<vector<b2Vec2>> 
			getPolygonConvex(vector<b2Vec2> contour,
			                 float epsilon, 
							 int scale) throw (ContourExp);

		vector<b2Vec2> getPolygonConvex(vector<b2Vec2> contour,
										float epsilon, 
										int scale,
										bool chained);

	private:
		map<int, string> _error;
		vector<b2Vec2> rdp(vector<b2Vec2> contour, float epsilon);
		float findPerpendicularDistance(b2Vec2 p, b2Vec2 p1, b2Vec2 p2);
		vector<vector<b2Vec2>> split(vector<b2Vec2> contour);
		vector<b2Vec2> mulK(vector<b2Vec2> contour, float scale);
		vector<vector<b2Vec2>> mulK(vector<vector<b2Vec2>> contours, float scale);
		vector<vector<b2Vec2>> valSize(vector<vector<b2Vec2>> contours);
		void removeVertexThanMore(vector<b2Vec2>* contour);
		int getIndex(float NroA,float NroB,float NroC);
	};
}
#endif /*__HANDLECONTOUR__*/
