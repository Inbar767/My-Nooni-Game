#pragma once

#include "Game.h"
#include "Definitions.h"
#include <vector>
#include <array>

//Class for AI playing Tic Tac Toe against user
class Ai
{
public:
	//Constructor
	Ai(gameDataRef data);
	//Destructor
	~Ai() = default;
	//Gets a board, a board of sprites, a gameState for turn and places an O piece on board
	void placePiece(int(*gridArray)[ROW_PIECES][ROW_PIECES], sf::Sprite gridPieces[ROW_PIECES][ROW_PIECES], int* gameState);

private:
	//Gets 3 x int and 3 y int as places on board, a piece to check board for, a game board,
	//a sprite board and checks if can win and place O piece on it else returns false
	bool checkSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[ROW_PIECES][ROW_PIECES], sf::Sprite gridPieces[ROW_PIECES][ROW_PIECES]);
	//Gets x, y, board and a board of sprites and checks if the place at x,y is empty and place O piece on it else returns false
	bool checkIfPieceIsEmpty(int X, int Y, int(*gridArray)[ROW_PIECES][ROW_PIECES], sf::Sprite gridPieces[ROW_PIECES][ROW_PIECES]);

	std::vector<std::array<int, 6> > checkMatchVector; //Holds possible solutions for game. Even places for row, odd places for column

	gameDataRef data;
};

