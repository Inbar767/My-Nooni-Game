#pragma once

#include "State.h"
#include "GameState.h"
#include "Pet.h"
#include "EffectsControl.h"
#include "SoundManage.h"
#include "Definitions.h"
#include "TicTacToe.h"
#include "ToysMenu.h"

//A subclass of GameState - Yard state for playing a game with a pet
class YardState : public GameState
{
public:
	//Constructor
	YardState(gameDataRef data, SoundManage* sounds, EffectsControl *effects, Pet* pet, ToysMenu::ToysType gamePlayed);
	//Destructor
	~YardState() { }
	//Init
	void init();
	//Handles Input
	bool handleInput(sf::Event event);
	//Updates
	void update(float dt);
	//Draws
	void draw(float dt);

private:
	//Make pet start playing
	void startPlay(); 
	//Start playing when pet is being touched
	void touchPet();
	//Stops current action
	void stopAction(int xp);
	//Game over
	void gameOver();

	sf::Sprite background;

	TicTacToe* ticTacToe;

	ToysMenu::ToysType gamePlayed;
	bool isPlayed; //Is the pet playing at the moment
	int gameStatus;

	const float PET_PLAYS_TIME = 2.0f;
	const int PLAYING_PET_XP = 2;
};
