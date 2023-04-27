#pragma once

#include "Menu.h"

enum ToysType {
	BALL = 8,
	CAR,
	TIC_TAC_TOE
};

//A child class of Menu - for toys menu
class ToysMenu : public Menu
{
public:
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
