#include "Timer.h"
#include "Base.h"
#include <iostream>
using namespace std;

void Timer::restart()
{
	//restart
	clock.restart();
	time = clock.restart();
}

double Timer::getElapsedTime()
{
	//if is pause clock will restart and stop count time during pause
	if (generalStuff::getIsPause())
	{
		clock.restart();
	}
	else
	{
		time += clock.getElapsedTime();
		clock.restart();
		return time.asSeconds();
	}

}

bool Timer::wait(double x)
{
	if (!isDelay)
	{
		restart();
		isDelay = true;
	}
	if (getElapsedTime() >= x)
	{
		isDelay = false;
		return true;
	}
	return false;
}

bool Timer::delay(double time)
{
	//check if elapsed time is greater then time that i defined
	if (getElapsedTime() >= time)
	{
		restart();
		return true;
	}
	return false;
}