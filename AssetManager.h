#pragma once

#include <vector>
#include "World.h"

using namespace std;
using namespace sf;

class AssetManager
{
private:
	static std::map<string, Texture> textures;
	static std::map<string, sf::Sound> sounds;
	static std::map<string, SoundBuffer> buffers;

	static SoundBuffer* getBuffer(string path);
public:
	static sf::Texture* manageTexture(string path);
	static void updateVolume();
	static void stopSound(string path);
	static void playSound(string path);
};