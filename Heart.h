#pragma once

#include "Game.h"
#include "Animation.h"
#include "Definitions.h"
#include <SFML/Graphics.hpp>

//A class for the heart above the pet
class Heart
{
public:
	//Constructor
	Heart(gameDataRef data);
	//Destructor 
	~Heart() = default;
	//Updates heart's frames
	void update();
	//Draws heart
	void draw();
	//Gets isSpinning and set heart's spinning according
	void setIsSpinning(bool isSpinning);
	//Restarts clock
	void restartClock();
	//Sets the position of the heart
	void setPosition(sf::Vector2f position);
	//Changes the color of the heart
	void setColor(MoodType color);

private:
	Animation *animation;

	gameDataRef data;

	std::string mood; //Mood of the heart
};

