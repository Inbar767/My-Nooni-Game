#pragma once

#include "Pam.h"

//A child class of Pam - is the big window showning pam's speech
class BigPam : public Pam
{
public:
	//Constructor
	BigPam(gameDataRef data, const std::vector<std::string_view>(&pamSpeech), bool isTitle, bool isTitleWin);
	//Destructor
	~BigPam() { }
	//Draws the window with pam
	void draw();

	const static bool TITLE = true;
	const static bool WINNING_TITLE = true;

protected:

	//Init
	void init();

	sf::Sprite pamSprite;
	sf::Sprite title;

	bool isTitle; //If there is a title
	bool isTitleWin;

	const int DIST_TEXT_BACKGROUND_X = 70;
	const int DIST_TEXT_BACKGROUND_Y = 150;
	const int DIST_TITLE_BACKGROUND_Y = 30;
};