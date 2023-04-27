#pragma once

#include "Level2.h"
#include "Menu.h"

//A child class of Level2 - is the third level of the game
class Level3 : public Level2
{
public:
	//Constructor
	Level3(gameDataRef data, SoundManage* sounds, EffectsControl* effects, Pet* pet, std::vector <bool> blockedWords);
	//Destructor 
	~Level3();

protected:
	//Game over and the user is winning
	virtual void levelUp();

	const std::vector<std::string_view > ADULT_PAM = {
		"Good news!\nYour Nooni just grew \nInto an adult...",
		"Now the refrigerator is full\nWith new different kind of\nFood..",
		"Now you can teach him\nMore new words at the \nSpeaking class...",
		"I'm going to come back as \nSoom as I can, please keep\nTaking care for him..."
	};

	const std::vector<std::string_view > WIN_PAM = {
		"Hello again, neighbor!\nThank you for the good \nTreatment you gave \nMy Nooni, now I'm going back \nHome, you can take care \nOf him again next time!..."
	};
};

