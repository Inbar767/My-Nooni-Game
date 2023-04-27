#pragma once

#include "Game.h"
#include <vector>
#include <SFML/Graphics.hpp>

//A class for menu
class Menu
{
public:
	//Constructor
	Menu(gameDataRef data);
	//Destructor
	~Menu() { }
	//Draws the menu
	void draw();
	//Handles input
	virtual int handleInput();

	const static int EXIT_MENU = -2;
	const static int NO_ELEMENT_CHOSEN = -1;

protected:
	//Pushes all elements sprites into sprites vector
	virtual void pushSpriteElements(int elementsNumber) = 0;
	//Sets the menu's buttons
	void setButtons();

	sf::Sprite background;
	sf::Sprite backButton;
	std::vector <sf::Sprite> sprites; //Menu's objects

	gameDataRef data;

	//Distance between two buttons
	const int MENU_BUTTON_DIS_HEIGHT = 100;
	const int MENU_BUTTON_DIS_WIDTH = 110;
	//Distance between first button and background
	const int BUTTON_DIS_BACKGROUND_X = 58;
	const int BUTTON_DIS_BACKGROUND_Y = 60;
	const int NUMBER_BUTTON_ROW = 3;
};