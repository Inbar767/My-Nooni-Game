#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>

//A class for pam's speech
class Pam
{
public:
	//Constructor
	Pam(gameDataRef data, const std::vector<std::string_view >(&pamSpeech));
	//Destructor
	~Pam() { }
	//Init
	virtual void init() = 0;
	//Gets if speech is over
	bool getIsDone();
	//Draws
	virtual void draw();
	//Handles input
	void handleInput(sf::Event event);

protected:
	//Sets pam'S speech frames
	void setFrames(const std::vector<std::string_view >(&pamSpeech));
	//Goes to the next frame
	void goNext();

	sf::Sprite background;
	sf::Font font;
	sf::Text text;

	std::vector <std::string_view > framesStrings; //Strings of pam's speech by frames

	int currentFrame;

	bool isDone; //If speech is over

	gameDataRef data;
};

