#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include "GameFunctions.h"

void GreetPlayer()
{
	std::cout << "\t\t***Welcome to Minesweeper! Clear the field to win the game. You got this, soldier!***\n";
	std::cout << "\n\n";
}

void PlaceBombs(int rows, int columns, int bombs, Minefield::Tile* boardOver[])
{
	assert(bombs > 0 && bombs < (rows* columns));

	srand(static_cast<unsigned int>(time(0)));

	int bombsPlaced = 0;

	while (bombsPlaced < bombs)
	{
		// This speeds things up DRASTICALLY, relying on one srand() combo is nightmarishly slow.
		// There's probably a more efficient way, but gosh darn it I found a way for now!
		int randomSeededROWS1 = (rand() % (rows)), randomSeededCOLUMNS1 = (rand() % (columns));
		int randomSeededROWS2 = (rand() % (rows)), randomSeededCOLUMNS2 = (rand() % (columns));
		int randomSeededROWS3 = (rand() % (rows)), randomSeededCOLUMNS3 = (rand() % (columns));
		int randomSeededROWS4 = (rand() % (rows)), randomSeededCOLUMNS4 = (rand() % (columns));
		int randomSeededROWS5 = (rand() % (rows)), randomSeededCOLUMNS5 = (rand() % (columns));

		if (bombsPlaced < bombs)
		{
			// Place bomb if location doesn't have one already
			if (boardOver[randomSeededROWS1][randomSeededCOLUMNS1].GetHasBomb() == false)
			{
				boardOver[randomSeededROWS1][randomSeededCOLUMNS1].SetHasBomb(true);
				bombsPlaced++;

				if (bombsPlaced == bombs)
				{
					break;
				}
			}
			else if (boardOver[randomSeededROWS2][randomSeededCOLUMNS2].GetHasBomb() == false)
			{
				boardOver[randomSeededROWS2][randomSeededCOLUMNS2].SetHasBomb(true);
				bombsPlaced++;

				if (bombsPlaced == bombs)
				{
					break;
				}
			}
			else if (boardOver[randomSeededROWS3][randomSeededCOLUMNS3].GetHasBomb() == false)
			{
				boardOver[randomSeededROWS3][randomSeededCOLUMNS3].SetHasBomb(true);
				bombsPlaced++;

				if (bombsPlaced == bombs)
				{
					break;
				}
			}
			else if (boardOver[randomSeededROWS4][randomSeededCOLUMNS4].GetHasBomb() == false)
			{
				boardOver[randomSeededROWS4][randomSeededCOLUMNS4].SetHasBomb(true);
				bombsPlaced++;

				if (bombsPlaced == bombs)
				{
					break;
				}
			}
			else if (boardOver[randomSeededROWS5][randomSeededCOLUMNS5].GetHasBomb() == false)
			{
				boardOver[randomSeededROWS5][randomSeededCOLUMNS5].SetHasBomb(true);
				bombsPlaced++;

				if (bombsPlaced == bombs)
				{
					break;
				}
			}
		}
	}
}

void OutputGameBoard(Minefield::Tile& tileInput, int rows, int columns, int bombs, Minefield::Tile* boardOver[], int indicesLeft, int indicesBottom, bool& overViaBomb, bool& overViaWin)
{
	// Exposes all bomb positions upon ending game
	// For debugging, take out of the first "if" check to see bombs immediately
	if (overViaBomb == true || overViaWin == true)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (boardOver[i][j].GetHasBomb() == true)
				{
					boardOver[i][j].SetTileValue('!');
				}
			}
		}
	}

	indicesLeft = 1;
	indicesBottom = columns;

	// Print each indexed value of the game board
	for (int i = 0; i < rows; ++i)
	{
		// This area is for the left indices
		if (indicesLeft <= rows)
		{
			std::cout << "\n" << " ";
		}
		std::cout << indicesLeft;

		for (int j = 0; j < columns; ++j)
		{
			if (boardOver[i][j].GetState() == Minefield::Tile::State::Hidden)
			{
				std::cout << "   " << boardOver[i][j].GetTileValue() << " ";
			}
			// Will print number if tile is revealed with no bomb
			else if (boardOver[i][j].GetState() == Minefield::Tile::State::Revealed)
			{
				std::cout << "   " << boardOver[i][j].GetRevealedValue() << " ";
			}
		}
		std::cout << "\n";
		indicesLeft++;

	}
	// This area is for the bottom indices
	std::cout << "\n" << "    ";
	for (indicesBottom = 1; indicesBottom <= columns; ++indicesBottom)
	{
		std::cout << " " << indicesBottom << "   ";
		if (indicesBottom == columns)
		{
			break;
		}
	}

	std::cout << "\n\n";
}

