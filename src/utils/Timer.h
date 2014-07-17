#pragma once

#ifndef TIMER_H_
#define TIMER_H_


#include <vector>
#include <string>
#include <ctime>

class Timer{

	private:
		std::clock_t startTime;
		bool hasStarted;

	public:
		Timer();
		~Timer();

		void start();
        void stop();
		void reset();
		float elapsed();
		bool isStarted();
};

#endif