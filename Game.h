#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

//A struct for GameDate for game settings
struct GameDate
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
};

typedef std::shared_ptr<GameDate> gameDataRef; //A pointer to GameDate

//A class for controlling the game
class Game
{
public:
	//Constructor
	Game();
	//Destructor
	~Game();
	//Handles input
	void handleInput();
	//Draws
	void draw(float interplation);	
	//Gets if game is over
	static bool getIsGameOver();
	//Starts a new game
	static void startNewGame();
	//Finish the game
	static void gameOver();

private:
	//Runs the game window 
	void run();
	const float dt = 1.0f / 60.0f;
	sf::Clock clock;

	sf::Sprite soundButton;
	static bool isGameOver; //Tells if game is over

	gameDataRef data = std::make_shared<GameDate>();

};

