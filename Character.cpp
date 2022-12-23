#include "Character.h"

 
Character::Character()
{
	//name for damage check in rocket,bullet,shuriken
	name = "Character";
}  





//void Character::save()
//{
//	ofstream write;
//	write.open("character.txt");
//
//	write << "posx:" << sprite.getPosition().x << endl;
//	write << "posy:" << sprite.getPosition().y << endl;
//	write << "health:" << health << endl;
//	write << "sprintspeed:" << sprintSpeed << endl;
//	write << "walkspeed:" << walkSpeed << endl;
//	write << "damagefromshuriken:" << damageFromShuriken << endl;
//	write << "damagefromsword:" << damageFromHit << endl;
//
//	write.close();
//}
//
//void Character::load(bool isRevive)
//{
//	ifstream load;
//	load.open("character.txt");
//	if (load.eof()==false)
//	{
//		sprite.setPosition(0, 0);
//		health = 100;
//		maxHealth = 100;
//		sprintSpeed = 0.008;
//		walkSpeed = 0.006;
//		damageFromShuriken = 20;
//		damageFromHit = 40;
//		speed = walkSpeed;
//	}
//
//	string line,name;
//	while (getline(load, line))
//	{
//		double value = getParameter(line, name);
//		if (name == "posx")
//			sprite.setPosition(value, sprite.getPosition().y);
//		else if (name == "posy")
//			sprite.setPosition(sprite.getPosition().x, value);
//		else if (name == "health")
//			health = value;
//		else if (name == "sprintspeed")
//			sprintSpeed = value;
//		else if (name == "walkspeed")
//			walkSpeed = value;
//		else if (name == "damagefromshuriken")
//			damageFromShuriken = value;
//		else if (name == "damagefromsword")
//			damageFromHit = value;
//	}
//
//	if (isRevive == true)
//		health = maxHealth;
//}