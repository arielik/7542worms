#ifndef __ONACTIONLISTENER__
#define __ONACTIONLISTENER__

#include "..\Entity\ActionEvent.h"

class OnActionListener{
	public:
		virtual void OnAction(ActionEvent e) = 0;
};

#endif
