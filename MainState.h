#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "SoundManage.h"

//A child class of State - is the main game state where the game starts from
class MainState : public State
{
public:
	//Constructor
	MainState(gameDataRef data, SoundManage* sounds);
	//Destructor 
	~MainState() {}
	//Init
	void init();
	//Handles input
	bool handleInput(sf::Event event);
	//Updates
	void update(float dt) { }
	//Draws the main state
	void draw(float dt);

private:
	sf::Sprite background;
	sf::Sprite logo; //Game logo
	sf::Sprite playButton;

	gameDataRef data;
	SoundManage* sounds;
};

