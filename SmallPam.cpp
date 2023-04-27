#include "SmallPam.h"
#include "Definitions.h"

//Constractor gets a data and the type of pam's speech
SmallPam::SmallPam(gameDataRef data, const std::vector<std::string_view>(&pamSpeech)) : Pam(data, pamSpeech)
{
	init();
	setFrames(pamSpeech);
}

//Init
void SmallPam::init()
{
	data->assets.loadTexture("Pam Window", SMALL_PAM_WINDOW);
	background.setTexture(data->assets.getTexture("Pam Window"));
	background.setPosition(sf::Vector2f(data->window.getSize().x / 2 - background.getGlobalBounds().width / 2,
		data->window.getSize().y / 2 - background.getGlobalBounds().height / 2));
	text.setPosition(sf::Vector2f(background.getGlobalBounds().getPosition().x + DIST_TEXT_BACKGROUND_X,
		background.getGlobalBounds().getPosition().y + DIST_TEXT_BACKGROUND_Y));
}
