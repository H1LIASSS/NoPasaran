#include "Weapon.h"
#include "Base.h"
#include "Character.h"
#include <iostream>
using namespace std;
using namespace generalStuff;

Weapon::Weapon() {};

void Weapon::fire(){}

void Weapon::reload()
{
	if (ammo < maxAmmo&&clip > 0 && isActive)
	{
		isReload = true;
		if (reloadTimer.wait(reloadDelay) == true)
		{
			if (clip >= maxAmmo)
			{
				clip -= maxAmmo - ammo;
				ammo = maxAmmo;
			}
			else
			{
				if (ammo + clip >= maxAmmo)
				{
					clip -= maxAmmo - ammo;
					ammo = maxAmmo;
				}
				else
				{
					ammo += clip;
					clip = 0;
				}
			}
			isReload = false;
		}
	}
}

void Weapon::attach()
{
	sprite.setPosition(parent->getSprite().getPosition().x, parent->getSprite().getPosition().y);
	sprite.setRotation(parent->getSprite().getRotation());
}