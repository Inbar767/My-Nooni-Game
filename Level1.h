#pragma once

#include "LevelState.h"

//A child class of LevelState - is the first level of the game
class Level1 : public LevelState
{
public:
	//Constructor
	Level1(gameDataRef data, SoundManage* sounds, Pet *pet, EffectsControl *effects);
	//Destructor 
	~Level1();
	//Updates the level
	void update(float dt);
	//Draws
	void draw(float dt);

protected:
	//Stops current action
	void stopAction();
	//Level up the pet
	void levelUp();	
	
	const std::vector<std::string_view > EGG_PAM = {
	"Welcome to your\nNooni's room!",
	"You can see your Nooni\nEgg on the carpet...",
	"The heart above him is\nA reflection of your \nNooni's needs...",
	"On the left side of the\nScreen you can see\nYour Nooni's needs...",
	"For now his only need\nIs being petted...",
	"Just press on your\nNooni as long as you \nWant to pet him!..."
	};
};
