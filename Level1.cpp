#include "Level1.h"
#include "Level2.h"
#include "SmallPam.h"
#include "BigPam.h"

//Constructor gets a data, sounds and the type of the pet
Level1::Level1(gameDataRef data, SoundManage* sounds, Pet* pet, EffectsControl* effects) : 
	LevelState(data, sounds, new EffectsControl(data), new Pet(data,type))
{
	endLevel = 60.0f;
	pam = new SmallPam(data, EGG_PAM);
	pet->setPosition(sf::Vector2f(data->window.getSize().x / 2 - EGG_WIDTH / 2, EGG_Y_POSTION));
}

//Updates pam, effects and checks if it's time for the egg to grow
void Level1::update(float dt)
{
	if (!isPause)
	{
		if (currentAction == ActioType::INTRO)
		{
			updatePam(); //Updates pam's speech
		}
		else
		{
			if (currentAction == ActioType::STAND)
			{
				if (clock.getElapsedTime().asSeconds() + exactTime > endLevel)
				{
					levelUp(); //Growing pet
				}
			}
			else if(currentAction == ActioType::GROW && !effects->isEffect())
			{
				stopAction();
			}
			GameState::update(dt);
		}
	}
}

//Draws level
void Level1::draw(float dt)
{
	LevelState::draw(dt);
	effects->draw();
	GameState::draw(dt);
}

//Level up the pet
void Level1::levelUp()
{
	currentAction = ActioType::GROW;
	sounds->playActionSound(SoundManage::SoundActionType::GROW_SOUND);
	pet->grow();
	effects->startEffect(EffectsControl::EffectType::GROW_EGG_EFFECT);
}

//Stops current action
void Level1::stopAction()
{
	sounds->stop();
	if (currentAction == ActioType::GROW)
	{
		currentAction = ActioType::STAND;
		pet->stopAction(0);
		data->machine.addState(StateRef(new Level2(data, sounds, effects, pet)), true); //Goes to Level2
	}
}

//Destructor
Level1::~Level1()
{
	delete pam;
}
