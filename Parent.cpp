#include "Parent.h"

void Parent::takeDamage(double damage)
{
	health -= damage;
}

void Parent::isDown(bool v)
{
	down = v;
}
void Parent::isUp(bool v)
{
	up = v;
}
void Parent::isLeft(bool v)
{
	left = v;
}
void Parent::isRight(bool v)
{
	right = v;
}

void Parent::move(int vecX, int vecY, double dt)
{
	sprite.move(speed * vecX * dt, speed * vecY * dt);
}

void Parent::setRotation(double angle)
{/*
	if (angle >= 135 && angle >= -135)
	{
		rotation = 1;
	}
	else if (angle <= 180 && angle >= 90)
	{
		rotation = 2;
	}
	else if (angle <= 135 && angle >= 45)
	{
		rotation = 3;
	}
	else if (angle >= 30 && angle <= 45)
	{
		rotation = 4;
	}
	else if (angle >= 0 && angle <= 30)
	{
		rotation = 5;
	}
	else if (angle <= 0 && angle >= -45)
	{
		rotation = 6;
	}
	else if (angle <= -45 && angle >= -100)
	{
		rotation = 7;
	}
	else if (angle >= -180 && angle <= 100)
	{
		rotation = 8;
	}*/
	sprite.setRotation(-angle);
}

void Parent::setSpeed(double param)
{
	speed = param;
}

//double Parent::getParameter(string& line, string& name)
//{
//	int i = line.find(':');
//	name = line.substr(0, i);
//	string value = line.substr(i + 1, line.length());
//	double dValue = stod(value);
//	return dValue;
//}

bool Parent::operator!=(Parent* other)
{
	if(this!=other)
	{
		return true;
	}
	else
	{
		return false;
	}
}