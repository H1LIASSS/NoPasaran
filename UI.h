#pragma once

#include "Character.h"

namespace Controll
{
	void setIsHold(bool x);
	bool getIsHold();
	bool getIsClick();
	void setIsClick(bool x);
};

 class Scroll
 {
 private:
	 bool isBoxClicked = false;
	 sf::RectangleShape box;
	 sf::RectangleShape line;
 public:
	 void setSroll(const sf::Vector2f point, const float length);
	 float scroll();
	 sf::RectangleShape getLine() { return line; };
	 sf::RectangleShape getBox() { return box; };
 };
class Name 
{
protected:
	sf::Text text;
	sf::Font font;
public:
	Name();
	void setName(sf::Vector2f pos, std::string value, int size);
	void setText(string x) { text.setString(x); };
	void setPosition(sf::Vector2f p) { text.setPosition(p); };
	sf::Text getText() { return text; };
};
class ButtonText : public Name
{
protected:
	bool isNothing = true;
	bool isHovered = false;
public:
	virtual bool clicked();
};
class Button : protected ButtonText
{
private:
	sf::Sprite sprite;
	sf::Texture* textureN;
	sf::Texture* textureH;
public:
	void setTextures(string x, string y,sf::Vector2f pos);
	sf::Sprite getSprite() { return sprite; };
	bool clicked();
};

class UI
{
private:
	int t;
	int fillBar;
	bool isClick = false;
	bool isHold = false;
	bool flipSizeWindow = true;
	sf::Sprite hearts[5];
	sf::Texture* textureHearts;
	sf::Texture* tCursor;
	sf::Sprite cursor;
	Scroll soundScroll;
	ButtonText playText_MM_Btn;
	ButtonText settingsText_MM_Btn;
	ButtonText settingsText_P_Btn;
	ButtonText continueText_P_Btn;
	ButtonText quitText_Btn;
	ButtonText sizeWindowText_S_Btn;
	ButtonText back_Btn;
	ButtonText restart_Btn_R;
	Name ammouCountText;
	Name sizeWindowText_S;
	Name soundValueText_S;
public:
	UI();
	int getFillBar() { return fillBar; };
	void setPositionHeart(sf::Vector2f pos);
	void setTimeDraw(Character character);
	bool getFlipSizeWindow() { return flipSizeWindow; };
	void setFlipSizeWindow(bool x) { flipSizeWindow = x; };
	void setCursorSpritePosition(sf::Vector2f pos);
	void setHearts(double hp);
	sf::Sprite getCursor() { return cursor; };
	ButtonText* getPlayText_MM_Btn() { return &playText_MM_Btn; };
	ButtonText* getContinueText_P_Btn() { return &continueText_P_Btn; };
	ButtonText* getSettingsText_P_Btn() { return &settingsText_P_Btn; };
	ButtonText* getQuitText_Btn() { return &quitText_Btn; };
	ButtonText* getSettingsText_MM_Btn() { return &settingsText_MM_Btn; };
	ButtonText* getSizeWindowText_Btn_S() { return &sizeWindowText_S_Btn; };
	ButtonText* getBack_Btn() { return &back_Btn; };
	ButtonText* getRestart_Btn() { return &restart_Btn_R; };
	Scroll* getSoundScroll() { return &soundScroll; };
	void setAmmoCountText(Character*);
	sf::Text getAmmoCountText() { return ammouCountText.getText(); };
	sf::Text getSoundValueText_S() { return soundValueText_S.getText(); };
	sf::Text getSizeWindowText_S() { return sizeWindowText_S.getText(); };
	sf::Sprite getHeartSprite(int i) { return hearts[i]; };
};