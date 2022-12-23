#pragma once

#include "Parent.h"
#include "Pistol.h"

class Character : public Parent
{
protected:
	Weapon* weapon = new Pistol(this);
	Timer attackTimer;
	bool isNear = false;
	bool isHit = false;
public:
	Character();
	Weapon* getWeapon() { return weapon; };
	bool getIsHit() { return isHit; };
};