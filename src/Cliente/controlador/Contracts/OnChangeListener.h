#ifndef __ONCHANGELISTENER__
#define __ONCHANGELISTENER__

#include "..\Entity\ChangeEvent.h"

class OnChangeListener{
	public:
		virtual void OnChange(ChangeEvent e){}
};

#endif

