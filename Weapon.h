#pragma once

#include "World.h"
class Character;

enum class WeaponType
{
	pistol = 0
};

class Weapon : public World 
{
protected:
	WeaponType weapon;
	Character* parent;
	Timer fireTimer;
	Timer reloadTimer;
	float damage = 0;
	int maxAmmo = 0;
	int ammo=0;
	int clip = 0;
	float fireDelay = 0;
	float reloadDelay=0;
	bool isReload = false;
	bool isActive = true;
public:
	Weapon();
	float getFireDelay() { return fireDelay; };
	WeaponType getWeapon() { return weapon; };
	void setIsActive(bool x) { isActive = x; };
	bool getIsActive() { return isActive; };
	virtual void fire();
	int getClip() { return clip; };
	int getAmmo() { return ammo; };
	bool getIsReload() { return isReload; };
	void attach();
	void reload();
};

