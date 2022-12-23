#pragma once

#include "UI.h"
#include "Character.h"

using namespace sf;

class Enemy : public Character
{
private:
	Timer attackTimerByWeapon;
	Timer attackNearTimer;
	static std::vector<Enemy> enemies;
public:
	Enemy();
	static void addEnemy();
	static void destroyAll();
	static int getCount() { return enemies.size(); };
	static void playEnemy(sf::RenderWindow& window, Character& character,double dt);
};