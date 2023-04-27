#include "SoundManage.h"
#include "Definitions.h"
#include <iostream>

//Constructor getss a data
SoundManage::SoundManage(gameDataRef data) : 
	data(data), isSound(true), actionSoundPlaying(NO_SOUND), speakSoundPlaying(NO_SOUND)
{
	loadSounds();
	//Sets background sound
	backgroundSound.setBuffer(backgroundBuffer.at(SoundManage::SoundBackgroundType::MAIN_GAME_SOUND));
	backgroundSound.play();
	//Sets volume for each sound
	backgroundSound.setVolume(BACKGROUND_VOLUME);
	gameSound.setVolume(GAME_VOLUME);
	speakSound.setPitch(1.5);

	backgroundSound.setLoop(true);
	actionSound.setLoop(true);
}

//Loads all sounds
void SoundManage::loadSounds()
{
	for (int i = 0; i < 2; i++)
	{
		data->assets.loadSoundBuffer("Game Sound " + std::to_string(i), GAME_SOUND + std::to_string(i) + ".wav");
		gameSoundBuffer.push_back(data->assets.getSoundBuffer("Game Sound " + std::to_string(i)));

		data->assets.loadSoundBuffer("Background Sound " + std::to_string(i), BACKGROUND_SOUND + std::to_string(i) + ".mp3");
		backgroundBuffer.push_back(data->assets.getSoundBuffer("Background Sound " + std::to_string(i)));
	}

	for (int i = 0; i < 6; i++)
	{
		data->assets.loadSoundBuffer("Action Sound " + std::to_string(i), ACTION_SOUND + std::to_string(i) + ".wav");
		actionsSoundBuffer.push_back(data->assets.getSoundBuffer("Action Sound " + std::to_string(i)));
	}
	for (int i = 0; i < 12; i++)
	{
		data->assets.loadSoundBuffer("Learn Sound " + std::to_string(i), LEARN_SOUND + std::to_string(i) + ".mp3");
		learnBuffer.push_back(data->assets.getSoundBuffer("Learn Sound " + std::to_string(i)));

		data->assets.loadSoundBuffer("Speak Sound " + std::to_string(i), SPEAK_SOUNDS + std::to_string(i) + ".mp3");
		speakBuffer.push_back(data->assets.getSoundBuffer("Speak Sound " + std::to_string(i)));
	}
}

//Gets if sound is on or not
bool SoundManage::getIsSound()
{
	return isSound;
}

//Sets sounds volume - off or on
void SoundManage::setSound()
{
	isSound = !isSound;
	if (!isSound)
	{
		backgroundSound.setVolume(0);
		actionSound.setVolume(0);
		gameSound.setVolume(0);
	}
	else
	{
		backgroundSound.setVolume(BACKGROUND_VOLUME);
		actionSound.setVolume(ACTION_VOLUME);
		gameSound.setVolume(GAME_VOLUME);
	}
}

//Gets a sound number and switches the background sound 
void SoundManage::switchBackground(SoundManage::SoundBackgroundType sound)
{
	int soundIndex = static_cast<int>(sound);
	if (soundIndex < backgroundBuffer.size())
	{
		backgroundSound.setBuffer(backgroundBuffer.at(soundIndex));
		backgroundSound.play();
	}
}

//Gets a game sound number and plays it 
void SoundManage::playGameSound(SoundManage::SoundGameType sound)
{
	int soundIndex = static_cast<int>(sound);
	if (soundIndex < gameSoundBuffer.size())
	{
		gameSound.setBuffer(gameSoundBuffer.at(soundIndex));
		gameSound.play();
	}
}

//Gets an action sound number and plays it 
void SoundManage::playActionSound(SoundManage::SoundActionType sound)
{
	int soundIndex = static_cast<int>(sound);
	if (soundIndex < actionsSoundBuffer.size())
	{
		actionSound.setBuffer(actionsSoundBuffer.at(soundIndex));
		actionSound.play();
		actionSoundPlaying = soundIndex;
		if (sound == SoundManage::SoundActionType::PLAY_SOUND)
		{
			actionSound.setPitch(1.5);
		}
	}
}

//Gets a word number, plays it and returns it's time
float SoundManage::speak(int word)
{
	if (word < speakBuffer.size())
	{
		speakSound.setBuffer(speakBuffer.at(word));
		speakSound.play();
		speakSoundPlaying = word;
		return speakBuffer.at(word).getDuration().asMicroseconds() - 800000;
	}
	return NO_SOUND;
}

//Gets a word number to learn, plays it and returns it's time
float SoundManage::learn(int word)
{
	if (word < learnBuffer.size())
	{
		speakSound.setBuffer(learnBuffer.at(word));
		speakSound.play();
		speakSoundPlaying = word;
		return learnBuffer.at(word).getDuration().asMicroseconds() - 1000000;
	}
	return NO_SOUND;
}

//Stops action and speaking sounds
void SoundManage::stop()
{
	if (actionSoundPlaying > NO_SOUND)
	{
		if (actionSound.getStatus() == sf::Sound::Paused)
		{
			actionSound.play();
		}
		actionSound.stop();
		if (actionSoundPlaying == static_cast<int>(SoundManage::SoundActionType::PLAY_SOUND))
		{
			actionSound.setPitch(1);
		}
		else
		{
			playGameSound(SoundManage::SoundGameType::HAPPY_PET_SOUND);
		}
		actionSoundPlaying = NO_SOUND;
	}
	if (speakSoundPlaying > NO_SOUND)
	{
		if (speakSound.getStatus() == sf::Sound::Paused)
		{
			speakSound.play();
		}
		speakSound.stop();
		speakSoundPlaying = NO_SOUND;
	}
}

//Pauses all played sounds
void SoundManage::pause()
{
	backgroundSound.pause();
	if (actionSoundPlaying > NO_SOUND)
	{
		actionSound.pause();
	}
	if (speakSoundPlaying > NO_SOUND)
	{
		speakSound.pause();
	}
}

//Resume all paused sounds
void SoundManage::resume()
{
	if (backgroundSound.getStatus() == sf::Sound::Paused)
	{
		backgroundSound.play();
	}
	if (actionSoundPlaying > NO_SOUND)
	{
		actionSound.play();
	}
	if (speakSoundPlaying > NO_SOUND)
	{
		speakSound.play();
	}
}
