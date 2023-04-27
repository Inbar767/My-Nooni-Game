#include "Pet.h"
#include <iostream>

//Constructor gets a data, sounds and animal type and creates the pet according
Pet::Pet(gameDataRef data, NooniName petType) :
	data(data), petType(petType), currentAction(ActioType::STAND), age("egg"), currentMood(MoodType::GREEAN_MOOD), needsNumber(1)
{
	std::string animalFolder{}; //String of the folder name of the chosen pet
	switch (petType)
	{
	case NooniName::ANGEL:
		animalFolder = ANGEL_FOLDER;
		break;
	case NooniName::COCO:
		animalFolder = COCO_FOLDER;
		break;
	case NooniName::FIFI:
		animalFolder = FIFI_FOLDER;
		break;
	default: case NooniName::BOO:
		animalFolder = BOO_FOLDER;
		break;
	}

	animation = new Animation(data, animalFolder, 29); //Sets animation
	setAnimation();

	heart = new Heart(data);

	//Sets pet's needs
	for (NeedType needIndex = NeedType::LOVE; needIndex <= NeedType::BORED; ++(int&)needIndex)
	{
		needs[needIndex] = (new Need(data, needIndex));
	}
	
}

//Sets the pet's animation by different actions
void Pet::setAnimation()
{
	//Pet's regular mood
	animation->addAction("egg", 0, 0, 0, false);
	animation->addAction("baby", 1, 2, 1.2f, false);
	animation->addAction("adult", 3, 4, 1.2f, false);
	//Changes the time of the blinking frame
	animation->changeFrameTime("baby", 2, 0.2f);
	animation->changeFrameTime("adult", 4, 0.2f);
	//Pet is being petted
	animation->addAction("baby_pet", 15, 16, 0.2f, false);
	animation->addAction("adult_pet", 9, 10, 0.2f, false);
	//Pet is taking shower
	animation->addAction("baby_shower", 5, 5,0, false);
	animation->addAction("adult_shower", 6, 6, 0, false);
	//Pet is playing
	animation->addAction("baby_play", 13, 18, 0.1f, false);
	animation->addAction("adult_play", 7, 12, 0.1f, false);
	//Pet is eating
	animation->addAction("baby_eat", 16, 17, 0.5f, false);
	animation->addAction("adult_eat", 10, 11, 0.5f, false);
	//Pet is talking
	animation->addAction("baby_talk", 24, 28, 0.2, false);
	animation->addAction("adult_talk", 19, 23, 0.2, false);

	animation->startAction("egg");
}

//Gets pet's type
NooniName Pet::getType()
{
	return petType;
}

//Gets current action
int Pet::getActionType()
{
	return currentAction;
}

//Gets the main position of the pet
sf::Vector2f Pet::getMainPosition()
{
	return mainPosition;
}

//Updates animation, needs and heart
void Pet::update(float dt)
{
	if (currentAction != ActioType::GROW)
	{
		for (int needIndex = 0; needIndex < needsNumber; needIndex++)
		{
			if (static_cast<int>(currentAction - ActioType::PETTED) != needIndex)
			{
				needs.at(needIndex)->update(dt);
			}
		}
		animation->animation();
	}
	heart->update();
}

//Draws
void Pet::draw()
{
	if (currentAction != ActioType::SLEEP)
	{
		animation->draw();
	}
	heart->draw();
	for (int needIndex = 0; needIndex < needsNumber; needIndex++)
	{
		needs.at(needIndex)->draw();
	}
}

//Handles input, return true if pet is being touched, else false
bool Pet::handleInput(sf::Event event)
{
	for (int needIndex = 0; needIndex < needsNumber; needIndex++)
	{
		needs.at(needIndex)->handleInput();
	}
	return animation->handleInput(event);
}

//Start action of being petted
void Pet::beingPetted()
{
	currentAction = ActioType::PETTED;
	heart->setIsSpinning(true);
	if (age != "egg")
	{
		animation->startAction(age + "_pet");
	}
}

