#pragma once

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>

//A class for room's accessorizes
class Accessorizes
{
public:

	enum AccessoryType {
		NO_ACCESSORY = -1,
		REFRIGERATOR,
		BED,
		BATH,
		TABLE,
		TOY_BOX
	};

	//Constructor
	Accessorizes(gameDataRef data);
	//Destructor
	~Accessorizes() = default;
	//Handles inout
	AccessoryType handleInput(sf::Event event);
	//Draws
	void draw();
	//Stop the use of an accessory
	void stopUse();
	//Set visibility of table
	void setVisibleTable();
	//Draws table
	void drawTable();

private:
	std::vector <sf::Sprite> accessorizes;

	bool visibleTable; //Is the table visible
	AccessoryType typeUsed; //Which accessory is being used

	gameDataRef data;
};
