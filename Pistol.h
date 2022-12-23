#pragma once
#include "Weapon.h"

class Pistol : public Weapon
{
public:
	Pistol(Character* x);
	void fire();
};

