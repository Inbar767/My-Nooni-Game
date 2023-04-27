#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "Game.h"
#include "Need.h"
#include "Heart.h"
#include "Animation.h"
#include "Definitions.h"

enum NooniName {
	ANGEL,
	COCO,
	FIFI,
	BOO
};

//A class for pet
class Pet
{
public:
	//Constructor
	Pet(gameDataRef data, NooniName petType);
	//Destructor
	~Pet();
	//Gets pet's type
	NooniName getType();
	//Gets current action type
	int getActionType();
	//Gets the main position of the pet
	sf::Vector2f getMainPosition();
	//Updates
	void update(float dt);
	//Draws
	void draw();
	//Handles input
	bool handleInput(sf::Event event);
	//Start action of being petted
	void beingPetted();
	//Start action of eating, can be only in baby/adult age
	void feed();
	//Start action of sleeping, can be only in baby/adult age
	void goSleep();
	//Start action of taking shower, can be only in baby/adult age
	void shower();	
	//Start action of playing, can be only in baby/adult age
	void startPlay();
	//Start action of growing, can be only in egg/baby age
	void grow();
	//Start action of talking, can be only in baby/adult age
	void startTalk();
	//Gets xp, increases the used need and stops current action
	void stopAction(int xp);
	//Restarts clock
	void restartClock();
	//Sets pet's position
	void setPosition(sf::Vector2f postion);
	//Updates current pet's mood and returns it
	MoodType getMood();

private:
	//Sets the pet's animation by different actions
	void setAnimation();

	gameDataRef data;

	Animation *animation;
	std::array <Need*, 5> needs; //Pet's needs
	Heart *heart; 

	sf::Vector2f mainPosition;

	NooniName petType;
	ActioType currentAction; //Current pet's action type
	std::string age;
	int needsNumber;
	MoodType currentMood;
};

