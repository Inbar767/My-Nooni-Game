#pragma once

#include <SFML/Graphics.hpp>

//A class for the game input
class InputManager
{
public:
	//Gets a sprite, A button and a window and returns true if the sprite was clicked by the mouse button, else false
	static bool isSpriteClicked(sf::Sprite, sf::Mouse::Button, sf::RenderWindow&);
	//Gets a window and returns mouse position on it
	static sf::Vector2i getMousePosition(sf::RenderWindow&);
};

