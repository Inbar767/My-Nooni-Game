#include "AI.h"
#include "Definitions.h"
#include <iostream>

//Constructor gets a data
Ai::Ai(gameDataRef data) : data(data)
{
	//Push all option for placing a piece for winning. Even places for row, odd places for column
	checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });
	checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });
	checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });
	checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });
	checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });
	checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });
	checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });
	checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });
	checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });
	checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });
	checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });
	checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });
	checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });
	checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });
	checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });
	checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });
	checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });
	checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });
	checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });
	checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });
	checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });
	checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });
	checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });
	checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });
}

//Gets a board, a board of sprites, a gameState for turn and places an O piece on board
void Ai::placePiece(int(*gridArray)[ROW_PIECES][ROW_PIECES], sf::Sprite gridPieces[ROW_PIECES][ROW_PIECES], int* gameState)
{
	//Check if Ai can win
	for (int i = 0; i < checkMatchVector.size(); i++)
	{
		if (checkSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], O_PIECE, gridArray, gridPieces))
		{
			return;
		}
	}
	//Check if player can win and place O piece to prevent it
	for (int i = 0; i < checkMatchVector.size(); i++)
	{
		if (checkSection(checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], X_PIECE, gridArray, gridPieces))
		{
			return;
		}
	}
	//Check if center is empty
	if (checkIfPieceIsEmpty(1, 1, gridArray, gridPieces))
	{
		return;
	}
	//Check if a corner is empty
	if (checkIfPieceIsEmpty(0, 2, gridArray, gridPieces) || checkIfPieceIsEmpty(2, 2, gridArray, gridPieces) ||
		checkIfPieceIsEmpty(0, 0, gridArray, gridPieces) || checkIfPieceIsEmpty(2, 0, gridArray, gridPieces))
	{
		return;
	}

	// check for any other empty piece
	if (checkIfPieceIsEmpty(1, 2, gridArray, gridPieces) || checkIfPieceIsEmpty(0, 1, gridArray, gridPieces) ||
		checkIfPieceIsEmpty(2, 1, gridArray, gridPieces) || checkIfPieceIsEmpty(1, 0, gridArray, gridPieces))
	{
		return;
	}
	*gameState = STATE_PLAYING;
}

//Gets 3 x int and 3 y int as places on board, a piece to check board for, a game board, 
//a sprite board and checks if can win and place O piece on it else returns false
bool Ai::checkSection(int x1, int y1, int x2, int y2, int x, int y, int pieceToCheck, int(*gridArray)[ROW_PIECES][ROW_PIECES], sf::Sprite gridPieces[ROW_PIECES][ROW_PIECES])
{
	if ((*gridArray)[x1][y1] == pieceToCheck && (*gridArray)[x2][y2] == pieceToCheck)
	{
		if (EMPTY_PIECE == (*gridArray)[x][y]) //If last place is empty places O piece
		{
			(*gridArray)[x][y] = O_PIECE;
			gridPieces[x][y].setTexture(this->data->assets.getTexture("O Piece"));
			gridPieces[x][y].setColor(sf::Color(255, 255, 255, 255));

			return true;
		}
	}
	return false;
}

//Gets x, y, board and a board of sprites and checks if the place at x,y is empty and place O piece on it else returns false
bool Ai::checkIfPieceIsEmpty(int x, int y, int(*gridArray)[ROW_PIECES][ROW_PIECES], sf::Sprite gridPieces[ROW_PIECES][ROW_PIECES])
{
	if (EMPTY_PIECE == (*gridArray)[x][y])
	{
		(*gridArray)[x][y] = O_PIECE;
		gridPieces[x][y].setTexture(this->data->assets.getTexture("O Piece"));
		gridPieces[x][y].setColor(sf::Color(255, 255, 255, 255));

		return true;
	}
	return false;
}
