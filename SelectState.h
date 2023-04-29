#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "BigPam.h"
#include "SoundManage.h"
#include <vector>
#include <array>
#include "Definitions.h"

//A child class of State - for user to select an egg
class SelectState : public State
{
public:
	//Constructor
	SelectState(gameDataRef data, SoundManage* sounds);
	//Destructor
	~SelectState();
	//Init
	void init();
	//Handles input
	bool handleInput(sf::Event event);
	//Updates
	void update(float dt);
	//Draws
	void draw(float dt);
	//Resumes this State
	void resume();

private:
	sf::Sprite background;
	sf::Sprite windowSprite;
	sf::Sprite selectEggTitle;
	sf::Sprite backButton;
	sf::Sprite effect; //Effect of mouse touches an egg
	sf::Font font;
	std::array < sf::Text, NUMBER_EGG > eggName; 
	std::array <sf::Sprite, NUMBER_EGG > eggButtons;

	gameDataRef data;
	SoundManage* sounds;
	BigPam* pam;

	bool isGameStarted = false;
	bool isInstruction;
	bool isEffect;
	int effectTouch; //Which egg has the effect

	const int NUMBER_EGG_ROW = 2;

	const std::array < std::string_view, NUMBER_EGG > EGGS_NAMES = { "Angel", "Coco", "Fifi", "Boo" };

	const std::vector<std::string_view > SELECT_PAM = {
	"Hello!\n\nMy name is Pam and I \nLive right next door.\nI'm going on a \nVacation and I can \nTake only 3 of my \nPets with me...",
	"\nI need your help\nWith taking care\nFor one of them\nCan you do that?..." ,
	"\nThank you for helping\nYou are the best!\nI have to be honest\nAnd say they are\nNot usual animals...",
	"They are creatures\nCalled Noonis.\nYou can feed, bath \nThem and play with \nThem and you can\nAlso teach them \nHow to speak! ...",
	"For now it's only in\nIt's egg stage.\nIt will grow slowly!\nI'm sure you two will\nHave a good time \nTogether!\nPlease go next\nAnd select your Nooni..."
	};
};
