#pragma once

#include "Character.h"
#include "Level.h"

class Player : public Character
{
	sf::Vector2f vec;
	double diagonal;
public:
	Player();
	void hit();
	void setIsNear();
	void collision(Level level);
};

