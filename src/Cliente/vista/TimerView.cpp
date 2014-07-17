#include "TimerView.h"


TimerView::TimerView(int x, int y)
	: View(x, y)
{
	SDL_Color white;
	//this->timerView = 60;
	//this->updateTimer = 0;
	white.a = 0xFF,	white.r = 0xFF;
	white.g = 0xFF, white.b = 0xFF;
	//this->finished = true;
	//this->timerP = 0.0;
	this->label.setText("Tiempo", white);
	this->printTimer(0);
	//this->updateTime();
}


TimerView::~TimerView(void)
{
}
/*
void TimerView::setTimer(float t){
	this->timerP = t;
}
*/

void TimerView::update()
{
	/*if(!this->finished){
		float tim = this->timmer.elapsed();
		if(this->timerP < tim){
			this->finished = true;
			this->timerView = 60;
			this->updateTimer = 0;
			this->updateTime();
		}
		this->updateTimer = (int) tim;
		this->updateTime();
	}
	else{
	}
	*/
}
/*
void TimerView::updateTime(){
	SDL_Color white;	
	white.a = 0xFF,	white.r = 0xFF;
	white.g = 0xFF,	white.b = 0xFF;
	stgTimerView = Util::int2string(
		this->timerView - this->updateTimer);
	this->numberLabel.setText(stgTimerView, white);
}
*/

void TimerView::printTimer(int second){
	SDL_Color white;	
	white.a = 0xFF,	white.r = 0xFF;
	white.g = 0xFF,	white.b = 0xFF;
	stgTimerView = Util::int2string(second);
	this->numberLabel.setText(stgTimerView, white);
}


void TimerView::clean()
{

}
/*
void TimerView::start(){
	this->timmer.start();
	this->finished = false;
	this->timerView = 60;
	this->updateTimer = 0;
}

void TimerView::reset(){
	this->start();
}

bool TimerView::isFinished(){
	return this->finished;
}
*/
void TimerView::draw(SDLScreen & screen){
		int margin_left = 10;
		TextureManager::Instance().draw("reloj", 5, 5, screen.getRenderer());
		this->label.draw(screen.getRenderer(), getX() + margin_left , getY());
		this->numberLabel.draw(screen.getRenderer(), getX() + margin_left + 20, getY() + 30);
}