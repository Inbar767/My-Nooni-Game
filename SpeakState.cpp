#include "SmallPam.h"
#include "BigPam.h"﻿
#include "SpeakState.h"
#include <iostream>

//Constructor gets a data, sounds, a pet and a vector says which word is blocked by the index of it
SpeakState::SpeakState(gameDataRef data, SoundManage* sounds, EffectsControl* effects, Pet *pet, std::vector <bool>& blockedWords) :
	GameState(data, sounds, effects, pet), blockedWords(blockedWords), isSpeaking(false), isLearning(false), wordIndex(0)
{
	sounds->switchBackground(SoundManage::SoundBackgroundType::SPEAK_STATE_SOUND);
	//Checks if at least one of the words isn't blocked and if so - changes actionType to be stand
	for (bool word : blockedWords)
	{
		if (!word)
		{
			currentAction = ActioType::STAND;
			break;
		}
	}
	if (currentAction == ActioType::INTRO)
	{
		pam = new SmallPam(data, SPEAK_PAM);
	}
}

//Init
void SpeakState::init()
{
	GameState::init();
	data->assets.loadTexture("Speak Background", CLASS_BACKGROUND);
	background.setTexture(data->assets.getTexture("Speak Background"));
	data->assets.loadTexture("Locked Word", LOCKED_WORD);
	data->assets.loadTexture("Unlocked Word", UNLOCKED_WORD);
	data->assets.loadTexture("Learn Word", LEARNING_WORD);

	//Loads font
	if (!font.loadFromFile("fonts/retganon.ttf"))
	{
		std::cout << "couldn't open font!";
	}

	int x = X_FIRST_BUTTON_POSITION, y = Y_FIRST_BUTTON_POSITION;
	//Position words' buttons
	for (int wordIndex = 0; wordIndex < blockedWords.size(); wordIndex++)
	{
		wordsButtons.push_back(sf::Sprite());
		wordsButtons.at(wordIndex).setPosition(sf::Vector2f(x, y));
		if (blockedWords.at(wordIndex))
		{
			wordsButtons.back().setTexture(data->assets.getTexture("Locked Word"));
		}
		else
		{
			wordsButtons.back().setTexture(data->assets.getTexture("Unlocked Word"));
			words.push_back(sf::Text(static_cast<std::string>(WORDS[wordIndex]), font, 25));
			words.back().setPosition(sf::Vector2f(wordsButtons.at(wordIndex).getGlobalBounds().getSize().x / 2 - words.back().getGlobalBounds().width / 2 +
				wordsButtons.at(wordIndex).getPosition().x, wordsButtons.at(wordIndex).getGlobalBounds().getSize().y / 2 - words.back().getGlobalBounds().height / 2 +
				wordsButtons.at(wordIndex).getPosition().y));
		}
		
		y += WORD_BUTTON_DIS_HEIGHT;
		if (wordIndex % NUMBER_BUTTON_ROW == 3)
		{
			x += WORD_BUTTON_DIS_WIDTH;
			y = Y_FIRST_BUTTON_POSITION;
		}
	}
}

//Draws
void SpeakState::draw(float dt)
{
	data->window.draw(background);
	pet->draw();
	for(sf::Sprite button : wordsButtons)
	{
		data->window.draw(button);
	}
	for(sf::Text text : words)
	{
		data->window.draw(text);
	}
	effects->draw();
	GameState::draw(dt);
}

//Handles input of pam and words' buttons
bool SpeakState::handleInput(sf::Event event)
{
	if (!GameState::handleInput(event))
	{
		if (!isPause)
		{
			bool isPetTouched = pet->handleInput(event);
			if (currentAction == ActioType::STAND)
			{			
				if (isPetTouched)
				{
					touchPet(); //Starts petting the pet
				}
				else
				{	
					for (int wordIndex = 0; wordIndex < wordsButtons.size(); wordIndex++)
					{
						if (data->input.isSpriteClicked(wordsButtons.at(wordIndex), sf::Mouse::Left, data->window))
						{
							sounds->playGameSound(SoundManage::SoundGameType::MOUSE_CLICKED_SOUND);
							speak(wordIndex); //Starts speak
							break;
						}
					}
				}
			}
			else
			{
				if (currentAction == ActioType::PETTED && (event.type == sf::Event::MouseButtonReleased))
				{
					stopAction((clock.getElapsedTime().asSeconds() + exactTime - startPetTime) * 2); //Stops current action
				}
			}
		}
	}	
	return true;
}

//Make the pet talk
void SpeakState::speak(int word)
{		
	wordIndex = word;
	pet->startTalk();
	currentAction = ActioType::TALK;
	if (blockedWords.at(wordIndex)) //If locked word
	{
		wordsButtons.at(wordIndex).setTexture(data->assets.getTexture("Learn Word"));
		words.push_back(sf::Text(static_cast<std::string>(WORDS[wordIndex]), font, 25));
		words.back().setPosition(sf::Vector2f(wordsButtons.at(wordIndex).getGlobalBounds().getSize().x / 2 - words.back().getGlobalBounds().width / 2 +
			wordsButtons.at(wordIndex).getPosition().x, wordsButtons.at(wordIndex).getGlobalBounds().getSize().y / 2 - words.back().getGlobalBounds().height / 2 +
			wordsButtons.at(wordIndex).getPosition().y));

		wordTime = sounds->learn(wordIndex);
		isLearning = true;
	}
	else
	{
		wordTime = sounds->speak(wordIndex);
		isSpeaking = true;
	}
	exactTime = 0;
	clock.restart();
}

//Updates
void SpeakState::update(float dt)
{
	if (!isPause)
	{
		if (currentAction == ActioType::INTRO)
		{
			updatePam(); //Updates pam's speech
		}
		else
		{
			if (currentAction == ActioType::TALK && clock.getElapsedTime().asMicroseconds() + exactTime >= wordTime)
			{
				stopAction(0); //Stops action after talking
			}
			GameState::update(dt);
		}
	}
}

//Starts petting the pet
void SpeakState::touchPet()
{
	pet->beingPetted();
	sounds->playActionSound(SoundManage::SoundActionType::PET_SOUND);
	currentAction = ActioType::PETTED;
	effects->startEffect(EffectsControl::EffectType::PET_EFFECT);
	startPetTime = clock.getElapsedTime().asSeconds();
}

//Stops current action
void SpeakState::stopAction(int xp)
{
	sounds->stop();
	pet->stopAction(xp);
	effects->stopEffect();
	currentAction = ActioType::STAND;
	if (isLearning)
	{
		wordsButtons.at(wordIndex).setTexture(data->assets.getTexture("Unlocked Word")); //Change word button to unlocked
		blockedWords.at(wordIndex) = false;
		isLearning = false;
		speak(wordIndex); //Say the word learned
	}
	else if(isSpeaking)
	{
		isSpeaking = false;
	}
}

//Game over
void SpeakState::gameOver()
{
	removeState(); //Remove the state
}

//Remove state
void SpeakState::removeState()
{
	sounds->switchBackground(SoundManage::SoundBackgroundType::MAIN_GAME_SOUND);
	GameState::removeState();
}

//Destructor
SpeakState::~SpeakState()
{
	delete pam;
}
