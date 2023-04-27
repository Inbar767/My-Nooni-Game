#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "Animation.h"

//A class of all effects of the game
class EffectsControl
{
public:

	enum EffectType {
		NO_EFFECT = -1,
		SLEEP_EFFECT,
		BATH_EFFECT,
		MILK_EFFECT,
		STRAWBERRY_EFFECT,
		SALAD_EFFECT,
		BURGER_EFFECT,
		PIZZA_EFFECT,
		CHOCOLATE_EFFECT,
		BALL_EFFECT,
		CAR_EFFECT,
		PET_EFFECT,
		GROW_EGG_EFFECT,
		GROW_BABY_EFFECT
	};

	//Constructor
	EffectsControl(gameDataRef data);
	//Destructor
	~EffectsControl() {}
	//Draws the effects
	void draw();
	//Updates the effect animation
	void update();
	//Playes effect
	void startEffect(EffectsControl::EffectType effectNumber);
	//Sends if some effects is being played
	bool isEffect();
	//Stops the effect is being played
	void stopEffect();
	//Restarts clock
	void restartClock();

private:
	//Adds effects into effects
	void addEffects();

	int countAnimation; //Counter of how many time effect is being animated
	int maxAnimation; //Max time of effect to being animated
	EffectType currentEffect;

	std::vector<std::unique_ptr<Animation>> effects; //vector of effects

	gameDataRef data;
};
