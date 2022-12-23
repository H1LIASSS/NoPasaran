#include "Player.h"
#include "Base.h"
#include <iostream>
#include "Base.h"
#include "AssetManager.h"

using namespace generalStuff;
using namespace std;

Player::Player()
{
	texture = AssetManager::manageTexture("Content/mainsprite.png");
	sprite.setTexture(*texture);
	sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
	weapon->setIsActive(false);
	isNear = true;
	health = 245;
	maxHealth = health;
	sprintSpeed = 0.00075;
	walkSpeed = 0.0005;
	speed = walkSpeed;
	diagonal = sqrt((sprite.getTexture()->getSize().x * sprite.getTexture()->getSize().x) + (sprite.getTexture()->getSize().x * sprite.getTexture()->getSize().x))*4;
}

void Player::setIsNear()
{
	//change type of fight
	if (isNear)
	{
		weapon->setIsActive(true);
		isNear = false;
	}
	else
	{
		weapon->setIsActive(false);
		isNear = true;
	}
}

void Player::hit()
{
	if (!isNear)
	{
		weapon->fire();
	}
	else if  (isNear&& attackTimer.delay(0.2) == true)
	{
		isHit = true;
	}
	else if(isNear&& attackTimer.delay(0.2) == false)
		isHit = false;
}

void Player::collision(Level level)
{
	for (int i = 0; i < level.getObjects().size(); i++)
	{
		if (makeDistance(level.getObjects()[i].getSprite().getPosition() - sprite.getPosition()) <= level.getObjects()[i].getDiagonal() + diagonal)
		{
			if (sprite.getGlobalBounds().intersects(level.getObjects()[i].getRect()))
			{
				sprite.setPosition(vec);
				break;
			}
		}
		else
			vec = sprite.getPosition();
	}
}