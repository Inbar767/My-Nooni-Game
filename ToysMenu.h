#pragma once

#include "Menu.h"

//A child class of Menu - for toys menu
class ToysMenu : public Menu
{
public:

	enum ToysType {
		BALL = 8,
		CAR,
		TIC_TAC_TOE
	};

	//Constructor
	ToysMenu(gameDataRef data, int elementsNumber);
	//Destructor
	~ToysMenu() { }
	//Handles input
	int handleInput();

	const static int MAX_TOYS_ELEMENTS = 3;

protected:
	//Pushes all elements sprites into sprites vector
	void pushSpriteElements(int elementsNumber);
};
