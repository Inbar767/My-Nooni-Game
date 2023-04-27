#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

//A class for all game's sounds
class SoundManage
{
public:

	enum SoundGameType {
		MOUSE_CLICKED_SOUND,
		HAPPY_PET_SOUND
	};

	enum SoundActionType {
		PET_SOUND,
		SHOWER_SOUND,
		EAT_SOUND,
		GROW_SOUND,
		SLEEP_SOUND,
		PLAY_SOUND
	};

	enum SoundBackgroundType {
		MAIN_GAME_SOUND,
		SPEAK_STATE_SOUND
	};

	//Constructor
	SoundManage(gameDataRef data);
	//Destructor
	~SoundManage() {}
	//Gets if sound is on or not
	bool getIsSound();
	//Sets sounds volume - off or on
	void setSound();
	//Gets a sound number and switches the background sound 
	void switchBackground(SoundManage::SoundBackgroundType sound);
	//Gets a game sound number and plays it 
	void playGameSound(SoundManage::SoundGameType sound);
	//Gets an action sound number and plays it 
	void playActionSound(SoundManage::SoundActionType sound);
	//Gets a word number, plays it and returns it's time
	float speak(int word);
	//Gets a word number to learn, plays it and returns it's time
	float learn(int word);
	//Stops action and speaking sounds
	void stop();
	//Pauses all played sounds
	void pause();
	//Resume all paused sounds
	void resume();
	
private:
	//Loads all sounds
	void loadSounds();

	std::vector <sf::SoundBuffer> actionsSoundBuffer;
	std::vector <sf::SoundBuffer> gameSoundBuffer;
	std::vector <sf::SoundBuffer> speakBuffer;
	std::vector <sf::SoundBuffer> learnBuffer;
	std::vector <sf::SoundBuffer> backgroundBuffer;

	sf::Sound backgroundSound;
	sf::Sound actionSound;
	sf::Sound gameSound;
	sf::Sound speakSound;

	int actionSoundPlaying;
	int speakSoundPlaying;
	bool isSound; //Is sound on or off

	gameDataRef data;

	const int BACKGROUND_VOLUME = 30;
	const int GAME_VOLUME = 50;
	const int ACTION_VOLUME = 100;
	const int NO_SOUND = -1;
};
