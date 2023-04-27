#include "Menu.h"
#include "Definitions.h"

//Constructor gets a data, sounds and a menu type
Menu::Menu(gameDataRef data) : data(data)
{
	data->assets.loadTexture("Menus Background", MENU_WINDOW);
	background.setTexture(data->assets.getTexture("Menus Background"));
	background.setPosition(sf::Vector2f(data->window.getSize().x / 2 - background.getGlobalBounds().width / 2, 
		data->window.getSize().y / 2 - background.getGlobalBounds().height / 2));

	backButton.setTexture(data->assets.getTexture("Select Menu Back Button"));
	backButton.setPosition(sf::Vector2f(background.getPosition().x, 
		background.getGlobalBounds().height + background.getPosition().y - 50));
}

//Sets the menu's buttons
void Menu::setButtons()
{
	int x, startX, y;
	x = startX = background.getPosition().x + BUTTON_DIS_BACKGROUND_X;
	y = background.getPosition().y + BUTTON_DIS_BACKGROUND_Y;

	for (int SpritesIndex = 0; SpritesIndex < sprites.size(); SpritesIndex++)
	{
		sprites.at(SpritesIndex).setPosition(sf::Vector2f(x, y));
		if (SpritesIndex % NUMBER_BUTTON_ROW == 2)
		{
			x = startX;
			y += MENU_BUTTON_DIS_HEIGHT;
		}
		else
		{
			x += MENU_BUTTON_DIS_WIDTH;
		}
	}
}

//Draws the menu
void Menu::draw()
{
	data->window.draw(background);
	data->window.draw(backButton);
	for (int SpritesIndex = 0; SpritesIndex < sprites.size(); SpritesIndex++)
	{
		data->window.draw(sprites.at(SpritesIndex));
	}
}

//Handles input
int Menu::handleInput()
{
	if (data->input.isSpriteClicked(backButton, sf::Mouse::Left, data->window))
	{
		return EXIT_MENU;
	}
	//Checks if one of the menu objects is being pressed and returns it
	for (int SpritesIndex = 0; SpritesIndex < sprites.size(); SpritesIndex++)
	{
		if (data->input.isSpriteClicked(sprites.at(SpritesIndex), sf::Mouse::Left, data->window))
		{
			return SpritesIndex;
		}
	}
	return NO_ELEMENT_CHOSEN;
}