#include "AssetManager.h"
#include "World.h"
#include <iostream>
#include <string>
#include "Base.h"

using namespace std;

std::map<string,Texture> AssetManager::textures;
std::map<string, SoundBuffer> AssetManager::buffers;
std::map<string, Sound> AssetManager::sounds;

sf::Texture* AssetManager::manageTexture(string path)
{
	//import/search texture
	if (textures.find(path) != textures.end())
	{
		return &textures[path];
	}
	textures[path].loadFromFile(path);
	return &textures[path];
}

SoundBuffer* AssetManager::getBuffer(string path)
{
	//serach or import buffer
	if (buffers.find(path) != buffers.end())
	{
		return &buffers[path];
	}
	buffers[path].loadFromFile(path);
	return &buffers[path];
}
void AssetManager::playSound(string path)
{
	//search sound and if search is failed sound will be imported
	if (sounds.find(path) != sounds.end())
	{
		sounds[path].play();
	}
	else
	{
		sounds[path].setBuffer(*getBuffer(path));
		sounds[path].play();
	}
}
void AssetManager::updateVolume()
{
	//set volume for each sound
	for (auto& item : sounds)
	{
		item.second.setVolume(settings::getVolume());
	}
}
void AssetManager::stopSound(string path)
{
	//search and stop sound work 
	if (sounds.find(path) != sounds.end())
	{
		sounds[path].stop();
	}
}