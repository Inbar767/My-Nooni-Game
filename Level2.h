#pragma once

#include "LevelState.h"
#include "Menu.h"

//A child class of LevelState - is the second level of the game
class Level2 : public LevelState
{
public:
	//Constructor
	Level2(gameDataRef data, SoundManage* sounds, EffectsControl*effects, Pet *pet);
	//Destructor
	~Level2();
	//Handles input
	bool handleInput(sf::Event event);
	//Updates the level
	void update(float dt);
	//Draws
	void draw(float dt);

protected:
	//Start action of eating
	void feed();
	//Start action of sleeping
	void goSleep();
	//Start action of taking shower
	void shower();
	//Start Accessorize's action
	void useAccessorize(AccessoryType accessorizeType);
	//Stops current action
	void stopAction();
	//Choose from the menu
	virtual void menuChoice();
	//Level up the pet
	virtual void levelUp();

	Menu** menus = new Menu * [2]; //Array of two menus

	std::vector <bool> blockedWords; //Vector of the blocked words the pet doesn't know yet

	const int WORDS_NUMBER = 6; //Number of words the pet can learn	
	
	const std::vector<std::string_view > BABY_PAM = {
		"Good news!\nYour Nooni just grew \nInto a baby...",
		"On the left side of the\nScreen you can see\nHis new needs...",
		"His needs are :\nBeing petted, eat, sleep, \nTake a bath and play...",
		"Now you can press on \nThe bed to let him \nSleep...",
		"You can press on the \nBath to let him take \nA bath...",
		"You can press on the\nRefrigerator to feed \nHim...",
		"You can press on the\nToy Box to play with\nHim...",
		"You can teach him how \nTo speak by pressing\nSpeech button...",
		"Have fun you two!\nJust don't forget taking\nCare for his needs..."
	};
};