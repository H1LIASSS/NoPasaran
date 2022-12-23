#include "Base.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace sf;
using namespace std;

sf::Clock worldClock;
sf::Vector2f cursorPosInWorld;
double distanceOfDraw;
double volume=0;
bool isPause = true;

//get/set pause 
bool generalStuff::getIsPause() { return isPause; };
void generalStuff::setIsPause(bool x) { isPause = x; };

//get/set volume
double settings::getVolume() { return volume; }
void settings::setVolume(double x) { volume = x; };

//search distance between 2 points
double generalStuff::makeDistance(sf::Vector2f difference) { return sqrt(difference.x * difference.x + difference.y * difference.y); }

//get draw distance depends from diagonal length pixels of monitor
double generalStuff::getLOD() { return distanceOfDraw; }

//set value of draw distance
void generalStuff::loadValueOfDrawDistance(sf::RenderWindow& window) { distanceOfDraw = window.getSize().x*1.9; }

//get delta 
double generalStuff::deltaTime() 
{ 
	return worldClock.getElapsedTime().asMicroseconds();
}

//search angle between 2 points
double generalStuff::slope(sf::Vector2f katet) { return atan2f(katet.x, katet.y) / M_PI * 180; }

//normalize vector
sf::Vector2f generalStuff::normalize(sf::Vector2f vector)
{
	double hypotenuza = sqrt(vector.x * vector.x + vector.y * vector.y);
	sf::Vector2f normal(vector.x / hypotenuza, vector.y / hypotenuza);
	return normal;
}

//get cursor position
sf::Vector2f generalStuff::getCursorPositionInWorld() { return cursorPosInWorld; };
//set curosr position
void generalStuff::setCursorPositionInWorld(sf::Vector2f x) { cursorPosInWorld = x; };


//reset delta time after loop
void generalStuff::resetClock() { worldClock.restart(); };