//Start action of eating, can be only in baby/adult age
void Pet::feed()
{
	if (age != "egg")
	{
		animation->startAction(age + "_eat");
		currentAction = ActioType::EAT;
		heart->setIsSpinning(true);
	}
}

//Start action of sleeping, can be only in baby/adult age
void Pet::goSleep()
{
	if (age != "egg")
	{
		currentAction = ActioType::SLEEP;
		heart->setIsSpinning(true);
	}
}

//Start action of taking shower, can be only in baby/adult age
void Pet::shower()
{
	if (age != "egg")
	{
		animation->startAction(age + "_shower");
		currentAction = ActioType::SHOWER;
		heart->setIsSpinning(true);
	}
}

//Start action of playing, can be only in baby/adult age
void Pet::startPlay()
{
	if (age != "egg")
	{
		animation->startAction(age + "_play");
		currentAction = ActioType::PLAY;
		heart->setIsSpinning(true);
	}
}

//Start action of growing, can be only in egg/baby age
void Pet::grow()
{
	if (age != "adult")
	{
		animation->setColor(sf::Color::Black);
		currentAction = ActioType::GROW;
		heart->setIsSpinning(true);
		if (age == "egg")
		{
			needsNumber = needs.size();
			age = "baby";
		}
		else
		{
			age = "adult";
		}
	}
}

//Start action of talking, can be only in baby/adult age
void Pet::startTalk()
{
	if (age != "egg")
	{
		animation->startAction(age + "_talk");
		currentAction = ActioType::TALK;
		heart->setIsSpinning(true);
	}
}

//Gets xp, increases the used need and stops current action
void Pet::stopAction(int xp)
{
	if (currentAction != ActioType::STAND)
	{
		if (age != "egg" && currentAction != ActioType::SLEEP)
		{
			animation->startAction(age); //Sets action to standing action
		}
		if (currentAction >= ActioType::PETTED && currentAction <= ActioType::GROW)
		{
			if (currentAction < ActioType::GROW)
			{
				int needIndex = static_cast<int>(currentAction);
				needs.at(needIndex)->levelUp(xp); //Increases xp
			}
			else if (currentAction == ActioType::GROW)
			{
				animation->setColor(sf::Color::White);
				mainPosition = sf::Vector2f(data->window.getSize().x / 2 - animation->getSpriteWidth() / 2,
				EGG_Y_POSTION - (animation->getSpriteHeigth() - EGG_HEIGHT)); //Changes the main position according to new size
				setPosition(mainPosition);
			}
		}
		heart->setIsSpinning(false);
		currentAction = ActioType::STAND;
		restartClock();
	}
}

//Restarts clock
void Pet::restartClock()
{
	animation->restartClock();
	for (int needIndex = 0; needIndex < needsNumber; needIndex++)
	{
		needs.at(needIndex)->restartClock();
	}
	heart->restartClock();
}

//Sets pet's position
void Pet::setPosition(sf::Vector2f postion)
{
	animation->setPosition(postion);
	heart->setPosition(sf::Vector2f(animation->getSpriteWidth() / 2 + postion.x - HEART_WIDTH / 2, 
		postion.y - (HEART_DIST_PET + HEART_WIDTH)));
}

//Updates current pet's mood and returns it
MoodType Pet::getMood()
{
	MoodType lowest = MoodType::GREEAN_MOOD, needMood;
	int countBlackMood = 0;
	for (int needIndex = 0; needIndex < needsNumber ; needIndex++)
	{
		if ((needMood = needs.at(needIndex)->getMood()) <= lowest)
		{
			if (needMood == MoodType::BLACK_MOOD)
			{
				countBlackMood++;
			}
			if (needMood != lowest)
			{
				lowest = needMood;
			}
		}
	}
	if (countBlackMood == needsNumber)
	{
		currentMood = MoodType::DEAD_MOOD;
	}
	else if (lowest != currentMood)
	{
		currentMood = lowest;
	}
	heart->setColor(currentMood);
	return currentMood;
}

//Destructor
Pet::~Pet()
{ 
	delete heart; 
	for (int i = 0; i < needs.size(); i++)
	{
		delete needs[i];
	}
}