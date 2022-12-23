#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Timer.h"

using namespace sf;

class World
{
protected:
	sf::Sprite sprite;
	sf::Texture* texture;
public:
	sf::Sprite getSprite() { return sprite; };
};
