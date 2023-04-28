#include "Level3.h"
#include "YardState.h"
#include "SpeakState.h"
#include "BigPam.h"
#include "SmallPam.h"
#include "ToysMenu.h"
#include "FoodMenu.h"

//Constructor gets a data, sounds, effects, a pet, vector of words and the type of the room
Level3::Level3(gameDataRef data, SoundManage* sounds, EffectsControl* effects, Pet* pet, std::vector <bool> blockedWords) : Level2(data, sounds, effects, pet)
{
	endLevel = 600.0f;
	pam = new SmallPam(data, ADULT_PAM);
	
	menus[0] = new FoodMenu(data, FoodMenu::MAX_FOOD_ELEMENTS); //Creates a menu for adult's food
	menus[1] = new ToysMenu(data, ToysMenu::MAX_TOYS_ELEMENTS); //Creates a menu for toys

	this->blockedWords = blockedWords;
	//Adds locked words the pet doesn't learn yet into blockedWords
	for (int wordIndex = 0; wordIndex < WORDS_NUMBER; wordIndex++)
	{
		this->blockedWords.push_back(true);
	}
}

//Game over and the user is winning
void Level3::levelUp()
{
	delete pam;
	pam = new BigPam(data, WIN_PAM, BigPam::TITLE, BigPam::WINNING_TITLE);
	currentAction = ActioType::INTRO;
	Game::gameOver();
}

//Destructor 
Level3::~Level3()
{
	delete pam;
	for (int i = 0; i < menus.size(); i++)
	{
		delete menus[i];
	}
}
