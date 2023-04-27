#include "Level2.h"
#include "Level3.h"
#include "SpeakState.h"
#include "YardState.h"
#include "SmallPam.h"
#include "BigPam.h"
#include "ToysMenu.h"
#include "FoodMenu.h"

//Constructor gets a data, sounds, effects and a pet
Level2::Level2(gameDataRef data, SoundManage* sounds, EffectsControl *effects, Pet *pet) :
	LevelState(data, sounds, effects, pet)
{
	endLevel = 35;
	menus[0] = new FoodMenu(data, FoodMenu::MAX_FOOD_ELEMENTS / 3); //Creates a menu for baby's food
	menus[1] = new ToysMenu(data, ToysMenu::MAX_TOYS_ELEMENTS); //Creates a menu for toys

	pam = new SmallPam(data, BABY_PAM);

	//Adds locked words the pet doesn't learn yet into blockedWords
	for (int i = 0; i < WORDS_NUMBER; i++)
	{
		blockedWords.push_back(true);
	}
}

//Handles input
bool Level2::handleInput(sf::Event event)
{
	if (!LevelState::handleInput(event) && !isPause)
	{
		if (currentAction == ActioType::OPEN_REFRIGERATOR || currentAction == ActioType::OPEN_BOX)
		{
			menuChoice(); //Select from menu
		}
		else
		{
			if (currentAction == ActioType::STAND)
			{
				Accessorizes::AccessoryType choice{ accessories->handleInput(event) };
				if (choice != Accessorizes::AccessoryType::NO_ACCESSORY)
				{
					useAccessorize(choice); //Use chosen accessory
				}
				else if (data->input.isSpriteClicked(speakButton, sf::Mouse::Left, data->window))
				{
					sounds->playGameSound(SoundManage::SoundGameType::MOUSE_CLICKED_SOUND);
					currentAction = ActioType::OTHER_STATE;
					data->machine.addState(StateRef(new SpeakState(data, sounds, effects, pet, blockedWords)), false);
				}
				else
				{
					sf::Vector2i mousePosition = data->input.getMousePosition(data->window);
					if (data->input.isSpriteClicked(background, sf::Mouse::Left, data->window))
					{
						if ((mousePosition.x >= TOYBOX_LEFT_X && mousePosition.x <= TOYBOX_RIGHT_X) &&
							(mousePosition.y >= TOYBOX_LEFT_Y && mousePosition.y <= TOYBOX_RIGHT_Y))
						{
							useAccessorize(Accessorizes::AccessoryType::TOY_BOX);
						}
					}
				}
			}
		}
	}
	return true;
}

//Updates pam, effects, pet and checks if it's time for the egg to grow
void Level2::update(float dt)
{
	if (!isPause)
	{
		if (currentAction == ActioType::INTRO)
		{
			updatePam(); //Updates pam's speech
		}
		else
		{
			if (currentAction != ActioType::STAND)
			{
				if (!effects->isEffect() && currentAction >= ActioType::EAT && currentAction <= ActioType::GROW) //If it's a pet's action stop it
				{
					stopAction();
				}
			}
			else if (clock.getElapsedTime().asSeconds() + exactTime >= endLevel)
			{
				levelUp(); //Growing pet
			}
			GameState::update(dt);
		}
	}
}

//Draws level
void Level2::draw(float dt)
{
	LevelState::draw(dt);
	if (currentAction == ActioType::OPEN_REFRIGERATOR)
	{
		menus[0]->draw();
	}
	else if(currentAction == ActioType::OPEN_BOX)
	{
		menus[1]->draw();
	}
	else if (currentAction == ActioType::SLEEP)
	{
		data->window.draw(darkScreen);
	}
	effects->draw();	
	GameState::draw(dt);
}

//Start action of eating
void Level2::feed()
{
	pet->feed();
	accessories->setVisibleTable(); //Show table to eat on
	sounds->playActionSound(SoundManage::SoundActionType::EAT_SOUND);
	currentAction = ActioType::EAT;
}

//Start action of sleeping
void Level2::goSleep()
{
	pet->setPosition(sf::Vector2f(310, 300));
	pet->goSleep();
	sounds->playActionSound(SoundManage::SoundActionType::SLEEP_SOUND);
	effects->startEffect(EffectsControl::EffectType::SLEEP_EFFECT);
	currentAction = ActioType::SLEEP;
	xp = 10;
}

//Start action of taking shower
void Level2::shower()
{
	pet->setPosition(sf::Vector2f(680, 248));
	pet->shower();
	sounds->playActionSound(SoundManage::SoundActionType::SHOWER_SOUND);
	effects->startEffect(EffectsControl::EffectType::BATH_EFFECT);
	currentAction = ActioType::SHOWER;
	xp = 10;
}

//Start Accessorize's action
void Level2::useAccessorize(Accessorizes::AccessoryType accessorizeType)
{
	switch (accessorizeType)
	{
	case Accessorizes::AccessoryType::REFRIGERATOR:
		currentAction = ActioType::OPEN_REFRIGERATOR;
		break;
	case Accessorizes::AccessoryType::BED:
		goSleep();
		break;
	case Accessorizes::AccessoryType::BATH:
		shower();
		break;
	case Accessorizes::AccessoryType::TOY_BOX:
		currentAction = ActioType::OPEN_BOX;
		break;
	default:
		break;
	}
}

//Stops current action
void Level2::stopAction()
{
	pet->stopAction(xp);
	sounds->stop();
	if (currentAction == ActioType::GROW)
	{
		data->machine.addState(StateRef(new Level3(data, sounds, effects, pet, blockedWords)), true);
	}
	else
	{
		if (currentAction == ActioType::SLEEP || currentAction == ActioType::SHOWER)
		{
			pet->setPosition(pet->getMainPosition()); //Returns pet to it's main position
			if (currentAction == ActioType::SLEEP)
			{
				accessories->stopUse();
			}
		}
		else if (currentAction == ActioType::EAT)
		{
			accessories->setVisibleTable();
		}
		currentAction = ActioType::STAND;
		xp = 0;
	}
}

//Checks if user selected from menu
void Level2::menuChoice()
{
	int choice{}, menuIdex;
	menuIdex = static_cast<int>(currentAction - ActioType::OPEN_REFRIGERATOR);
	choice = menus[menuIdex]->handleInput();
	if (choice != Menu::NO_ELEMENT_CHOSEN)
	{
		sounds->playGameSound(SoundManage::SoundGameType::MOUSE_CLICKED_SOUND);
		if (choice == Menu::EXIT_MENU)
		{
			currentAction = ActioType::STAND;
		}
		else
		{
			if (currentAction == ActioType::OPEN_REFRIGERATOR)
			{
				effects->startEffect(static_cast<EffectsControl::EffectType>(choice));
				xp = ((FoodMenu *)menus[0])->getFoodXp(choice); //Gets xp of chosen food
				feed();
			}
			else
			{
				currentAction = ActioType::OTHER_STATE;
				data->machine.addState(StateRef(new YardState(data, sounds, effects, pet, static_cast<ToysMenu::ToysType>(choice))), false);
			}
		}
	accessories->stopUse();
	}
}

//Level up the pet
void Level2::levelUp()
{
	currentAction = ActioType::GROW;
	sounds->playActionSound(SoundManage::SoundActionType::GROW_SOUND);
	pet->grow();
	effects->startEffect(EffectsControl::EffectType::GROW_BABY_EFFECT);
}

//Destructor
Level2::~Level2()
{
	delete pam;
	for (int i = 0; i < menus.size(); i++)
	{
		delete menus[i];
	}
}
