#include "TicTacToe.h"
#include "Definitions.h"
#include <iostream>

//Constructor gets a data
TicTacToe::TicTacToe(gameDataRef data) : data(data)
{
	gameState = STATE_PLAYING; //User turn to play

	this->ai = new Ai(data);
	//Loads game board and pieces
	data->assets.loadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
	data->assets.loadTexture("X Piece", X_PIECE_FILEPATH);
	data->assets.loadTexture("O Piece", O_PIECE_FILEPATH);
	gridSprite.setTexture(data->assets.getTexture("Grid Sprite"));
	gridSprite.setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - (gridSprite.getGlobalBounds().width / 2), 
		(SCREEN_HEIGHT / 2) - ((gridSprite.getGlobalBounds().height) / 2) - 150));

	initGridPieces(); //Place invisible pieces on board

	//Changes all places on board to be empty
	for (int x = 0; x < ROW_PIECES; x++)
	{
		for (int y = 0; y < ROW_PIECES; y++)
		{
			gridArray[x][y] = EMPTY_PIECE;
		}
	}
}

//Handles input of board
void TicTacToe::handleInput(sf::Event event)
{
	if (data->input.isSpriteClicked(this->gridSprite, sf::Mouse::Left, data->window))
	{
		this->checkAndPlacePiece(data->input.getMousePosition(data->window)); //Place the piece if empty place
	}
}

//Updates game status
bool TicTacToe::update(float dt)
{
	if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
	{
		return true;
	}
	return false;
}

//Draws board and pieces
void TicTacToe::draw(float dt)
{
	data->window.draw(this->gridSprite);

	for (int x = 0; x < ROW_PIECES; x++)
	{
		for (int y = 0; y < ROW_PIECES; y++)
		{
			data->window.draw(this->gridPieces[x][y]);
		}
	}
}

//Init invisible X pieces on all places on board
void TicTacToe::initGridPieces()
{
	sf::Vector2u tempSpriteSize = data->assets.getTexture("X Piece").getSize();

	for (int x = 0; x < ROW_PIECES; x++)
	{
		for (int y = 0; y < ROW_PIECES; y++)
		{
			gridPieces[x][y].setTexture(data->assets.getTexture("X Piece"));
			gridPieces[x][y].setPosition(sf::Vector2f(gridSprite.getPosition().x + (tempSpriteSize.x * x), 
				gridSprite.getPosition().y + (tempSpriteSize.y * y)));
			gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
		}
	}
}

//Gets a point on board and checks if the chosen place is empty
void TicTacToe::checkAndPlacePiece(sf::Vector2i touchPoint)
{
	sf::Vector2u size = data->assets.getTexture("X Piece").getSize(); //Gets X piece size
	sf::Vector2 gridSectionPoint =  gridSprite.getPosition(); //Gets position of the board

	int column, row;

	//Checks which column the user has clicked
	if (touchPoint.x < gridSectionPoint.x + size.x) // First Column
	{
		column = 0;
	}
	else if (touchPoint.x < (gridSectionPoint.x + (size.x * 2))) // Second Column
	{
		column = 1;
	}
	else  // Third Column
	{
		column = 2;
	}

	//Checks which row the user has clicked
	if (touchPoint.y < gridSectionPoint.y + size.y) // First Row
	{
		row = 0;
	}
	else if (touchPoint.y < gridSectionPoint.y + (size.y * 2)) // Second Row
	{
		row = 1;
	}
	else // Third Row
	{
		row = 2;
	}

	if (gridArray[column][row] == EMPTY_PIECE) //Checks if the chosen place is empty
	{
		gridArray[column][row] = X_PIECE;
		this->checkHasPlayerWon(); //Checks if X piece win
		gridPieces[column][row].setColor(sf::Color(255, 255, 255, 255));
	}
}

//Checks if a player win
void TicTacToe::checkHasPlayerWon()
{
	//Checks if user win with this pieces on board
	check3PiecesForMatch(0, 0, 1, 0, 2, 0, X_PIECE);
	check3PiecesForMatch(0, 1, 1, 1, 2, 1, X_PIECE);
	check3PiecesForMatch(0, 2, 1, 2, 2, 2, X_PIECE);
	check3PiecesForMatch(0, 0, 0, 1, 0, 2, X_PIECE);
	check3PiecesForMatch(1, 0, 1, 1, 1, 2, X_PIECE);
	check3PiecesForMatch(2, 0, 2, 1, 2, 2, X_PIECE);
	check3PiecesForMatch(0, 0, 1, 1, 2, 2, X_PIECE);
	check3PiecesForMatch(0, 2, 1, 1, 2, 0, X_PIECE);

	if (STATE_WON != gameState) //If user isn't win
	{
		gameState = STATE_AI_PLAYING;

		ai->placePiece(&gridArray, gridPieces, &gameState); //AI place a piece on board
		//Checks if ai win with this pieces on board
		check3PiecesForMatch(0, 0, 1, 0, 2, 0, O_PIECE);
		check3PiecesForMatch(0, 1, 1, 1, 2, 1, O_PIECE);
		check3PiecesForMatch(0, 2, 1, 2, 2, 2, O_PIECE);
		check3PiecesForMatch(0, 0, 0, 1, 0, 2, O_PIECE);
		check3PiecesForMatch(1, 0, 1, 1, 1, 2, O_PIECE);
		check3PiecesForMatch(2, 0, 2, 1, 2, 2, O_PIECE);
		check3PiecesForMatch(0, 0, 1, 1, 2, 2, O_PIECE);
		check3PiecesForMatch(0, 2, 1, 1, 2, 0, O_PIECE);
	}

	int emptyNum = ROW_PIECES * ROW_PIECES;

	for (int x = 0; x < ROW_PIECES; x++)
	{
		for (int y = 0; y < ROW_PIECES; y++)
		{
			if (EMPTY_PIECE != gridArray[x][y])
			{
				emptyNum--;
			}
		}
	}

	// check if the game is a draw
	if (0 == emptyNum && (STATE_WON != gameState) && (STATE_LOSE != gameState))
	{
		gameState = STATE_DRAW;
	}
}

//Gets 3 places on board and the played piece and checks if win
void TicTacToe::check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck)
{
	//Checks is pieceToCheck win with this pieces on board
	if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3]) 
	{
		if (X_PIECE == pieceToCheck)
		{
			gameState = STATE_WON;
		}
		else
		{
			gameState = STATE_LOSE;
		}
	}
}

TicTacToe::~TicTacToe()
{
	delete ai;
}