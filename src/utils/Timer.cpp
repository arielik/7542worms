#include "Timer.h"

Timer::Timer(){
	this->hasStarted = true;
	this->startTime = 0;
}
		
Timer::~Timer(){}

void Timer::start(){
	this->startTime = std::clock();
}

void Timer::stop(){
	 this->startTime = 0;
	 this->hasStarted = false;
}


float Timer::elapsed(){
	 float time = 0;

	 time =  (float)(std::clock() - this->startTime) /  (float)CLOCKS_PER_SEC;

	 return time;

}

void Timer::reset(){
	 this->startTime = std::clock();
	 this->hasStarted = true;
}

bool Timer::isStarted(){
	return this->hasStarted;
}