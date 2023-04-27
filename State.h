#pragma once

#include <SFML/Graphics.hpp>

//A class for state
class State
{
public:
	//Init
	virtual void init() = 0;
	//Handles input
	virtual bool handleInput(sf::Event event) = 0;
	//Updates
	virtual void update(float dt) = 0;
	//Draws
	virtual void draw(float dt) = 0;
	//Pauses game
	virtual void pause() {}
	//Resumes game
	virtual void resume() {}
};

