#pragma once

#include "Menu.h"
#include <array>

enum FoodType {
	MILK = 2,
	STRAWBERRY,
	SALAD,
	BURGER,
	PIZZA,
	CHOCOLATE,
};

//A child class of Menu - for food menu
class FoodMenu : public Menu
{
public:
	//Constructor
	FoodMenu(gameDataRef data, int elementsNumber);
	//Destructor
	~FoodMenu() = default;
	//Handles input
	int handleInput();
	//Gets the xp of chosen food from menu
	int getFoodXp(int index);

	const static int MAX_FOOD_ELEMENTS = 6;

protected:
	//Pushes all elements sprites into sprites vector
	void pushSpriteElements(int elementsNumber);

	const std::array<int, 6> FOOD_XP { 5, 3, 7, 6, 4, 2 };
};
