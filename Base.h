#pragma once

#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace sf;

namespace generalStuff
{
	double getLOD();
	sf::Vector2f getCursorPositionInWorld();
	void setCursorPositionInWorld(sf::Vector2f x);
	void setIsPause(bool);
	bool getIsPause();
	void loadValueOfDrawDistance(sf::RenderWindow& window);
	double deltaTime();
	sf::Vector2f normalize(sf::Vector2f vect);
	void resetClock();
	double makeDistance(sf::Vector2f);
	double slope(sf::Vector2f katet);
};

namespace settings
{
	double getVolume();
	void setVolume(double);
}