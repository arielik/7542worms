#pragma once


#ifndef __ACTIVITY_H_
#define __ACTIVITY_H_
#include "SDLScreen.h"
#include "ViewGroup.h"

class Activity
{
private:
	SDLScreen m_screen;

protected:
	/** Clear windows to draw view*/
	void clear();

	/** Set the view to draw on window*/
	void setContentView(ViewGroup * newView);

	ViewGroup* aView;

	

public:

	Activity(SDLScreen & screen);

	virtual ~Activity(void);

	virtual void stop();

	/** Update	 the view*/
	virtual void update();

	/** Render the view on screen*/
	void render();

	virtual void setMessageView(std::string msg) = 0;
	virtual void showMessageError(std::string msg) = 0;
	virtual void showMessageInfo(std::string msg) = 0;

};

#endif /* defined(__ACTIVITY_H_) */
