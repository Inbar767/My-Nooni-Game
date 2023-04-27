#include "Animation.h"
#include <iostream>

//Constructor gets a data, the name of the file of the sprite and numbers of frames on the file and load all frames into animationFrames
Animation::Animation(gameDataRef data, const std::string& textureFileName, int numFrames) :
	animationIterator(0), isReverse(false), currentAction(""), totalFramesNumbers(numFrames), data(data)
{
	for (int i = 0; i < numFrames; i++)
	{
		data->assets.loadTexture(textureFileName + std::to_string(i), textureFileName + std::to_string(i) + ".png");
		animationFrames.push_back(data->assets.getTexture(textureFileName + std::to_string(i)));
	}
}

//Constructor gets a data, the name of the file of the sprite and numbers of frames on the file and the position of the sprite
//loads all frames into animationFrames and changes the position
Animation::Animation(gameDataRef data, const std::string& textureFileName, int numFrames, sf::Vector2f position) :
	Animation(data, textureFileName, numFrames)
{
	sprite.setPosition(position);
}

//Gets name of the action, first and last indexes of frames, the time for each frame to be drawn and if the animation includes a reversion
//and add the new action into actions
void Animation::addAction(const std::string& actionName, int firstFrame, int lastFrame, float time, bool isReverse)
{
	if (firstFrame < totalFramesNumbers)
	{
		if (lastFrame >= totalFramesNumbers)
		{
			lastFrame = totalFramesNumbers - 1;
		}
		bool isAnimation = (firstFrame != lastFrame);
		actions[actionName] = AnimationAction(firstFrame, lastFrame, isAnimation, isReverse);
		for (int i = firstFrame; i <= lastFrame; i++)
		{
			actions[actionName].times.insert({ i, time });
		}
	}
	else
	{
		std::cout << "Can't create action\n";
	}
}

//Gets an action name, frame index and a time and changes the frame's time in this action according
void Animation::changeFrameTime(const std::string& actionName, int frameNumber, float time)
{
	if (actions.contains(actionName) && frameNumber >= actions[actionName].firstFrame && frameNumber <= actions[actionName].lastFrame)
	{
		actions[actionName].times.at(frameNumber) = time;
	}
	else
	{
		std::cout << "The frame is out of bound\n";
	}
}

//Gets an action name and start it
void Animation::startAction(const std::string& actionName)
{
	if (actions.contains(actionName))
	{
		currentAction = actionName;
		isReverse = false;
		animationIterator = actions[currentAction].firstFrame;
		sprite.setTexture(animationFrames.at(animationIterator), true);
		time = actions[currentAction].times.at(animationIterator);
		clock.restart();
	}
	else
	{
		std::cout << "There is no action called" << actionName << "\n";
	}
}

//Sends the position of the sprite
sf::Vector2f Animation::getPosition()
{
	return sprite.getPosition();
}

//Gets a vector2f  and changes the position of the sprite
void Animation::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}

//Animates the sprite
bool Animation::animation()
{
	if (isReverse) //Go to reveresionAnimation function to animate the reversion of the animation
	{
		return reveresionAnimation();
	}
	bool isDone = false;
	if (currentAction != "" && actions[currentAction].isAnimation)
	{
		if (clock.getElapsedTime().asSeconds() > time)
		{
			if (animationIterator < actions[currentAction].lastFrame)
			{
				animationIterator++;
			}
			else
			{
				if (actions[currentAction].isReverse)
				{
					isReverse = true;
				}
				else
				{
					animationIterator = actions[currentAction].firstFrame;
					isDone = true;
				}
			}
			if (!isReverse)
			{
				time = actions[currentAction].times.at(animationIterator);
				sprite.setTexture(animationFrames.at(animationIterator), true);
			}
			clock.restart();
		}
	}
	return isDone;
}

//Animates the reversion of the animation
bool Animation::reveresionAnimation()
{
	bool isDone = false;
	if (clock.getElapsedTime().asSeconds() > time)
	{
		if (animationIterator > actions[currentAction].firstFrame)
		{
			animationIterator--;
		}
		else
		{
			isDone = true;
			isReverse = false;
			animationIterator = actions[currentAction].firstFrame;
		}
		time = actions[currentAction].times.at(animationIterator);
		sprite.setTexture(animationFrames.at(animationIterator), true);
		clock.restart();
	}
	return isDone;
}

//Draws the sprite
void Animation::draw()
{
	if (currentAction != "")
	{
		data->window.draw(sprite);
	}
}

//Restarts the clock
void Animation::restartClock()
{
	clock.restart();
}

//Handles input - checks if the sprite is being clicked by the mouse and returns true if so
bool Animation::handleInput(sf::Event event)
{
	if (currentAction != "" && data->input.isSpriteClicked(sprite, sf::Mouse::Left, data->window))
	{
		return true;
	}
	return false;
}

//Sends the current action is played
std::string Animation::getCurrentAction()
{
	return currentAction;
}

//Gets a color and changes the sprite's color according
void Animation::setColor(sf::Color color)
{
	sprite.setColor(color);
}

//Sends the width of the sprite
float Animation::getSpriteWidth()
{
	return sprite.getGlobalBounds().width;
}

//Sends the height of the sprite
float Animation::getSpriteHeigth()
{
	return sprite.getGlobalBounds().height;
}