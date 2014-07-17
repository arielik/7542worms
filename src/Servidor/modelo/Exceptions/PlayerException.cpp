#include "PlayerException.h"
#include "..\..\..\utils\Constantes\Constantes.h"

using namespace server_model_exp;

PlayerExp::PlayerExp(int error) : exception(), idError(error) {
	mError[HP_OFFSET + 1] = HP_ERROR_1;
	mError[HP_OFFSET + 2] = HP_ERROR_2;
}


PlayerExp::~PlayerExp(void)
{
}


const char* PlayerExp::what(){
	return mError[HC_OFFSET + idError].c_str();
}