int* SelectTile()
{
	int playerInputROW;
	int playerInputCOLUMN;
	char playerChoice;
	int tileChoices[2];
	do
	{
		playerChoice = '\0';

		std::cout << "Please select the tile you want by typing the row (number from the left) then column (number from the bottom).\n";
		std::cout << "ROW: ";
		std::cin >> playerInputROW;
		std::cout << "COLUMN: ";
		std::cin >> playerInputCOLUMN;

		std::cout << "Is that the tile you want to select? (type 'y' for yes or 'n' for no)\n";
		std::cin >> playerChoice;

		if (playerChoice == 'y')
		{
			// The "minus ones" here give us accurate 1 to 1 indexing with the in-game board indices.
			tileChoices[0] = playerInputROW - 1;
			tileChoices[1] = playerInputCOLUMN - 1;

			return tileChoices;
		}
		else if (playerChoice != 'y')
		{
			playerInputROW = NULL;
			playerInputCOLUMN = NULL;
		}
	} while (playerChoice != 'y');
}

int TileOptions()
{
	int optionChosen;

	// Tile options
	do
	{
		std::cout << "\nReveal Tile (1)\n";
		std::cout << "Highlight Tile (2)\n";
		std::cout << "Flag Tile As A Bomb (3)\n";
		std::cout << "Start New Game (4)\n";
		std::cout << "Your choice: ";
		std::cin >> optionChosen;

		if (optionChosen < 1 || optionChosen > 4)
		{
			std::cout << "\nInvalid selection. Type a relevant number, please.\n";
		}
	} while (optionChosen < 1 || optionChosen > 4);

	return optionChosen;
}

void SetChosenTileInteraction(int optionChosen, ETileInteractions& ChosenTileInteraction)
{
	switch (optionChosen)
	{
	case 1:
		ChosenTileInteraction = ETileInteractions::ETI_Reveal;

		break;
	case 2:
		ChosenTileInteraction = ETileInteractions::ETI_Highlight;

		break;
	case 3:
		ChosenTileInteraction = ETileInteractions::ETI_Flag;

		break;
	case 4:
		ChosenTileInteraction = ETileInteractions::ETI_Restart;

		break;
	}
}

void UpdateGameBoard(int tileIndexROW, int tileIndexCOLUMN, Minefield::Tile& tileInput, int rows, int columns, int bombs, Minefield::Tile* boardOver[], int indicesLeft, int indicesBottom, int& safeTiles, bool& overViaBomb, bool& overViaWin, bool& overViaRestart)
{
	if (tileIndexROW >= rows || tileIndexCOLUMN >= columns)
	{
		std::cout << "\nPlease enter a valid position!\n";
	}

	// This is ignored if above condition is not met
	if (tileIndexROW < rows && tileIndexCOLUMN < columns)
	{
		// Checking a 3x3 range for bombs
		int nearbyBombs = 0;
		int rowRange = 1;
		int colRange = 1;

		int rowStart = std::max(tileIndexROW - 1, 0);
		int rowFinish = std::min(tileIndexROW + 1, rows - 1);
		int colStart = std::max(tileIndexCOLUMN - 1, 0);
		int colFinish = std::min(tileIndexCOLUMN + 1, columns - 1);

		for (int curRow = rowStart; curRow <= rowFinish; curRow++)
		{
			for (int curCol = colStart; curCol <= colFinish; curCol++)
			{
				if (boardOver[curRow][curCol].GetHasBomb() == true)
				{
					++nearbyBombs;
				}
			}
		}

		// Declaration and initialization of enum instance
		ETileInteractions ChosenTileInteraction;
		SetChosenTileInteraction(TileOptions(), ChosenTileInteraction);

		// Affect selected tile depending on player's choice
		switch (ChosenTileInteraction)
		{
		case ETileInteractions::ETI_Reveal:
			// Reveal | This area will change the tile to the number of nearby bombs
			boardOver[tileIndexROW][tileIndexCOLUMN].SetTileValue(NULL);
			boardOver[tileIndexROW][tileIndexCOLUMN].SetRevealedValue(nearbyBombs);

			std::cout << "\nREVEAL\n";
			boardOver[tileIndexROW][tileIndexCOLUMN].SetState(Minefield::Tile::State::Revealed);
			BombCheck(tileIndexROW, tileIndexCOLUMN, boardOver, overViaBomb);
			SafeTileCheck(rows, columns, boardOver, safeTiles, overViaWin);

			break;
		case ETileInteractions::ETI_Highlight:
			// Highlight | Turns char to letter H
			if (boardOver[tileIndexROW][tileIndexCOLUMN].GetTileValue() == tileInput.GetTileValue())
			{
				boardOver[tileIndexROW][tileIndexCOLUMN].SetTileValue(tileInput.GetHighlightedValue());
			}
			else if (boardOver[tileIndexROW][tileIndexCOLUMN].GetTileValue() == tileInput.GetHighlightedValue())
			{
				boardOver[tileIndexROW][tileIndexCOLUMN].SetTileValue(tileInput.GetTileValue());
			}
			else if (boardOver[tileIndexROW][tileIndexCOLUMN].GetState() == Minefield::Tile::State::Revealed)
			{
				std::cout << "\nCan't highlight a revealed tile!\n\n";
			}

			break;
		case ETileInteractions::ETI_Flag:
			// Flag | Turns tileValue to letter B if it isn't that already, otherwise turns it back into 'x'
			if (boardOver[tileIndexROW][tileIndexCOLUMN].GetTileValue() == tileInput.GetTileValue())
			{
				boardOver[tileIndexROW][tileIndexCOLUMN].SetTileValue(tileInput.GetFlaggedValue());
			}
			else if (boardOver[tileIndexROW][tileIndexCOLUMN].GetTileValue() == tileInput.GetFlaggedValue())
			{
				boardOver[tileIndexROW][tileIndexCOLUMN].SetTileValue(tileInput.GetTileValue());
			}
			else if (boardOver[tileIndexROW][tileIndexCOLUMN].GetState() == Minefield::Tile::State::Revealed)
			{
				std::cout << "\nCan't flag a revealed tile!\n\n";
			}

			break;
		case ETileInteractions::ETI_Restart:
			// Restart Game Option
			overViaRestart = true;

			break;
		}
	}

	OutputGameBoard(tileInput, rows, columns, bombs, boardOver, indicesLeft, indicesBottom, overViaBomb, overViaWin);
}

