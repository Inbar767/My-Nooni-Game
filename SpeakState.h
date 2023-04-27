#pragma once

#include "GameState.h"
#include "Game.h"
#include "SoundManage.h"
#include "Pam.h"
#include "Pet.h"
#include <vector>
#include <array> 
#include <SFML/Graphics.hpp>

//A subclass of GameState - Speak class for teaching a pet how to talk
class SpeakState : public GameState
{
public:
	//Constructor
	SpeakState(gameDataRef data, SoundManage* sounds, EffectsControl* effects, Pet *pet, std::vector <bool> & blockedWords);
	//Destructor
	~SpeakState();
	//Init
	void init();
	//Draws
	void draw(float dt);
	//Handles input
	bool handleInput(sf::Event event);
	//Update
	void update(float dt);

private:
	//Make the pet say word
	void speak(int word);
	//Pet the pet
	void touchPet();
	//Stops current action
	void stopAction(int xp);
	//Game over
	void gameOver();
	//Remove this state
	void removeState();

	sf::Sprite background;

	std::vector <sf::Sprite> wordsButtons;
	std::vector <sf::Text> words;
	std::vector <bool>& blockedWords; //Tells if the word is blocked or not

	sf::Font font;

	float wordTime; //How long the word is taking to say
	bool isSpeaking;
	bool isLearning;
	int wordIndex; //Current word
	float startPetTime;

	const int WORD_BUTTON_DIS_HEIGHT = 60;
	const int WORD_BUTTON_DIS_WIDTH = 175;	
	const int X_FIRST_BUTTON_POSITION = 190;
	const int Y_FIRST_BUTTON_POSITION = 100;
	const int NUMBER_BUTTON_ROW = 4;

	const std::vector <std::string_view > SPEAK_PAM = {
		"Welcome to the \nSpeaking class...",
		"This is the place where\nYour nooni can learn new\nWords and speak...",
		"The words are blocked.\nIn order to open them\nAnd teach your nooni...",
		"Please press on\nThe locked buttons...",
		"Please give your nooni as\nMuch time as he needs\nTo complete his learning...",
		"After finishing his learning\nYou can press on the word \nButton and he will say it..."
	};

	//Words to learn array
	const std::array <std::string_view, 12 > WORDS = {
		"Nooni", "Hello", "Mommy", "Daddy", 
		"Happy", "Sad", "I love U", "I can talk",
		"My room", "You are pretty", "Let's play", "I love pizza"
	};
};

