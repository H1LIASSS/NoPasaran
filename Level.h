#pragma once 

#include <vector>
#include "World.h"
#include <map>
#include "tinyxml.h"

class Object
{
	double diagonal;
	sf::Rect<float> rect;
	sf::Sprite sprite;
public:
	Object(sf::Rect<float> a, sf::Sprite b, double c) { rect = a; sprite = b; diagonal = c; };
	double getDiagonal() { return diagonal; };
	sf::Rect<float> getRect(){ return rect; };
	sf::Sprite getSprite() { return sprite; };
};

struct Layer
{
	int opacity;
	std::vector<sf::Sprite> tiles;
};

class Level
{
private:
	int width, height, tileWidth, tileHeight, tileN;
	int firstTileID;
	sf::Rect<float> drawingBounds;
	sf::Texture tilesetImage;
	std::vector<int> matrix;
	std::vector<Object> objects;
	std::vector<Layer> layers;
public:
	bool loadFromFile(std::string levelName,std::string tileName, std::string image);
	void draw(sf::RenderWindow& window, sf::Vector2f pos);
	std::vector<Object> getObjects() { return objects; };
};