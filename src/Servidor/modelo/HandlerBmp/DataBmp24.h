#ifndef DataBmp24_H
#define DataBmp24_H

#include <list>
#include <vector>

#include "DataBmp.h"
#include "PixelBmp.h"


using namespace std;

class DataBmp24 : public DataBmp
{


public:
    DataBmp24(char* data,int row_padded, int height,int width);
    DataBmp24();
	virtual ~DataBmp24();

protected:
		void loadMatrix(char* data,int row_padded=0, int height=0, int width=0);


};

#endif // DataBmp24_H
