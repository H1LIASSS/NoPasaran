#include "Pistol.h"
#include "AssetManager.h"
#include "Base.h"
#include "Bullet.h"

Pistol::Pistol(Character* x)
{
	parent = x;
	texture = AssetManager::manageTexture("Content/mainsprite.png");
	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2,0);
	sprite.setScale(0.5, 0.5);
	damage = 200;
	maxAmmo = 16;
	ammo = 100000000;
	clip = 100000000;
	fireDelay = 0.1;
	reloadDelay = 1.5;
}

void Pistol::fire()
{
	if (ammo != 0&&fireTimer.delay(fireDelay)&&!isReload&&isActive)
	{
		ammo--;
		Bullet::addBullet(damage, generalStuff::getCursorPositionInWorld() - sprite.getPosition(), sprite.getPosition(), sprite.getRotation(), parent);
	}
}