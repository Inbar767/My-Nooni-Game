#include "InputManager.h"

//Gets a sprite, A button and a window and returns true if the sprite was clicked by the mouse button, else false
bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect(sf::Vector2i(object.getPosition().x, object.getPosition().y),
			sf::Vector2i(object.getGlobalBounds().width, object.getGlobalBounds().height));
		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

//Gets a window and returns mouse position on it
sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}