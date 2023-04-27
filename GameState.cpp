#include "GameState.h"
#include "Definitions.h"
#include "BigPam.h"
#include <iostream>

//Constructor gets a data, sounds, effects and a pet
GameState::GameState(gameDataRef data, SoundManage* sounds, EffectsControl* effects, Pet* pet) :
	data(data), sounds(sounds), pet(pet), effects(effects), currentAction(ActioType::INTRO), isPause(false), exactTime(0)
{ 
}

//Removes the state
void GameState::removeState()
{
	if (isPause)
	{
		sounds->resume();
	}
	if (effects != NULL)
	{
		effects->stopEffect();
	}
	pet->stopAction(0);
;	sounds->stop();
	data->machine.removeState();
}

//Loads sprites
void GameState::init()
{
	//Pause button sprite
	data->assets.loadTexture("Pause Button", PAUSE_BUTTON);
	pauseButton.setTexture(data->assets.getTexture("Pause Button"));
	pauseButton.setPosition(sf::Vector2f(720, 10));
	//Back button sprite
	data->assets.loadTexture("Back Game Button", BACK_BUTTON);
	backButton.setTexture(data->assets.getTexture("Back Game Button"));
	backButton.setPosition(sf::Vector2f(790, 10));
	//Play button sprite
	data->assets.loadTexture("play Game Button", BIG_PLAY_BUTTON);
	playButton.setTexture(data->assets.getTexture("play Game Button"));
	playButton.setPosition(sf::Vector2f(data->window.getSize().x / 2 - playButton.getGlobalBounds().width / 2,
		data->window.getSize().y / 2 - playButton.getGlobalBounds().height / 2));
	//Dark screen sprite
	data->assets.loadTexture("Dark Screen", DARK_SCREEN);
	darkScreen.setTexture(data->assets.getTexture("Dark Screen"));
}

//Handles input and checks if buttons was being pressed
bool GameState::handleInput(sf::Event event)
{
	if (!isPause)
	{
		if ((event.type == sf::Event::LostFocus || data->input.isSpriteClicked(pauseButton, sf::Mouse::Left, data->window)))
		{
			pause();
			return true;
		}
		else if(currentAction == ActioType::INTRO && pam != NULL)
		{
			pam->handleInput(event);
			return true;
		}
	}
	else
	{
		if (data->input.isSpriteClicked(playButton, sf::Mouse::Left, data->window))
		{
			resume();
			return true;
		}
	}
	if (data->input.isSpriteClicked(backButton, sf::Mouse::Left, data->window))
	{
		sounds->playGameSound(SoundGameType::MOUSE_CLICKED_SOUND);
		removeState();
		return true;
	}
	return false;
}

//Pause the game
void GameState::pause()
{
	sounds->playGameSound(SoundGameType::MOUSE_CLICKED_SOUND);
	sounds->pause();
	isPause = true;
	exactTime += clock.getElapsedTime().asSeconds();
}

//Resumes the game
void GameState::resume()
{
	isPause = false;
	if (currentAction == ActioType::OTHER_STATE)
	{
		currentAction = ActioType::STAND;
		if (Game::getIsGameOver())
		{
			gameOver();
		}
	}
	else
	{
		restartClock();
	}
	sounds->resume();
}

//Draws buttons and darkScreen in pause mood
void GameState::draw(float dt)
{
	data->window.draw(pauseButton);
	data->window.draw(backButton);
	if (currentAction == ActioType::INTRO && pam != NULL) //Draws pam if needed
	{
		pam->draw();
	}
	if (isPause)
	{
		data->window.draw(darkScreen);
		data->window.draw(playButton);
	}
}

//Updates the game
void GameState::update(float dt)
{
	if (effects != NULL)
	{
		effects->update();
	}
	pet->update(dt);
	petMood(); //Checks the pet's mood
}

//Restart clocks of the game
void GameState::restartClock()
{
	clock.restart();
	pet->restartClock();
	if (effects != NULL)
	{
		effects->restartClock();
	}
}

//Starts Game over mood
void GameState::gameOver()
{
	if (pam != NULL)
	{
		delete pam;
	}
	pam = new BigPam(data, LOOSE_PAM, BigPam::TITLE, !BigPam::WINNING_TITLE);
	currentAction = ActioType::INTRO;
	Game::gameOver();
	sounds->stop();
}

//Checks the pet's mood
void GameState::petMood()
{
	MoodType currentMood = pet->getMood();
	if (currentMood == MoodType::DEAD_MOOD)
	{
		gameOver();
	}
}

//Updates pam
void GameState::updatePam()
{
	if (pam->getIsDone())
	{
		currentAction = ActioType::STAND;
		restartClock();
		if (Game::getIsGameOver())
		{
			removeState();
		}
	}
}