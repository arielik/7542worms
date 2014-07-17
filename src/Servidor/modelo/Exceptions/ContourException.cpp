#include "ContourException.h"
#include "..\..\..\utils\Constantes\Constantes.h"

using namespace server_model_exp;

ContourExp::ContourExp(int error) : exception(), idError(error) {
	mError[HC_OFFSET + 1] = HC_ERROR_1;
	mError[HC_OFFSET + 2] = HC_ERROR_2;
	mError[HC_OFFSET + 3] = HC_ERROR_3;
	mError[HC_OFFSET + 4] = HC_ERROR_4;
}


ContourExp::~ContourExp(void)
{
}


const char* ContourExp::what(){
	return mError[HC_OFFSET + idError].c_str();
}

