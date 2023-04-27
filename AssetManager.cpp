#include "AssetManager.h"
#include <iostream>

//Gets two strings, name for texture and the file name and loads the file into textures
void AssetManager::loadTexture(std::string name, std::string fileName)
{
	sf::Texture texture;
	if (texture.loadFromFile(fileName))
	{
		textures[name] = texture;
	}
	else
	{
		std::cout << "Couldn't load file name called " << fileName << "\n";
	}
}

//Gets a name and returns a texture by the name from textures
sf::Texture &AssetManager::getTexture(std::string name)
{
	if (textures.contains(name))
	{
		return textures.at(name);
	}
	sf::Texture texture;
	return texture;
}

//Gets two strings, name for sound and the file name and loads the file into soundBuffers
void AssetManager::loadSoundBuffer(std::string name, std::string fileName)
{
	sf::SoundBuffer sound;
	if (sound.loadFromFile(fileName))
	{
		soundBuffers[name] = sound;
	}
	else
	{
		std::cout << "Couldn't load file name called " << fileName << "\n";
	}
}

//Gets a name and returns a soundBuffer by the name from soundBuffers
sf::SoundBuffer& AssetManager::getSoundBuffer(std::string name)
{
	if (soundBuffers.contains(name))
	{
		return soundBuffers.at(name);
	}
	sf::SoundBuffer sound;
	return sound;
}