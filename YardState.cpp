#include "YardState.h"
#include <iostream>

//Constructor get a data, sounds, effects, a pet and a type of game to play with the pet
YardState::YardState(gameDataRef data, SoundManage* sounds, EffectsControl* effects, Pet* pet, ToysType gamePlayed) :
    GameState(data, sounds, effects, pet), gamePlayed(gamePlayed)
{
    currentAction = ActioType::STAND;
    if (gamePlayed == ToysType::TIC_TAC_TOE)
    {
        isPlayed = true;
        ticTacToe = new TicTacToe(data);
    }
    else
    {
        if (gamePlayed < ToysType::BALL && gamePlayed > ToysType::TIC_TAC_TOE) //Checks if gameType has a valid value
        {
            this->gamePlayed = ToysType::BALL;
        }
        isPlayed = false;
    }
}

//Init
void YardState::init()
{
    GameState::init();
    data->assets.loadTexture("Yard Background", YARD_BACKGROUND);
    background.setTexture(data->assets.getTexture("Yard Background"));
}

//Handles input of the games
bool YardState::handleInput(sf::Event event)
{
    if (!GameState::handleInput(event) && !isPause)
    {
        bool isPetTouched = pet->handleInput(event);
        if ((gamePlayed == ToysType::TIC_TAC_TOE))
        {
          if (isPlayed)
          {
             ticTacToe->handleInput(event);
          }
        }
        else
        {
            if (isPetTouched && !isPlayed)
            {
              touchPet();
            }
        }
    }
    return true;
}

//Updates pam and pet
void YardState::update(float dt)
{
    if (!isPause)
    {
        if (currentAction == ActioType::INTRO)
        {
            if (pam->getIsDone())
            {
                removeState();
            }
        }
        else
        {
            if ((gamePlayed != ToysType::TIC_TAC_TOE))
            {
                if (isPlayed && !effects->isEffect())
                {
                    stopAction(PLAYING_PET_XP); //Stops pet playing action
                }
            }
            else if (isPlayed)
            {
                if (ticTacToe->update(dt)) //Ends tic tac toe game with the pet playing
                {
                  isPlayed = false;
                  pet->startPlay();
                  stopAction(PLAYING_PET_XP * 3);
                  pet->startPlay();
                  sounds->playGameSound(SoundGameType::HAPPY_PET_SOUND);
                }
                else
                {
                    float currentTime = clock.getElapsedTime().asSeconds();
                    if (pet->getActionType() == ActioType::PLAY)
                    {
                        if (currentTime >= PET_PLAYS_TIME / 1.6)
                        {
                            stopAction(PLAYING_PET_XP); //Stops pet playing action
                    }
                }
                else
                {
                    if (currentTime >= PET_PLAYS_TIME)
                    {
                        startPlay(); //Make the pet start playing
                     }
                }
            }
        }
    }
    GameState::update(dt);
    }
}

//draws 
void YardState::draw(float dt)
{
    data->window.draw(background);
    pet->draw();
    if (gamePlayed == ToysType::TIC_TAC_TOE)
    {
        ticTacToe->draw(dt);
    }
    else
    {
        effects->draw();
    }
    GameState::draw(dt);
}

//Make pet start playing
void YardState::startPlay()
{
    currentAction = ActioType::PLAY;
    pet->startPlay();
    sounds->playActionSound(SoundActionType::PLAY_SOUND);
    clock.restart();
}

//Start playing when pet is being touched
void YardState::touchPet()
{
    effects->startEffect(static_cast<EffectType>(gamePlayed));
    startPlay(); //Make the pet start playing
    isPlayed = true;
}

//Stops current action
void YardState::stopAction(int xp)
{
    if (gamePlayed != ToysType::TIC_TAC_TOE)
    {
        isPlayed = false;
    }
    else
    {
        clock.restart();
        currentAction = ActioType::STAND;
    }
    pet->stopAction(xp);
    sounds->stop();
}

//Game over
void YardState::gameOver()
{
    removeState(); //Removes the state
}