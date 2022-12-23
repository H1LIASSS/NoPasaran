#pragma once
#include "SFML/System.hpp"
class Timer
{
	sf::Clock clock;
	sf::Time time;
	bool isDelay = false;
	double getElapsedTime();
	void restart();
public:
	bool wait(double);
	bool delay(double);
};

