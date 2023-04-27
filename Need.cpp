#include "Need.h"
#include "Definitions.h"

//Constructor gets a data and a need type (being petted, hungry, sleep, clean and fun)
Need::Need(gameDataRef data, Need::NeedType needType) :
	data(data), needType(needType), xp(MoodType::GREEAN_MOOD), currentMood(MoodType::GREEAN_MOOD), showScale(false)
{
	//Sets the position of the need's icon
	int y = NEED_ICON_SIZE * (needType + 1) + Y_FIRST_POSITION;
	std::string typeName; //Name of need's type

	switch (needType)
	{
	case Need::NeedType::LOVE:
		typeName = "pet";
		scaleTime = 4.5f;
		break;
	case Need::NeedType::HUNGER:
		typeName = "hungry";
		scaleTime = 4.0f;
		break;
	case Need::NeedType::TIRED:
		typeName = "sleep";
		scaleTime = 6.0f;
		break;
	case Need::NeedType::CLEAN:
		typeName = "clean";
		scaleTime = 5.0f;
		break;
	default : case Need::NeedType::BORED:
		typeName = "fun";
		scaleTime = 3.5f;
		break;
	}
	//Loads icon's image
	data->assets.loadTexture("Need Icon " + typeName, NEED_SCALE + typeName + ".png");
	SpriteIcon.setTexture(data->assets.getTexture("Need Icon " + typeName));
	SpriteIcon.setPosition(sf::Vector2f(X_POSITION, y));

	//Loading scale's images
	for (int scaleIndex = 0; scaleIndex < NEED_SCALE_FRAMES; scaleIndex++)
	{
		data->assets.loadTexture("Need Scale " + std::to_string(scaleIndex), NEED_SCALE + std::to_string(NEED_SCALE_FRAMES - 1 - scaleIndex) + ".png");
	}
	spriteScale.setTexture(data->assets.getTexture("Need Scale " + std::to_string(0)));
	spriteScale.setPosition(sf::Vector2f(X_POSITION + SpriteIcon.getLocalBounds().height - 2, y + SpriteIcon.getLocalBounds().height / 2));

	//Set mood circle around icon
	ShapeIcon.setRadius(SpriteIcon.getLocalBounds().height / 2 + NEEDS_CIRCLE_DISTANCE);
	ShapeIcon.setFillColor(sf::Color::Green);
	ShapeIcon.setOutlineColor(sf::Color::White);
	ShapeIcon.setOutlineThickness(NEEDS_CIRCLE_DISTANCE);
	ShapeIcon.setPosition(sf::Vector2f(X_POSITION - NEEDS_CIRCLE_DISTANCE, y - NEEDS_CIRCLE_DISTANCE));
}

//Gets the current mood of the need
MoodType Need::getMood()
{
	return currentMood;
}

//draws need's sprites
void Need::draw()
{
	if (showScale)
	{
		data->window.draw(spriteScale);
	}
	data->window.draw(ShapeIcon);
	data->window.draw(SpriteIcon);
}

//Updates need by time
void Need::update(float dt)
{
	if (xp > static_cast<int>(MoodType::BLACK_MOOD))
	{
		float time = scaleTime;
		if (xp <= static_cast<int>(MoodType::RED_MOOD)) //If xp smaller than redMood - time is going faster
		{
			time /= 2.0f;
		}
		if (clock.getElapsedTime().asSeconds() >= time)
		{
			restartClock();
			updateScale(xp--);
		}
	}
}

//Updates the scale and ShapeIcon's color according to the new xp
void Need::updateScale(int oldXp)
{
	int placeXp= static_cast<int>(MoodType::GREEAN_MOOD) - xp;
	spriteScale.setTexture(data->assets.getTexture("Need Scale " + std::to_string(placeXp))); //Sets the new frame of the scale
	if (!xp)
	{
		if (oldXp > static_cast<int>(MoodType::BLACK_MOOD))
		{
			ShapeIcon.setFillColor(sf::Color::Black);
			currentMood = MoodType::BLACK_MOOD;
		}
	}
	else
	{
		if (xp <= static_cast<int>(MoodType::RED_MOOD))
		{
			if (oldXp > static_cast<int>(MoodType::RED_MOOD) || !oldXp)
			{
				ShapeIcon.setFillColor(sf::Color::Red);
				currentMood = MoodType::RED_MOOD;
			}
		}
		else if (xp <= static_cast<int>(MoodType::YELLOW_MOOD))
		{
			if (oldXp > static_cast<int>(MoodType::YELLOW_MOOD) || oldXp <= static_cast<int>(MoodType::RED_MOOD))
			{
				ShapeIcon.setFillColor(sf::Color::Yellow);
				currentMood = MoodType::YELLOW_MOOD;
			}
		}
		else if (oldXp <= static_cast<int>(MoodType::YELLOW_MOOD))
		{
			ShapeIcon.setFillColor(sf::Color::Green);
			currentMood = MoodType::GREEAN_MOOD;
		}
	}
}

//Handles input
void Need::handleInput()
{
	//If the mouse touches SpriteIcon - shows scale
	if (!showScale && SpriteIcon.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y)))
	{
		showScale = true;
	}
	//If the mouse stops touching SpriteIcon - hides scale
	if(showScale && !SpriteIcon.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(data->window).x, sf::Mouse::getPosition(data->window).y)))
	{
		showScale = false;
	}
}

//Increases need's xp
void Need::levelUp(int amount)
{
	int oldXp = xp;
	if (xp + amount >= static_cast<int>(MoodType::GREEAN_MOOD))
	{
		xp = static_cast<int>(MoodType::GREEAN_MOOD);
	}
	else
	{
		xp += amount;
	}
	updateScale(oldXp); //Updates the scale and shapeIcon
}

//Restarts clock
void Need::restartClock()
{
	clock.restart();
}
