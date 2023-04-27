#include "SelectState.h"
#include "Level1.h"
#include <sstream>;
#include <iostream>

//Constructor gets a data and sounds
SelectState::SelectState(gameDataRef data, SoundManage* sounds) : 
	data(data), sounds(sounds), isInstruction(true), isEffect(false)
{
	pam = new BigPam(data, SELECT_PAM, !BigPam::TITLE, !BigPam::WINNING_TITLE);
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

	//Init eggs buttons
	data->assets.loadTexture("Select Menu Bunny Button", ANGEL_FOLDER + std::to_string(0) + ".png");
	animalButtons[0].setTexture(data->assets.getTexture("Select Menu Bunny Button"));
	data->assets.loadTexture("Select Menu Fox Button", COCO_FOLDER + std::to_string(0) + ".png");
	animalButtons[1].setTexture(data->assets.getTexture("Select Menu Fox Button"));
	data->assets.loadTexture("Select Menu Penguin Button", FIFI_FOLDER + std::to_string(0) + ".png");
	animalButtons[2].setTexture(data->assets.getTexture("Select Menu Penguin Button"));
	data->assets.loadTexture("Select Menu Pug Button", BOO_FOLDER + std::to_string(0) + ".png");
	animalButtons[3].setTexture(data->assets.getTexture("Select Menu Pug Button"));

	data->assets.loadTexture("Select Menu Back Button", BACK_BUTTON);
	backButton.setTexture(data->assets.getTexture("Select Menu Back Button"));
	backButton.setPosition(sf::Vector2f(150,500));
	data->assets.loadTexture("Menu Effect", SELECT_EFFECT);
	effect.setTexture(data->assets.getTexture("Menu Effect"));

	//Position eggs
	int  startX = 300, startY= 220, y = startY, x = startX;
	for (int i = 0; i < NUMBER_EGG; i++)
	{
		if (i % 2 == 1)
		{
			x += DIST_EGG_WIDTH;
		}
		else
		{
			x = startX;
		}
		if (i == 2)
		{
			y += DIST_EGG_HEIGHT;
		}
		animalButtons[i].setPosition(sf::Vector2f(x, y));
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
			text[i].setFont(font);
			text[i].setCharacterSize(25);
			text[i].setFillColor(sf::Color{ 249, 85, 162, 255 });
			text[i].setPosition(sf::Vector2f(animalButtons[i].getGlobalBounds().getPosition().x + 20,
				animalButtons[i].getGlobalBounds().getPosition().y + animalButtons[i].getGlobalBounds().height + 2));
		}
	}
	//Sets eggs' names
	text[0].setString("Angel");
	text[1].setString("Coco");
	text[2].setString("Fifi");
	text[3].setString("Boo");
}

//Handles input in case some egg is being touched by the mouse
bool SelectState::handleInput(sf::Event event)
{
	if (isInstruction)
	{
		pam->handleInput(event);
	}
	else
	{
		if (!isEffect)
		{
			//Checks if the mouse touches the egg in order to add effect
			for (int i = 0; i < NUMBER_EGG && !isEffect; i++)
			{
				if (animalButtons[i].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y)))
				{
					isEffect = true;
					effect.setPosition(sf::Vector2f(animalButtons[i].getPosition().x - 14, animalButtons[i].getPosition().y - 17));
					effectTouch = i;
				}
			}
		}
		else
		{
			if (!animalButtons[effectTouch].getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y)))
			{
				isEffect = false;
			}
		}
		//Checks if one egg is being selected and starts new game
		for (int eggIndex = 0; eggIndex < NUMBER_EGG; eggIndex++)
		{
			if (data->input.isSpriteClicked(animalButtons[eggIndex], sf::Mouse::Left, data->window))
			{
				Game::startNewGame();
				sounds->playGameSound(SoundGameType::HAPPY_PET_SOUND);
				data->machine.addState(StateRef(new Level1(data, sounds, static_cast<NooniName>(eggIndex))), true);
				return true;
			}
		}
	}
	if (data->input.isSpriteClicked(backButton, sf::Mouse::Left, data->window))
	{
		sounds->playGameSound(SoundGameType::MOUSE_CLICKED_SOUND);
		data->machine.removeState();
	}
	return true;
}

//Updates pam's speech
void SelectState::update(float dt)
{
	if (pam->getIsDone())
	{
		isInstruction = false;
	}
}

//Draws
void SelectState::draw(float dt)
{
	data->window.draw(background);
	data->window.draw(windowSprite);
	if (isEffect)
	{
		data->window.draw(effect);
	}
	for (int i = 0; i < NUMBER_EGG; i++)
	{
		data->window.draw(animalButtons[i]);
		data->window.draw(text[i]);
	}
	if (isInstruction)
	{
		pam->draw();
	}
	data->window.draw(backButton);
}

//Destructor
SelectState::~SelectState() 
{
	delete pam; 
}