bool BombCheck(int& tileIndexROW, int& tileIndexCOLUMN, Minefield::Tile* boardOver[], bool& overViaBomb)
{
	if (boardOver[tileIndexROW][tileIndexCOLUMN].GetHasBomb() == true)
	{
		overViaBomb = true;

		return true;
	}
	else if (boardOver[tileIndexROW][tileIndexCOLUMN].GetHasBomb() == false)
	{
		return false;
	}
}

void SafeTileCheck(int rows, int columns, Minefield::Tile* boardOver[], int& safeTiles, bool& overViaWin)
{
	int revealedTiles = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (boardOver[i][j].GetState() == Minefield::Tile::State::Revealed)
			{
				revealedTiles++;
			}
		}
	}

	if (revealedTiles == safeTiles)
	{
		overViaWin = true;
	}
	else
	{
		overViaWin = false;
	}
}

bool GameOver(bool& overViaBomb, bool& overViaWin, bool& overViaRestart)
{
	if (overViaBomb == true)
	{
		std::cout << "\n\t\t\t\t***KABOOM*** GAME OVER, CAPTAIN PEG-LEG";
		return overViaBomb;
	}
	else if (overViaWin == true)
	{
		std::cout << "\n\t\t***YOU WIN!!*** Great job, soldier! Now go home to your wife and suspiciously tan baby.";
		return overViaWin;
	}
	else if (overViaRestart == true)
	{
		std::cout << "\n\t\t\t\t\t***GAME ENDED EARLY***";
		return overViaRestart;
	}
}

bool GameComplete(bool& gameComplete, bool& gameRestart)
{
	int playerChoice;
	std::cout << "\nWould you like to: \n\n(1) Play Again\n(2) Exit Game\n\n";

	do
	{
		std::cout << "Input either 1 or 2 to choose: ";
		std::cin >> playerChoice;
		if (playerChoice == 1)
		{
			gameRestart = true;
			gameComplete = false;
			std::cout << "\nGame Board cleared. Let's go again!\n\n";

			return gameComplete;
		}
		else if (playerChoice == 2)
		{
			gameComplete = true;
			std::cout << "\nGame Board cleared. Thanks for playing!!";

			return gameComplete;
		}
		else if (playerChoice != 1 && playerChoice != 2)
		{
			std::cout << "Invalid option!\n";
		}
	} while (playerChoice != 1 && playerChoice != 2);
}