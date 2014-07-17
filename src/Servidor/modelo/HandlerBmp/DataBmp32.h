#ifndef DataBmp32_H
#define DataBmp32_H

#include <list>
#include <vector>

#include "DataBmp.h"
#include "PixelBmp.h"


using namespace std;

class DataBmp32 : public DataBmp
{


public:
    DataBmp32(char* data,int row_padded, int height,int width);
    DataBmp32();
	virtual ~DataBmp32();

protected:
		void loadMatrix(char* data,int row_padded=0, int height=0, int width=0);


};

#endif // DataBmp32_H
