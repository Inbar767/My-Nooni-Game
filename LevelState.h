#pragma once

#include <SFML/Graphics.hpp>
#include "Pet.h"
#include "Accessorizes.h"
#include "EffectsControl.h"
#include "GameState.h"
#include "Pam.h"

//A child class of GameState - for levels states
class LevelState : public GameState
{
public:
	//Constructor
	LevelState(gameDataRef data, SoundManage* sounds, EffectsControl *effects, Pet *pet);
	//Destructor 
	~LevelState();
	//Init
	void init();
	//Handles input
	bool handleInput(sf::Event event);
	//Draws level
	void draw(float dt);

protected:
	//Starts an action
	void touchPet();
	//Stops current action
	void stopAction();
	//Level up the pet
	virtual void levelUp() = 0;

	sf::Sprite background;
	sf::Sprite roomTitle;
	sf::Sprite speakButton;

	Accessorizes* accessories;

	int xp;
	float endLevel;
	float startPetTime; //Petting action was started
};
