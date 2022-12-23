#include "Enemy.h"
#include "Base.h"
#include "AssetManager.h"
#include <fstream>
#include <iostream>
#include "Bullet.h"
#include "Parent.h"
#define _USE_MATH_DEFINES

using namespace generalStuff;
using namespace std;

std::vector<Enemy> Enemy::enemies;

Enemy::Enemy()
{
	//initialize bot parameters
	speed = 0.0005;
	health = 100;
	damageFromShuriken = 5;
	damageFromHit = 10;
	name = "Enemy";
	sprite.setPosition(rand() % 10000, rand() % 10000);
}

void Enemy::addEnemy()
{
	//add bot to array
	enemies.push_back(Enemy());

	enemies.back().texture = AssetManager::manageTexture("Content/mainsprite.png");
	enemies.back().sprite.setTexture(*enemies.back().texture);
	enemies.back().sprite.setOrigin(enemies.back().texture->getSize().x / 2, enemies.back().texture->getSize().y / 2);
}

void Enemy::destroyAll()
{
	//destroy all bots
	enemies.clear();
}

void Enemy::playEnemy(sf::RenderWindow& window,Character&character,double dt)
{
	//loop for each enemy work
	for (int i = 0; i < enemies.size(); i++)
	{
	//Enemy work
		//point distance
		sf::Vector2f dEnemyChar = character.getSprite().getPosition() - enemies.at(i).sprite.getPosition();
		//distance
		double hEnemyChar = generalStuff::makeDistance(dEnemyChar);
		//angle attack
		double alpha = -generalStuff::slope(dEnemyChar)+180;
		//samurai near damage
		if (hEnemyChar <= 300 && character.getIsHit()&& alpha >= character.getSprite().getRotation() - 30 && alpha <= character.getSprite().getRotation() + 30)
		{
			enemies[i].health -= 250;
		}
		//check intertsection of character and bot to change movement and attack state
		bool intersected = enemies[i].sprite.getGlobalBounds().intersects(character.getSprite().getGlobalBounds());
		//draw distance (if bot is out of view)
		if (hEnemyChar <= generalStuff::getLOD())
			window.draw(enemies.at(i).sprite);
		//shuriken logic when bot throw it
		Bullet::playBullet(nullptr,&enemies[i],nullptr,dt);
		//vector move for bot 
		sf::Vector2f forward = normalize(dEnemyChar);
		//rotate to character
		enemies.at(i).sprite.setRotation(generalStuff::slope(dEnemyChar));

		//move if is not intersected with character
		if (!intersected)
			enemies[i].sprite.move(forward.x * enemies[i].speed * dt, forward.y * enemies[i].speed * dt);
		
		//
		if (enemies.at(i).attackTimerByWeapon.delay(0.5) && !intersected&& hEnemyChar <= 1600)
		{
			Bullet::addBullet(enemies[i].damageFromShuriken, dEnemyChar,enemies[i].sprite.getPosition(), enemies[i].sprite.getRotation(), &enemies.at(i));
		}
		//hit character by sword if bot is near
		if (intersected && enemies[i].attackNearTimer.delay(0.8))
		{
			character.takeDamage(enemies[i].getDamageFromHit());
		}

		//make death bot logic 
		if (enemies[i].getHealth() <= 0) 
		{
			//erase from array
			enemies.erase(enemies.begin() + i);
		}
	}
}