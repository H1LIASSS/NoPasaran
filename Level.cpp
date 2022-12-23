#include "Level.h"
#include <iostream>
#include "Base.h"
#include <sstream>

using namespace std;

//int Object::getPropertyInt(std::string name)
//{
//	return atoi(properties[name].c_str());
//}
//
//float Object::getPropertyFloat(std::string name)
//{
//	return strtod(properties[name].c_str(), NULL);
//}
//
//std::string Object::getPropertyString(std::string name)
//{
//	return properties[name];
//}

bool Level::loadFromFile(std::string levelName,std::string tileName,std::string image) 
{
	TiXmlDocument levelFile(levelName.c_str());

	if (!levelFile.LoadFile())
	{
		std::cout << "Loading level \"" << levelName << "\" failed." << std::endl;
		return false;
	}

	TiXmlElement* map;
	map = levelFile.FirstChildElement("map");

	width = atoi(map->Attribute("width"));
	height = atoi(map->Attribute("height"));
	tileWidth = atoi(map->Attribute("tilewidth"));
	tileHeight = atoi(map->Attribute("tileheight"));

	TiXmlDocument tileFile(tileName.c_str());
	TiXmlElement* tilesetElement = tileFile.FirstChildElement("tileset");

	firstTileID = atoi(map->FirstChildElement("tileset")->Attribute("firstgid"));

	std::string imagepath = image;
	sf::Image img;

	if (!img.loadFromFile(imagepath))
	{
		std::cout << "Failed to load tile sheet." << std::endl;
		return false;
	}


	img.createMaskFromColor(sf::Color(255, 255, 255));
	tilesetImage.loadFromImage(img);
	tilesetImage.setSmooth(false);

	int columns = tilesetImage.getSize().x / tileWidth;
	int rows = tilesetImage.getSize().y / tileHeight;

	std::vector<sf::Rect<int>> subRects;

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
		{
			sf::Rect<int> rect;

			rect.top = y * tileHeight;
			rect.height = tileHeight;
			rect.left = x * tileWidth;
			rect.width = tileWidth;

			subRects.push_back(rect);
		}

	TiXmlElement* layerElement;
	layerElement = map->FirstChildElement("layer");

	while (layerElement)
	{
		Layer layer;

		if (layerElement->Attribute("opacity") != NULL)
		{
			float opacity = strtod(layerElement->Attribute("opacity"), NULL);
			layer.opacity = 255 * opacity;
		}
		else
		{
			layer.opacity = 255;
		}

		TiXmlElement* layerDataElement;
		layerDataElement = layerElement->FirstChildElement("data");

		if (layerDataElement == NULL)
		{
			std::cout << "Bad map. No layer information found." << std::endl;
		}

		string editTileMatrix = layerDataElement->GetText();
		for (int i = 0; i < editTileMatrix.size(); i++)
		{
			if (editTileMatrix[i] == ' ')
			{
				editTileMatrix[i] = ',';
			}
		}
		istringstream tileMatrix(editTileMatrix);
		string saveElementTileMatrix;
		while (getline(tileMatrix, saveElementTileMatrix, ','))
		{
			if(saveElementTileMatrix.size()!=0)
			matrix.push_back(stoi(saveElementTileMatrix));
		}

		int x = 0;
		int y = 0;
		for (int i = 0; i < matrix.size(); i++)
		{
			int tileGID = matrix[i];
			int subRectToUse = tileGID - firstTileID;

			if (subRectToUse >= 0)
			{
				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(subRects[subRectToUse]);
				sprite.setPosition(x * tileWidth, y * tileHeight);
				sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

				layer.tiles.push_back(sprite);
			}

			x++;
			if (x >= width)
			{
				x = 0;
				y++;
				if (y >= height)
					y = 0;
			}
		}
		layers.push_back(layer);

		layerElement = layerElement->NextSiblingElement("layer");
	}

	TiXmlElement* objectGroupElement;

	if (map->FirstChildElement("objectgroup") != NULL)
	{
		objectGroupElement = map->FirstChildElement("objectgroup");
		while (objectGroupElement)
		{
			TiXmlElement* objectElement;
			objectElement = objectGroupElement->FirstChildElement("object");

			while (objectElement)
			{
				std::string objectType;
				if (objectElement->Attribute("type") != NULL)
				{
					objectType = objectElement->Attribute("type");
				}
				std::string objectName;
				if (objectElement->Attribute("name") != NULL)
				{
					objectName = objectElement->Attribute("name");
				}
				int x = atoi(objectElement->Attribute("x"));
				int y = atoi(objectElement->Attribute("y"));

				int width, height;

				sf::Sprite sprite;
				sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
				sprite.setPosition(x, y);

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}
				else
				{
					width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
					height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
					sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
				}

				sf::Rect <float> objectRect;
				objectRect.top = y;
				objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;

				double diagonal = (sqrt(pow(height, 2) + pow(width, 2)));

				Object object(objectRect, sprite, diagonal);

				TiXmlElement* properties;
				properties = objectElement->FirstChildElement("properties");
				if (properties != NULL)
				{
					TiXmlElement* prop;
					prop = properties->FirstChildElement("property");
					if (prop != NULL)
					{
						while (prop)
						{
							std::string propertyName = prop->Attribute("name");
							std::string propertyValue = prop->Attribute("value");

							prop = prop->NextSiblingElement("property");
						}
					}
				}

				objects.push_back(object);

				objectElement = objectElement->NextSiblingElement("object");
			}
			objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
		}
	}
	else
	{
		std::cout << "No object layers found..." << std::endl;
	}

	return true;
}

void Level::draw(sf::RenderWindow & window, sf::Vector2f pos)
{
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
		{
			if(generalStuff::makeDistance(pos- layers[layer].tiles[tile].getPosition())<=generalStuff::getLOD())
			window.draw(layers[layer].tiles[tile]);
		}
}