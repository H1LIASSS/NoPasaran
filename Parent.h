#pragma once

#include <string>
#include "World.h"

using namespace std;

class Parent : public World
{ 
protected:
	double speed;
	double sprintSpeed;
	double walkSpeed;
	double health;
	double damageFromShuriken;
	double damageFromHit;
	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false; 
	double maxHealth;
	std::string name;
	bool isExpolsed = false;
public:
	void takeDamage(double damage);
	void move(int x, int y, double dt);
	void setRotation(double angle);
	void isUp(bool);
	void isDown(bool);
	void isRight(bool);    
	void isLeft(bool);           
	void setSpeed(double param);
	std::string className() { return name; };
	double getDamageFromHit() { return damageFromHit; };
	double getSpeed() { return speed; }; 
	double getWalkSpeed() { return walkSpeed; };
	double getMaxHealth() { return maxHealth; };
	double getSprintSpeed() { return sprintSpeed; };
	double getHealth() { return health; };
	double getDamageFromShuriken() { return damageFromShuriken; };
	bool operator!=(Parent*);
};
