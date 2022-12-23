#include "Bullet.h"
#include "Base.h"
#include "AssetManager.h"
#include <iostream>

using namespace generalStuff;

std::vector<Bullet> Bullet::bullets;

Bullet::Bullet(const double dam, sf::Vector2f distance, const sf::Vector2f pos, const double slope, Character* obj)
{
	initiator = obj;

	forward = generalStuff::normalize(distance);

	speed = 0.0003;

	damage = dam;

	sprite.setPosition(pos);
	sprite.setRotation(slope);

	texture = AssetManager::manageTexture("Content/mainsprite.png");
	sprite.setTexture(*texture);
	sprite.setScale(0.5, 0.5);
	sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);


	rad = texture->getSize().x / 2;
}

Bullet::Bullet()
{
}

void Bullet::addBullet(const double damage, sf::Vector2f distance, const sf::Vector2f pos, const double slope, Character* obj)
{
	bullets.push_back(Bullet(damage, distance, pos, slope, obj));
}

void Bullet::playBullet(sf::RenderWindow* window,Character* character, Level* level,double dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].sprite.move(bullets[i].speed * bullets[i].forward.x * dt, bullets[i].speed * bullets[i].forward.y * dt);
		
		if (window != nullptr)
		{
			double hCharacterShuriken = generalStuff::makeDistance(character->getSprite().getPosition() - bullets[i].sprite.getPosition());
			if (hCharacterShuriken <= generalStuff::getLOD())
				window->draw(bullets[i].sprite);
		}

		if (bullets[i].lifeTime.delay(3)==true)
		{
			bullets.erase(bullets.begin() + i);
		}
		else if (bullets[i].sprite.getGlobalBounds().intersects(character->getSprite().getGlobalBounds()) && bullets[i].initiator != character && character->className() != bullets[i].initiator->className())
		{
			character->takeDamage(bullets[i].damage);
		}
		else if (level != nullptr)
		{
			for (int j = 0; j < level->getObjects().size(); j++)
			{
				if (makeDistance(level->getObjects()[j].getSprite().getPosition() - bullets[i].sprite.getPosition()) <= level->getObjects()[j].getDiagonal() + bullets[i].getRad())
				{
					if ((bullets[i].sprite.getGlobalBounds().intersects(level->getObjects()[j].getRect())))
					{
						bullets.erase(bullets.begin() + i);
					}
				}
			}

		}
	}
}