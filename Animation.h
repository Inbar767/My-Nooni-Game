#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
#include "Definitions.h"
#include <map>

//A struct for sprite's action
struct AnimationAction {
	int firstFrame; //The index of first frame
	int lastFrame; //The index of last frame
	bool isAnimation; //Is it only one frame action or an animation
	bool isReverse; //Is the animation include reversion
	std::map <int, float> times; //A map of action's indexes with their times
};

//A class for drawing animation
class Animation
{
public:

	//Constructors
	Animation(gameDataRef data, const std::string& textureFileName, int numFrames);
	Animation(gameDataRef data, const std::string& textureFileName, int numFrames, sf::Vector2f position);
	//Destructor
	~Animation() = default;
	//Sends the name of the current action is being played
	std::string getCurrentAction();
	//Sends the sprite's width
	float getSpriteWidth();
	//Sends the sprite's height
	float getSpriteHeigth();
	//Sends the current position of the sprite
	sf::Vector2f getPosition();
	//Changes the current position of the sprite
	void setPosition(sf::Vector2f position);
	//Changes the color of the sprite
	void setColor(sf::Color color);
	//Adding new action for sprite
	void addAction(const std::string& actionName, int firstFrame, int lastFrame, float time, bool isReverse);
	//Changing the time of a frame
	void changeFrameTime(const std::string& actionName, int frameNumber, float time);
	//Playes action
	void startAction(const std::string& actionName);
	//Animates the sprite by changing frames according time
	bool animation();
	//Draws the sprite
	void draw();
	//Restarts clock
	void restartClock();
	//Handles the input
	bool handleInput(sf::Event event);

private:

	//Animates the sprite from last frame to first frame index
	bool reveresionAnimation();

	sf::Sprite sprite; 
	std::vector <sf::Texture> animationFrames; //Frames of the sprite
	std::map <std::string, AnimationAction> actions; //Map of the actions the sprite has

	int animationIterator; //Current frame of the sprite
	std::string currentAction;  //Current action of the sprite
	float time; //Time to go next frame
	bool isReverse; //Is the reversion of animation is being played
	int totalFramesNumbers; //Total number of frames the sprites has

	gameDataRef data;
	sf::Clock clock;
};

