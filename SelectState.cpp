#include "SelectState.h"
#include "Level1.h"
#include <iostream>

Pet* pet;
EffectsControl* effects;

//Constructor gets a data and sounds
SelectState::SelectState(gameDataRef data, SoundManage* sounds) : 
	data(data), sounds(sounds), isInstruction(true), isEffect(false)
{
	pam = new BigPam(data, SELECT_PAM, !BigPam::TITLE, !BigPam::WINNING_TITLE);
	effects = new EffectsControl(data);
}

//Init
void SelectState::init()
{
	data->assets.loadTexture("Select Menu Background", YARD_BACKGROUND);
	background.setTexture(data->assets.getTexture("Select Menu Background"));
	data->assets.loadTexture("Window Background", CANDY_WINDOW);
	windowSprite.setTexture(data->assets.getTexture("Window Background"));
	windowSprite.setPosition(sf::Vector2f(data->window.getSize().x / 2 - windowSprite.getGlobalBounds().width / 2,
		data->window.getSize().y / 2 - windowSprite.getGlobalBounds().height / 2));
	data->assets.loadTexture("Select Menu Back Button", BACK_BUTTON);
	backButton.setTexture(data->assets.getTexture("Select Menu Back Button"));
	backButton.setPosition(sf::Vector2f(150,500));
	data->assets.loadTexture("Menu Effect", SELECT_EFFECT);
	effect.setTexture(data->assets.getTexture("Menu Effect"));
	data->assets.loadTexture("Select Egg Title", SELECT_EGG_TITLE);
	selectEggTitle.setTexture(data->assets.getTexture("Select Egg Title"));
	selectEggTitle.setPosition(sf::Vector2f(windowSprite.getGlobalBounds().width / 2 + windowSprite.getGlobalBounds().getPosition().x - selectEggTitle.getGlobalBounds().width / 2,
		windowSprite.getGlobalBounds().height / 2 + windowSprite.getGlobalBounds().getPosition().y - selectEggTitle.getGlobalBounds().height / 2));

	//Init eggs buttons
	data->assets.loadTexture("Select Menu Bunny Button", ANGEL_FOLDER + std::to_string(0) + ".png");
	eggButtons[0].setTexture(data->assets.getTexture("Select Menu Bunny Button"));
	data->assets.loadTexture("Select Menu Fox Button", COCO_FOLDER + std::to_string(0) + ".png");
	eggButtons[1].setTexture(data->assets.getTexture("Select Menu Fox Button"));
	data->assets.loadTexture("Select Menu Penguin Button", FIFI_FOLDER + std::to_string(0) + ".png");
	eggButtons[2].setTexture(data->assets.getTexture("Select Menu Penguin Button"));
	data->assets.loadTexture("Select Menu Pug Button", BOO_FOLDER + std::to_string(0) + ".png");
	eggButtons[3].setTexture(data->assets.getTexture("Select Menu Pug Button"));

	//Position eggs
	int firstX, x, firstY, y;
	firstX = x = windowSprite.getGlobalBounds().width / NUMBER_EGG + windowSprite.getGlobalBounds().getPosition().x;
	firstY = y = windowSprite.getGlobalBounds().height / NUMBER_EGG + windowSprite.getGlobalBounds().getPosition().y;
	for (int eggIndex = 0; eggIndex < NUMBER_EGG; eggIndex++)
	{
		if (eggIndex % NUMBER_EGG_ROW == 1)
		{
			x += windowSprite.getGlobalBounds().width / 2;
		}
		else if (eggIndex == NUMBER_EGG_ROW)
		{
			x = firstX;
			y += windowSprite.getGlobalBounds().height / 2;
		}
		eggButtons[eggIndex].setPosition(sf::Vector2f(x - eggButtons[eggIndex].getGlobalBounds().width / 2, y - eggButtons[eggIndex].getGlobalBounds().height / 2));
	}
	//Loads font for text
	if (!font.loadFromFile("fonts/retganon.ttf"))
	{
		std::cout << "couldn't open font!";
	}
	else
	{
		for (int i = 0; i < NUMBER_EGG; i++)
		{
			eggName[i].setString(static_cast<std::string>(EGGS_NAMES[i]));
			eggName[i].setFont(font);
			eggName[i].setCharacterSize(25);
			eggName[i].setFillColor(sf::Color{ 249, 85, 162, 255 });
			eggName[i].setPosition(sf::Vector2f(eggButtons[i].getGlobalBounds().getPosition().x + 20,
				eggButtons[i].getGlobalBounds().getPosition().y + eggButtons[i].getGlobalBounds().height + 2));
		}
	}
}

//Handles input in case some egg is being touched by the mouse
bool SelectState::handleInput(sf::Event event)
{
	if (data->input.isSpriteClicked(backButton, sf::Mouse::Left, data->window))
	{
		sounds->playGameSound(SoundManage::SoundGameType::MOUSE_CLICKED_SOUND);
		data->machine.removeState();
	}
	else
	{
		if (isInstruction)
		{
			pam->handleInput(event);
		}
		else if (isEffect && !eggButtons[effectTouch].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y)))
		{
			isEffect = false;
		}
		else
		{	
			for (int eggIndex = 0; eggIndex < NUMBER_EGG; eggIndex++)
			{
				if (eggButtons[eggIndex].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y)))
				{
					isEffect = true;
					effect.setPosition(sf::Vector2f(eggButtons[eggIndex].getPosition().x - 14, eggButtons[eggIndex].getPosition().y - 17));
					effectTouch = eggIndex;
					if (data->input.isSpriteClicked(eggButtons[eggIndex], sf::Mouse::Left, data->window))
					{
						Game::startNewGame();
						sounds->playGameSound(SoundManage::SoundGameType::HAPPY_PET_SOUND);
						isGameStarted = true;
						data->machine.addState(StateRef(new Level1(data, sounds, (pet = new Pet(data, static_cast<Pet::NooniName>(eggIndex))), effects)), false);
					}
					break;
				}
			}
		}
	}
	return true;
}

//Updates pam's speech
void SelectState::update(float dt)
{
	if (isInstruction && pam->getIsDone())
	{
		isInstruction = false;
	}
}

//Draws
void SelectState::draw(float dt)
{
	data->window.draw(background);
	data->window.draw(windowSprite);
	if (isInstruction)
	{
		pam->draw();
	}
	else
	{
		data->window.draw(selectEggTitle);
		if (isEffect)
		{
			data->window.draw(effect);
		}
		for (int eggIndex = 0; eggIndex < eggButtons.size(); eggIndex++)
		{
			data->window.draw(eggButtons[eggIndex]);
			data->window.draw(eggName[eggIndex]);
		}
	}
	data->window.draw(backButton);
}

//Resumes this State
void SelectState::resume()
{
	if (isGameStarted)
	{
		delete pet;
	}
}

//Destructor
SelectState::~SelectState() 
{
	delete pam; 
	delete pet;
	delete effects;
}
