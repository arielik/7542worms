#pragma once

#ifndef __TIMER_VIEW_H__
#define __TIMER_VIEW_H__
#include "TextureManager.h"
#include "View.h"
#include "TextView.h"
#include "../../utils/Constantes/Colors.h"
#include "../../utils/Timer.h"
class TimerView: public View
{
public:
	TimerView(int x, int y);

	void clean();
	
	void update();

	void draw(SDLScreen & screen);
	
	void printTimer(int second);

/*
	void start();

	void reset();

	void updateTime();

	bool isFinished();

	void setTimer(float t);
	*/
	~TimerView(void);

private:
	TextView label;
	TextView numberLabel;
	std::string stgTimerView;
	/*
	Timer timmer;
	float timerP;
	bool finished;
	int index;
	int timerView;
	int updateTimer;*/
};

#endif /** __TIMER_VIEW_H__ **/