#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <SDL.h>
#include "../controlador/Contracts/OnScrollListener.h"
#include "../controlador/Contracts/OnZoomListener.h"
#include "../../utils/Log.h"

typedef enum {
	FOCUS_BOTOOM_CENTER,
	FOCUS_CENTER
} tFocus;

class Camera : public OnScrollListener, public OnZoomListener
{
	SDL_Rect box;
	int widthScenario;
	int heightScenario;
	int widthScreen;
	int heightScreen;

	float scale;

public:
	Camera();

	void setDimension(int w, int h);
	void setPosition(int x, int y);
	int getX() { return this->box.x;}
	int getY() { return this->box.y;}
	int getW() { return this->box.w;}
	int getH() { return this->box.h;}
	void setW(int w) { this->box.w = w;}
	void setH(int h) { this->box.h = h;}
	int getWidthScenario() {return this->widthScenario;}
	int getHeightScenario() {return this->heightScenario;}
	void setWidthScenario(int w) { this->widthScenario = w;}
	void setHeightScenario(int h) {this->heightScenario = h;}
	void setWidthScreen(int w) { this->widthScreen = w;}
	void setHeightScreen(int h) {this->heightScreen = h;}

	void OnScroll(ScrollEvent e);

	void setFocus(tFocus tipo, int dest_w, int dest_h);

	void OnZoom(ZoomEvent e);

	float getScale() {return this->scale;}

	void scrollUp(int delta_y);
	void scrollLeft(int delta_x);

	bool validateScrollUp(int delta_y);

	bool validateScrollLeft(int delta_x);

	~Camera(void);


};

#endif