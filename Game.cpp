#include "Game.h"
#include "MainState.h"
#include "SoundManage.h"
#include "Definitions.h"

bool Game::isGameOver = false;

SoundManage* sounds;

//Constructor creates game window
Game::Game()
{
	data->window.create(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), "My Nooni", sf::Style::Close || sf::Style::Titlebar);
	data->machine.addState(StateRef(new MainState(this->data, sounds = new SoundManage (this->data))));
	data->assets.loadTexture("Sound 1", SOUND_ON);
	data->assets.loadTexture("Sound 0", SOUND_OFF);
	soundButton.setTexture(data->assets.getTexture("Sound 1"));
	soundButton.setPosition(sf::Vector2f(10, 10));
	run(); //Starts the game
}

//Runs the game window 
void Game::run()
{
	float newTime, frameTime, interplation;
	float currentTime = clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	while (data->window.isOpen())
	{
		data->machine.processStateChanges();
		newTime = clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= dt)
		{
			data->machine.processStateChanges();
			data->machine.getCurrentState()->update(dt);
			handleInput();
			accumulator -= dt;
		}
		interplation = accumulator / dt;
		draw(interplation);
	}
}

//Gets if game is over
bool Game::getIsGameOver()
{
	return isGameOver;
}

//Starts a new game
void Game::startNewGame()
{
	isGameOver = false;
}

//Finish the game
void Game::gameOver()
{
	isGameOver = true;
}

//Handles input
void Game::handleInput()
{
	sf::Event event;
	while (this->data->window.pollEvent(event))
	{
		if (data->input.isSpriteClicked(soundButton, sf::Mouse::Left, data->window))
		{
			sounds->setSound(); //Switch sound on and off
			soundButton.setTexture(data->assets.getTexture("Sound " + std::to_string(sounds->getIsSound()))); 
		}
		else
		{
			data->machine.getCurrentState()->handleInput(event); //Handles input of the current State of the game
		}
	}
}

//Draws game window
void Game::draw(float interplation)
{
	data->window.clear();
	data->machine.getCurrentState()->draw(interplation);
	data->window.draw(soundButton);
	data->window.display();
}

//Destructor
Game::~Game()
{	
	data.~shared_ptr();
	delete sounds;
}