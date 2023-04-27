#include "MainState.h"
#include "SelectState.h"
#include <sstream>
#include <iostream>
#include "Definitions.h"

//Constructor gets a data and sounds
MainState::MainState(gameDataRef data, SoundManage* sounds) : data(data), sounds(sounds)
{
}

//Init
void MainState::init()
{
	data->assets.loadTexture("Main Menu Background", YARD_BACKGROUND);
	background.setTexture(data->assets.getTexture("Main Menu Background"));
	data->assets.loadTexture("logo", LOGO);
	logo.setTexture(data->assets.getTexture("logo"));
	logo.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 -(logo.getGlobalBounds().width / 2), 120));
	data->assets.loadTexture("Play Button", BIG_PLAY_BUTTON);
	playButton.setTexture(data->assets.getTexture("Play Button"));
	playButton.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - (playButton.getGlobalBounds().width / 2),
		SCREEN_HEIGHT / 2 - (playButton.getGlobalBounds().height / 2) + 180));
}

//Handle input if play button is being clicked
bool MainState::handleInput(sf::Event event)
{
	if (data->input.isSpriteClicked(playButton, sf::Mouse::Left, data->window))
	{
		sounds->playGameSound(SoundManage::SoundGameType::MOUSE_CLICKED_SOUND);
		data->machine.addState(StateRef(new SelectState(data, sounds)), false);
	}
	return true;
}


//Draws the main state
void MainState::draw(float dt)
{
	data->window.draw(background);
	data->window.draw(playButton);
	data->window.draw(logo);
}
