#include "ToysMenu.h"
#include "Definitions.h"

//Constructor gets a data, sounds and a menu type
ToysMenu::ToysMenu(gameDataRef data, int elementsNumber) : Menu(data)
{
	pushSpriteElements(elementsNumber);
	setButtons();
}

//Pushes all elements sprites into sprites vector
void ToysMenu::pushSpriteElements(int elementsNumber)
{
	for (int SpritesIndex = 0; SpritesIndex < elementsNumber && SpritesIndex < MAX_TOYS_ELEMENTS; SpritesIndex++)
	{
		data->assets.loadTexture("Toys Menu Buttons " + std::to_string(SpritesIndex), TOY_MENU + std::to_string(SpritesIndex) + ".png");
		sprites.push_back(sf::Sprite(data->assets.getTexture("Toys Menu Buttons " + std::to_string(SpritesIndex))));
	}
}

//Handles input
int ToysMenu::handleInput()
{
	int MenuChoice = Menu::handleInput();
	if (MenuChoice != EXIT_MENU && MenuChoice != NO_ELEMENT_CHOSEN)
	{
		MenuChoice += static_cast<int>(ToysType::BALL); //If element was chosen - set index to match ToysType
	}
	return MenuChoice;
}