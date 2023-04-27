#pragma once

#include "Game.h"
#include "AI.h"
#include "Definitions.h"

//A class for Tic Tac Toe game agains AI
class TicTacToe
{
public:
	//Constructor
	TicTacToe(gameDataRef data);
	//Destructor
	~TicTacToe();
	//Handles input
	void handleInput(sf::Event event);
	//Updates game
	bool update(float dt);
	//Draws
	void draw(float dt);

private:
	//Init invisible X pieces on all places on board
	void initGridPieces();
	//Gets a point on board and checks if the chosen place is empty
	void checkAndPlacePiece(sf::Vector2i touchPoint);
	//Checks if a player win
	void checkHasPlayerWon();
	//Gets 3 places on board and the played piece and checks if win
	void check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);

	gameDataRef data;

	sf::Sprite gridSprite; //Board sprite

	sf::Sprite gridPieces[ROW_PIECES][ROW_PIECES]; //Sprites of pieces located on board
	int gridArray[ROW_PIECES][ROW_PIECES]; //Pieces located on board 

	int gameState; //State turn to play

	Ai* ai;
};

