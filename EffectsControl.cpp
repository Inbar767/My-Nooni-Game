#include "EffectsControl.h"
#include <iostream>
#include "Definitions.h"

//Constructor gets a data
EffectsControl::EffectsControl(gameDataRef data) : 
	data(data), currentEffect(EffectType::NO_EFFECT), countAnimation(0)
{
	addEffects();
}

//Adds effects into effects
void EffectsControl::addEffects()
{
	//Sleep effect
	effects.push_back(std::make_unique <Animation>(data, SLEEP_ANIMATION, 23, sf::Vector2f(220, 230)));
	//Bath effect
	effects.push_back(std::make_unique <Animation>(data, BATH_ANIMATION, 26, sf::Vector2f(650, 295)));
	//Food effects
	effects.push_back(std::make_unique <Animation>(data, MILK_ANIMATION, 4, sf::Vector2f(410, 500)));
	effects.push_back(std::make_unique <Animation>(data, STRAWBERRY_ANIMATION, 4, sf::Vector2f(410, 500)));
	effects.push_back(std::make_unique <Animation>(data, SALAD_ANIMATION, 4, sf::Vector2f(410, 500)));
	effects.push_back(std::make_unique <Animation>(data, BURGER_ANIMATION, 4, sf::Vector2f(410, 500)));
	effects.push_back(std::make_unique <Animation>(data, PIZZA_ANIMATION, 4, sf::Vector2f(410, 500)));
	effects.push_back(std::make_unique <Animation>(data, CHOCOLATE_ANIMATION, 4, sf::Vector2f(410, 500)));
	//Games effects
	effects.push_back(std::make_unique <Animation>(data, BALL_ANIMATION, 10, sf::Vector2f(0, 0)));
	effects.push_back(std::make_unique <Animation>(data, CAR_ANIMATION, 10, sf::Vector2f(0, 0)));
	//Being pet effect
	effects.push_back(std::make_unique <Animation>(data, BEING_PET_ANIMATION, 8, sf::Vector2f(data->window.getSize().x / 2 - 192 / 2, 400)));
	//Growing pet effect
	effects.push_back(std::make_unique <Animation>(data, EGG_GROWING_ANIMATION, 10, sf::Vector2f(data->window.getSize().x / 2 - 96, 370)));
	effects.push_back(std::make_unique <Animation>(data, BABY_GROWING_ANIMATION, 10, sf::Vector2f(data->window.getSize().x / 2 - 96, 370)));

	//Addings actions
	effects.at(static_cast<int>(EffectType::SLEEP_EFFECT))->addAction("effect", 0, 22, 0.04, false);
	effects.at(static_cast<int>(EffectType::BATH_EFFECT))->addAction("effect", 0, 25, 0.09, false);

	for (int foodIndex = static_cast<int>(EffectType::MILK_EFFECT); foodIndex <= static_cast<int>(EffectType::CHOCOLATE_EFFECT); foodIndex++)
	{
		effects.at(foodIndex)->addAction("effect", 0, 3, 2.0f, false);
	}

	for (int toyIndex = static_cast<int>(EffectType::BALL_EFFECT); toyIndex <= static_cast<int>(EffectType::CAR_EFFECT); toyIndex++)
	{
		effects.at(toyIndex)->addAction("effect", 0, 9, 0.05f, true);
	}

	effects.at(static_cast<int>(EffectType::PET_EFFECT))->addAction("effect", 0, 7, 0.09f, false);

	for (int growIndex = static_cast<int>(EffectType::GROW_EGG_EFFECT); growIndex <= static_cast<int>(EffectType::GROW_BABY_EFFECT); growIndex++)
	{
		effects.at(growIndex)->addAction("effect", 0, 9, 0.2f, false);
	}
}

//Draws current effect
void EffectsControl::draw()
{
	if (currentEffect != EffectType::NO_EFFECT)
	{
		effects.at(currentEffect)->draw();
	}
}

//Updates current effect frames
void EffectsControl::update()
{
	if (currentEffect != EffectType::NO_EFFECT)
	{
		if(effects.at(currentEffect)->animation() && currentEffect != EffectType::PET_EFFECT)
		{
			countAnimation++;
			if (countAnimation == maxAnimation) //If current effect is animated maxAnimation times - stop effect
			{
				currentEffect = EffectType::NO_EFFECT;
				countAnimation = 0;
			}
		}
	}
}

//Playes effect
void EffectsControl::startEffect(EffectType effectNumber)
{
	int effectIndex = static_cast<int>(effectNumber);
	if (effectNumber >= EffectType::SLEEP_EFFECT && effectIndex < effects.size())
	{
		currentEffect = effectNumber;
		countAnimation = 0;
		//Changes maxAnimation accordding to type of the effect
		if (effectNumber == EffectType::SLEEP_EFFECT)
		{
			maxAnimation = 5;
		}
		else
		{
			if (effectNumber == EffectType::BATH_EFFECT)
			{
				maxAnimation = 2;
			}
			else
			{
				maxAnimation = 1;
			}
		}
		effects.at(effectIndex)->startAction("effect");
	}
}

//Sends if effects is being played
bool EffectsControl::isEffect()
{
	return (currentEffect != EffectType::NO_EFFECT);
}

//Stops current effect
void EffectsControl::stopEffect()
{
	if (currentEffect != EffectType::NO_EFFECT)
	{
		currentEffect = EffectType::NO_EFFECT;
	}
}

//Restarts clock of current effect
void EffectsControl::restartClock()
{
	if (currentEffect != EffectType::NO_EFFECT)
	{
		int effectIndex = static_cast<int>(currentEffect);
		effects.at(effectIndex)->restartClock();
	}
}