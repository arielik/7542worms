#pragma once

#ifndef __POWER_VIEW_H__
#define __POWER_VIEW_H__
#include "TextureManager.h"
#include "..\controlador\Contracts\OnChangeListener.h"
#include "..\controlador\Entity\ChangeEvent.h"
#include "View.h"
#include "TextView.h"
#include "../../utils/Constantes/Colors.h"
class PowerView: public View,
	             public OnChangeListener
{
public:
	PowerView(int x, int y);

	void clean();
	
	void update();

	void OnChange(ChangeEvent e);

	void draw(SDLScreen & screen);

	void allow();

	void deny();

	~PowerView(void);
private:
	TextView label;
	SDL_Rect rect;
	bool bAllow;
};

#endif /** __POWER_VIEW_H__ **/