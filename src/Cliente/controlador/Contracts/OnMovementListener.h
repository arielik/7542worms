#ifndef __ONMOVEMENTLISTENER__
#define __ONMOVEMENTLISTENER__

#include "..\Entity\MovementEvent.h"

class OnMovementListener{
	public:
		virtual void OnMovement(MovementEvent e){}
};

#endif


