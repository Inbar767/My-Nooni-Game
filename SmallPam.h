#pragma once

#include "Pam.h"

//A child class of Pam - is the small window showning pam's speech
class SmallPam : public Pam
{
public:
	//Constructor
	SmallPam(gameDataRef data, const std::vector<std::string_view>(&pamSpeech));
	//Destructor
	~SmallPam() { }

protected:

	//Init
	void init();

	//Distance between text and background's frame
	const int DIST_TEXT_BACKGROUND_X = 120;
	const int DIST_TEXT_BACKGROUND_Y = 100;
};

