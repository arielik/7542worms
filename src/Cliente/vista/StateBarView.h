#pragma once
#ifndef __STATEBARVIEW_H__
#define __STATEBARVIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "ViewGroup.h"
#include "TextView.h"
#include "time.h"
#include "TextManager.h"
class StateBarView : public View
{
private:


	int i;

	std::string msj;

	TextView label;
	
	TextView labelCenter;

	Uint32 colorInfo;
	Uint32 colorError;
	
	Uint32 colorMsg;

public:
	int j;
	SDL_Color color;

	~StateBarView(void);

	StateBarView();
				
	void setMsj(std::string msj);

	void setMsjInfo(std::string msj);

	void setMsjError(std::string msj);

	void setMessageCenter(std::string msg);

	void draw(SDLScreen & screen);

};

#endif /** __STATEBARVIEW_H__*/