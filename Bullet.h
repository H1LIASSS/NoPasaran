#pragma once

#include "Character.h"
#include "Bullet.h"
#include "Level.h"
#include <vector>

class Bullet : public World
{
	static std::vector<Bullet> bullets;
protected:
	sf::Vector2f forward;
	Timer lifeTime;
	double speed;
	double damage;
	Character* initiator;
	int rad;
public:
	Bullet(const double dam, sf::Vector2f distance, const sf::Vector2f pos, const double slope, Character* obj);
	Bullet();
	int getRad() { return rad; };
	static int getBullets() { return bullets.size(); };
	static void addBullet(const double dam, sf::Vector2f distance, const sf::Vector2f pos, const double slope, Character* obj);
	static void playBullet(sf::RenderWindow* window, Character* character,Level* level,double dt);
};

