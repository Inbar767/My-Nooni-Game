#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//A class for loading sounds and textures files from computer to the game
class AssetManager
{
public:
	//Gets two strings, name for texture and the file name and loads the file into textures
	void loadTexture(std::string, std::string);
	//Gets a name and returns a texture by the name from textures
	sf::Texture& getTexture(std::string);
	//Gets two strings, name for sound and the file name and loads the file into soundBuffers
	void loadSoundBuffer(std::string, std::string);
	//Gets a name and returns a soundBuffer by the name from soundBuffers
	sf::SoundBuffer& getSoundBuffer(std::string);

private:
	std::map <std::string, sf::Texture> textures; //Holds loaded textures
	std::map <std::string, sf::SoundBuffer> soundBuffers; //Holds loaded soundBuffers
};