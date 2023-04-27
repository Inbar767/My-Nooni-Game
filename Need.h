#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "Definitions.h"

//A class for the pet's need
class Need
{
public:
	
	enum NeedType {
		LOVE,
		HUNGER,
		TIRED,
		CLEAN,
		BORED
	};

	//Constructor
	Need(gameDataRef data, Need::NeedType needType);
	//Destructor
	~Need() {}
	//Gets the current mood of the need
	MoodType getMood();
	//Draws
	void draw();
	//Updates the need
	void update(float dt);
	//Handles input
	void handleInput();
	//Increases need's xp
	void levelUp(int amount);
	//Restarts clock
	void restartClock();

private:	
	//Updates the scale's sprites
	void updateScale(int oldXp);

	sf::Clock clock;

	MoodType currentMood;
	NeedType needType;

	int xp;
	float scaleTime;
	bool showScale; //Is the scalse should be displayed

	gameDataRef data;

	sf::CircleShape ShapeIcon; //Circle represents need's mood

	sf::Sprite SpriteIcon;
	sf::Sprite spriteScale;
};
