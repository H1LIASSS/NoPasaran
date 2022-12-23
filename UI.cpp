#include "UI.h"
#include "Character.h"
#include "AssetManager.h"
#include "Base.h"
#include <iostream>
using namespace generalStuff;

//initialization global variables by namespace
bool isClicked = false;
bool isHold = false;
void Controll::setIsHold(bool x) { isHold = x; };
bool Controll::getIsHold() { return isHold; };
void Controll::setIsClick(bool x) { isClicked = x; };
bool Controll::getIsClick() { return isClicked; };

UI::UI()
{
	tCursor = AssetManager::manageTexture("Content/cursor.png");
	cursor.setTexture(*tCursor);
	cursor.setOrigin(tCursor->getSize().x / 2, tCursor->getSize().y / 2);
	cursor.setScale(0.125, 0.125);
	
	settingsText_P_Btn.setName(sf::Vector2f(1000, 0), "settings", 150);
	playText_MM_Btn.setName(sf::Vector2f(-1000, -350), "play", 150);
	settingsText_MM_Btn.setName(sf::Vector2f(-1000, -175), "settings", 150);
	continueText_P_Btn.setName(sf::Vector2f(0, -750), "continue", 300);
	quitText_Btn.setName(sf::Vector2f(-1000, 0), "quit", 150);
	back_Btn.setName(sf::Vector2f(1000, -200), "back", 150);
	sizeWindowText_S_Btn.setName(sf::Vector2f(300, -1280), "windowed", 150);
	sizeWindowText_S.setName(sf::Vector2f(-250, -1280), "screen size:", 150);
	soundValueText_S.setName(sf::Vector2f(-183, -1100), "sound volume:", 150);
	restart_Btn_R.setName(sf::Vector2f(0,-750), "restart", 300);
	ammouCountText.setName(sf::Vector2f(0, -750), "0/0", 150);


	soundScroll.setSroll(sf::Vector2f(250,-1050), 1000);
}

void UI::setAmmoCountText(Character* w)
{
	if (w->getWeapon()->getIsActive())
	{
		if(!w->getWeapon()->getIsReload())
		ammouCountText.setText(to_string(w->getWeapon()->getAmmo()) + "/" + to_string(w->getWeapon()->getClip()));
		else
			ammouCountText.setText("reload");
	}
	else if(!w->getWeapon()->getIsActive())
	{
		ammouCountText.setText("No weapon");
	}
	ammouCountText.setPosition(sf::Vector2f(w->getSprite().getPosition().x + 700, w->getSprite().getPosition().y+500));
}

void UI::setHearts(double health)
{
	t = health / 5;
	fillBar = ceil(health / t);

	textureHearts = AssetManager::manageTexture("Content/heart.png");
	for (int i = 0; i < 5; i++)
	{
		hearts[i].setTexture(*textureHearts);
		hearts[i].setScale(0.25, 0.25);
		hearts[i].setOrigin(textureHearts->getSize().x / 2, textureHearts->getSize().y / 2);
	}
}

Name::Name()
{
	font.loadFromFile("Content/BebasNeue-Regular.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
}

void Scroll::setSroll(sf::Vector2f p, float l)
{
	box.setSize(sf::Vector2f(50, 100));
	box.setOutlineColor(sf::Color::Green);
	box.setOutlineThickness(5);
	box.setOrigin(box.getSize().x / 2, box.getSize().y / 2);
	box.setPosition(p.x , p.y);
	line.setPosition(p.x, p.y);
	line.setSize(sf::Vector2f(l, 5));
}


float Scroll::scroll()
{
	if (isHold)
	{
		if (getCursorPositionInWorld().x < (box.getSize().x / 2) + box.getPosition().x + 100 && getCursorPositionInWorld().x > box.getPosition().x - (box.getSize().x / 2) - 100&& getCursorPositionInWorld().y < (box.getSize().y / 2) + box.getPosition().y&& getCursorPositionInWorld().y > box.getPosition().y-(box.getSize().y / 2))
		{
			isBoxClicked = true;
			if (getCursorPositionInWorld().x < line.getPosition().x + line.getSize().x && getCursorPositionInWorld().x > line.getPosition().x)
			{
				box.setPosition(getCursorPositionInWorld().x, box.getPosition().y);
			}
		}
		else if (getCursorPositionInWorld().x < (box.getSize().x / 2) + box.getPosition().x + 100 && getCursorPositionInWorld().x > box.getPosition().x - (box.getSize().x / 2) - 100 && isBoxClicked)
		{
			if (getCursorPositionInWorld().x < line.getPosition().x + line.getSize().x && getCursorPositionInWorld().x > line.getPosition().x)
			{
				box.setPosition(getCursorPositionInWorld().x, box.getPosition().y);
			}
		}
	}
	else if(!isHold)
		isBoxClicked = false;

	if(((box.getPosition().x - line.getPosition().x) / line.getSize().x) * 100 < 1)
		return 0;
	else
	return ((box.getPosition().x - line.getPosition().x) / line.getSize().x)*100;
}

void UI::setCursorSpritePosition(sf::Vector2f pos)
{
	cursor.setPosition(pos);
}

void Name::setName(sf::Vector2f pos, std::string value,int size)
{
	text.setString(value);
	text.setCharacterSize(size);
	text.setPosition(pos);
	text.setOrigin((text.getGlobalBounds().width + text.getGlobalBounds().left - text.getGlobalBounds().left) / 2, (text.getGlobalBounds().height + text.getGlobalBounds().top - text.getGlobalBounds().top) / 2);
}

void Button::setTextures(string x, string y, sf::Vector2f pos)
{
	textureN = AssetManager::manageTexture(x);
	textureH = AssetManager::manageTexture(y);
	sprite.setPosition(pos);
	sprite.setTexture(*textureN);
}

bool ButtonText::clicked()
{
	if (text.getGlobalBounds().contains(getCursorPositionInWorld()))
	{
		if (isClicked)
		{
			return true;
		}
		else if (isHovered == false)
		{
			isHovered = true;
			isNothing = false;
			text.setFillColor(sf::Color::Green);
			return false;
		}
	}
	else if(isNothing == false)
	{
		isHovered = false;
		isNothing = true;
		text.setFillColor(sf::Color::White);
		return false;
}
	}

bool Button::clicked()
{
	if (sprite.getGlobalBounds().contains(getCursorPositionInWorld()))
	{
		if (isClicked)
		{
			return true;
		}
		else if (isHovered == false)
		{
			isHovered = true;
			isNothing = false;
			sprite.setTexture(*textureH);
			return false;
		}
	}
	else if (isNothing == false)
	{
		isHovered = false;
		isNothing = true;
		sprite.setTexture(*textureN);
		return false;
	}
}

void UI::setPositionHeart(sf::Vector2f pos)
{
	hearts[0].setPosition(pos.x - 200, pos.y - 200);
	hearts[1].setPosition(pos.x - 100, pos.y - 200);
	hearts[2].setPosition(pos.x, pos.y - 200);
	hearts[3].setPosition(pos.x + 100, pos.y - 200);
	hearts[4].setPosition(pos.x + 200, pos.y - 200);
}

void UI::setTimeDraw(Character character)
{
	fillBar = ceil(character.getHealth() / t);
}