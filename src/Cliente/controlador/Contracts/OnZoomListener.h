#ifndef __ONZOOMLISTENER__
#define __ONZOOMLISTENER__

#include "..\Entity\ZoomEvent.h"

class OnZoomListener{
	public:
		virtual void OnZoom(ZoomEvent e){}
};

#endif

