#pragma once

#ifndef __WAIT_VIEW_H__
#define __WAIT_VIEW_H__
#include "TextureManager.h"
#include "TextView.h"
#include "View.h"
enum WaitState {
	WAIT_VIEW_WAIT,
	WAIT_VIEW_GAMEOVER,
	WAIT_VIEW_WINNER,
	WAIT_VIEW_ALERT,
};

class WaitView: public View
{

	WaitState state;

	std::string imageId;

	std::string imageWaitId;

	std::string imageGameOverId;

	std::string imageWinnerId;

	std::string imageAlertId;

	TextView  text;

public:
	WaitView(std::string imageWaitId, std::string imageGameOverId, std::string imageWinnerId, std::string imageAlertId);
									
	void clean();
	
	void update();

	void draw(SDLScreen & screen);

	void setMessage(std::string msg);

	void setStateWinner() {this->state = WAIT_VIEW_WINNER;}
	void setStateGameOver() {this->state = WAIT_VIEW_GAMEOVER;}
	void setStateWait() {this->state = WAIT_VIEW_WAIT;}
	void setStateAlert() {this->state = WAIT_VIEW_ALERT;}

	~WaitView(void);
};

#endif /** __WAIT_VIEW_H__ **/