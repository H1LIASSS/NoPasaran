#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"

#include <iostream>

#include "World.h"
#include "UI.h"
#include "Enemy.h"
#include "Level.h"
#include "Player.h"
#include "AssetManager.h"
#include "Bullet.h"
#include "Base.h"
#include "Timer.h"

using namespace std;
using namespace sf;
using namespace generalStuff;


enum class GameState
{
	mainMenu, pauseMenu, settings_MM, settings_P, restart
};

int main()
{
	sf::VideoMode screenSize = sf::VideoMode(sf::VideoMode().getDesktopMode().width, sf::VideoMode().getDesktopMode().height);
	sf::RenderWindow window(sf::VideoMode(screenSize.width / 1.5, screenSize.height / 1.5), "NoPasaran");
	window.setMouseCursorVisible(false);

	bool isRestart = true;

	UI user_interface;

	while (isRestart)
	{
		isRestart = false;

		Player* character = new Player();
		user_interface.setHearts(character->getHealth());

		Enemy::destroyAll();

		generalStuff::loadValueOfDrawDistance(window);

		Level level;
		level.loadFromFile("Content/untitled.tmx", "Content/tileset.tsx", "Content/image.png");

		sf::View view;
		view.zoom(3);
		double prop = (double(screenSize.width)) / screenSize.height;
		view.setViewport(sf::FloatRect(0, 0, 1, prop));
		window.setView(view);

		sf::Vector2f centerViewCharacter;
		sf::Vector2f divideViewCharacter(2.5, 2.5);

		Event event;

		Clock current;
		current.restart();

		int fps = 0;

		GameState gameState = GameState::mainMenu;

		AssetManager::playSound("Content/LetGo.wav");

		Clock c;

		for (int i = 1; i <= 100; i++)
		{
			Enemy::addEnemy();
		}
		while (window.isOpen() && !isRestart)
		{
			window.clear();

			/*cout << sf::Mouse::getPosition(window).x << ":" << sf::Mouse::getPosition(window).y << endl;*/

			AssetManager::updateVolume();

			generalStuff::setCursorPositionInWorld(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

			if (current.getElapsedTime().asMilliseconds() <= 1000) {
				fps++;
			}
			else {
				std::cout << "FPS" << ":" << fps << endl;
				fps = 0;
				current.restart();
			}

			int sizeBeforeResizeX = window.getSize().x;
			int sizeBeforeResizeY = window.getSize().y;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Resized)
				{
					if (window.getSize().x != sizeBeforeResizeX)
						window.setSize(sf::Vector2u(window.getSize().x, window.getSize().x / prop));
					else
						window.setSize(sf::Vector2u(window.getSize().y * prop, window.getSize().y));
				}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
					Controll::setIsClick(true);
				else
					Controll::setIsClick(false);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					Controll::setIsHold(true);
				else
					Controll::setIsHold(false);

				if (event.type == sf::Event::MouseWheelMoved && !generalStuff::getIsPause())
				{
					character->setIsNear();
				}

				if (event.type == sf::Event::Closed)
					window.close();

				if (event.key.code == sf::Keyboard::Escape && !generalStuff::getIsPause())
				{
					gameState = GameState::pauseMenu;
					generalStuff::setIsPause(true);
				}

				if (event.key.code == sf::Keyboard::R)
				{
					character->getWeapon()->reload();
				}

				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::A:
						character->isLeft(false);
						break;
					case sf::Keyboard::D:
						character->isRight(false);
						break;
					case sf::Keyboard::W:
						character->isUp(false);
						break;
					case sf::Keyboard::S:
						character->isDown(false);
						break;
					case sf::Keyboard::LShift:
						character->setSpeed(character->getWalkSpeed());
						break;
					case sf::Event::KeyPressed:
						switch (event.key.code)
						{
						case sf::Keyboard::LShift:
							character->setSpeed(character->getSprintSpeed());
							break;
						}
						break;
					}
				}
			}
			if (generalStuff::getIsPause())
			{
				view.setCenter(sf::Vector2f(0, 0));

				switch (gameState)
				{
				case GameState::mainMenu:
					//play button (spawn character on game begin)
					if (user_interface.getPlayText_MM_Btn()->clicked() == true)
					{
						setIsPause(false);
					};
					//quit game button
					if (user_interface.getQuitText_Btn()->clicked() == true)
					{
						window.close();
					}
					//settings button
					if (user_interface.getSettingsText_MM_Btn()->clicked() == true)
					{
						gameState = GameState::settings_MM;
					}
					//draw buttons
					window.draw(user_interface.getPlayText_MM_Btn()->getText());
					window.draw(user_interface.getSettingsText_MM_Btn()->getText());
					window.draw(user_interface.getQuitText_Btn()->getText());
					break;
				case GameState::pauseMenu:
					//continue game
					if (user_interface.getContinueText_P_Btn()->clicked() == true)
					{
						generalStuff::setIsPause(false);
					}
					//quit game button
					if (user_interface.getQuitText_Btn()->clicked() == true)
					{
						window.close();
					}
					//settings button
					if (user_interface.getSettingsText_P_Btn()->clicked() == true)
					{
						gameState = GameState::settings_P;
					}
					//draw buttons
					window.draw(user_interface.getContinueText_P_Btn()->getText());
					window.draw(user_interface.getQuitText_Btn()->getText());
					window.draw(user_interface.getSettingsText_P_Btn()->getText());
					break;
				case GameState::settings_P:
					if (user_interface.getSizeWindowText_Btn_S()->clicked() == true)
					{
						switch (user_interface.getFlipSizeWindow())
						{
						case true:
							user_interface.getSizeWindowText_Btn_S()->setText("FULL");
							window.setPosition(sf::Vector2i(-8, -31));
							window.setSize(sf::Vector2u(screenSize.width, screenSize.height));
							generalStuff::loadValueOfDrawDistance(window);
							user_interface.setFlipSizeWindow(false);
							break;
						case false:
							user_interface.getSizeWindowText_Btn_S()->setText("windowed");
							window.setPosition(sf::Vector2i(screenSize.width / 6, screenSize.height / 6));
							window.setSize(sf::Vector2u(screenSize.width / 1.5, screenSize.height / 1.5));
							generalStuff::loadValueOfDrawDistance(window);
							user_interface.setFlipSizeWindow(true);
							break;
						}
					}
					window.draw(user_interface.getSizeWindowText_Btn_S()->getText());
					window.draw(user_interface.getSizeWindowText_S());
					if (user_interface.getBack_Btn()->clicked() == true)
					{
						gameState = GameState::pauseMenu;
					}
					window.draw(user_interface.getBack_Btn()->getText());
					window.draw(user_interface.getSoundScroll()->getBox());
					window.draw(user_interface.getSoundScroll()->getLine());
					window.draw(user_interface.getSoundValueText_S());
					settings::setVolume(user_interface.getSoundScroll()->scroll());
					break;
				case GameState::settings_MM:
					if (user_interface.getSizeWindowText_Btn_S()->clicked() == true)
					{
						switch (user_interface.getFlipSizeWindow())
						{
						case true:
							user_interface.getSizeWindowText_Btn_S()->setText("FULL");
							window.setPosition(sf::Vector2i(-8, -31));
							window.setSize(sf::Vector2u(screenSize.width, screenSize.height));
							generalStuff::loadValueOfDrawDistance(window);
							user_interface.setFlipSizeWindow(false);
							break;
						case false:
							user_interface.getSizeWindowText_Btn_S()->setText("windowed");
							window.setPosition(sf::Vector2i(screenSize.width / 6, screenSize.height / 6));
							window.setSize(sf::Vector2u(screenSize.width / 1.5, screenSize.height / 1.5));
							generalStuff::loadValueOfDrawDistance(window);
							user_interface.setFlipSizeWindow(true);
							break;
						}
					}
					if (user_interface.getBack_Btn()->clicked() == true)
					{
						gameState = GameState::mainMenu;
					}
					window.draw(user_interface.getSizeWindowText_Btn_S()->getText());
					window.draw(user_interface.getSizeWindowText_S());
					window.draw(user_interface.getBack_Btn()->getText());
					window.draw(user_interface.getSoundScroll()->getLine());
					window.draw(user_interface.getSoundScroll()->getBox());
					window.draw(user_interface.getSoundScroll()->getLine());
					window.draw(user_interface.getSoundValueText_S());
					settings::setVolume(user_interface.getSoundScroll()->scroll());
					break;
				case GameState::restart:
					if (user_interface.getRestart_Btn()->clicked() == true)
					{
						isRestart = true;
					}
					window.draw(user_interface.getRestart_Btn()->getText());
					break;
				}
			}
			else
			{
				//Level:
				level.draw(window, character->getSprite().getPosition());
				//Bullets:
				if (Bullet::getBullets() > 0)
				{
					Bullet::playBullet(&window,character, &level, generalStuff::deltaTime());
				}

				//Enemies:
				
				if(Enemy::getCount()>0)
				Enemy::playEnemy(window, *character, generalStuff::deltaTime());
					
				//Character:
				centerViewCharacter.x = character->getSprite().getPosition().x + (sf::Mouse::getPosition(window).x / divideViewCharacter.x);
				centerViewCharacter.y = character->getSprite().getPosition().y + (sf::Mouse::getPosition(window).y / divideViewCharacter.y) + 600;
				view.setCenter(centerViewCharacter);

				character->setRotation(slope(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - character->getSprite().getPosition()));

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					character->setSpeed(character->getSprintSpeed());
				}

				character->collision(level);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					character->move(0, -1, generalStuff::deltaTime());
					character->isUp(true);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					character->move(-1, 0, generalStuff::deltaTime());
					character->isLeft(true);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					character->move(0, 1, generalStuff::deltaTime());
					character->isDown(true);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					character->move(1, 0, generalStuff::deltaTime());
					character->isRight(true);
				}



				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					character->hit();
				}

				window.draw(character->getSprite());

				//Weapon(For character):
				character->getWeapon()->attach();
				if (character->getWeapon()->getIsReload())
					character->getWeapon()->reload();

				if (character->getWeapon()->getIsActive())
					window.draw(character->getWeapon()->getSprite());

				//UI(For character):
				user_interface.setPositionHeart(character->getSprite().getPosition());
				user_interface.setTimeDraw(*character);
				for (int i = 0; i < user_interface.getFillBar(); i++)
					window.draw(user_interface.getHeartSprite(i));

				user_interface.setAmmoCountText(character);
				window.draw(user_interface.getAmmoCountText());
				//destroy character
				if (character->getHealth() <= 0)
				{
					gameState = GameState::restart;
					generalStuff::setIsPause(true);
					delete character;
				}
			}

			window.setView(view);

			user_interface.setCursorSpritePosition(getCursorPositionInWorld());
			window.draw(user_interface.getCursor());

			window.display();

			generalStuff::resetClock();
		}
	}
	return 0;
}