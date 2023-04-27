#include "BigPam.h"
#include "Definitions.h"

//Constractor gets a data and the type of pam's speech
BigPam::BigPam(gameDataRef data, const std::vector<std::string_view>(&pamSpeech), bool isTitle, bool isTitleWin) :
	Pam(data, pamSpeech), isTitle(isTitle), isTitleWin(isTitleWin)
{
	init();
	setFrames(pamSpeech);
}

//Draws pam and title if needed
void BigPam::draw()
{
	Pam::draw();
	data->window.draw(pamSprite);
	if (isTitle)
	{
		data->window.draw(title);
	}
}

//Init
void BigPam::init()
{
	data->assets.loadTexture("Pam Window", CANDY_WINDOW);
	background.setTexture(data->assets.getTexture("Pam Window"));
	background.setPosition(sf::Vector2f(data->window.getSize().x / 2 - background.getGlobalBounds().width / 2,
		data->window.getSize().y / 2 - background.getGlobalBounds().height / 2));
	std::string pamString = HAPPY_PAM_WINDOW; //The file of pam's sprite
	int titleDistY{};
	if (isTitle)
	{
		std::string titleString; //The file of title's sprite
		if (isTitleWin)
		{
			titleString = WIN_TITLE;
		}
		else
		{
			titleString = LOOSE_TITLE;
			pamString = SAD_PAM_WINDOW;
		}
		titleDistY = DIST_TITLE_BACKGROUND_Y * 2;
		data->assets.loadTexture("Pam Title", titleString);
		title.setTexture(data->assets.getTexture("Pam Title"));
		title.setPosition(sf::Vector2f(background.getGlobalBounds().getPosition().x + DIST_TEXT_BACKGROUND_X / 2,
			background.getGlobalBounds().getPosition().y + DIST_TITLE_BACKGROUND_Y));
	}
	data->assets.loadTexture("Pam", pamString);
	pamSprite.setTexture(data->assets.getTexture("Pam"));
	pamSprite.setPosition(sf::Vector2f(data->window.getSize().x / 2 - background.getGlobalBounds().width / 2,
		data->window.getSize().y / 2 - background.getGlobalBounds().height / 2));
	text.setPosition(sf::Vector2f(background.getGlobalBounds().getPosition().x + DIST_TEXT_BACKGROUND_X,
	background.getGlobalBounds().getPosition().y + DIST_TEXT_BACKGROUND_Y + titleDistY));
}