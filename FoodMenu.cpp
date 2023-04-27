#include "FoodMenu.h"
#include "Definitions.h"

//Constructor gets a data, sounds and a menu type
FoodMenu::FoodMenu(gameDataRef data, int elementsNumber) : Menu(data)
{
	pushSpriteElements(elementsNumber);
	setButtons();
}


//Pushes all elements sprites into sprites vector
void FoodMenu::pushSpriteElements(int elementsNumber)
{
	for (int i = 0; i < elementsNumber && i < MAX_FOOD_ELEMENTS; i++)
	{
		data->assets.loadTexture("Food Menu Buttons " + std::to_string(i), FOOD_MENU + std::to_string(i) + ".png");
		sprites.push_back(sf::Sprite(data->assets.getTexture("Food Menu Buttons " + std::to_string(i))));
	}
}

//Handles input
int FoodMenu::handleInput()
{
	int MenuChoice = Menu::handleInput();
	if (MenuChoice != EXIT_MENU && MenuChoice != NO_ELEMENT_CHOSEN)
	{
		MenuChoice += static_cast<int>(FoodType::MILK); //If element was chosen - set index to match FoodType
	}
	return MenuChoice;
}

//Gets the xp of chosen food from menu
int FoodMenu::getFoodXp(int index)
{
	int foodStartIndex = static_cast<int>(FoodType::MILK);
	int foodLastIndex = static_cast<int>(FoodType::CHOCOLATE);
	if (index >= foodStartIndex && index <= foodLastIndex)
	{
		return FOOD_XP[index - foodStartIndex];
	}
	return FOOD_XP[foodStartIndex];
}