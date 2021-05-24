#include <iostream>
#include "Minefield.h"
#include "GameFunctions.h"


int main()
{
	bool gameComplete = false, gameRestart = false;

	// MAIN GAME LOOP
	do
	{
		bool overViaBomb = false, overViaWin = false, overViaRestart = false;
		int rows;
		int columns;
		int bombs;

		Minefield minefield;
		Minefield::Tile tile;

		GreetPlayer();
		do
		{
			std::cout << "ROWS: ";
			std::cin >> rows;
			std::cout << "COLUMNS: ";
			std::cin >> columns;

			if (rows < 2 && columns < 2)
			{
				std::cout << "\nIncrease either row or column amount.\n";
			}
		} while (rows < 2 && columns < 2);

		do
		{
			std::cout << "BOMBS: ";
			std::cin >> bombs;
			if (bombs >= (rows * columns))
			{
				std::cout << "\nToo many bombs. This is a game, not a suicide.\n";
			}
		} while (bombs >= (rows * columns));

		std::cout << "\nThe bombs are set. Good luck!" << "\n";

		int safeTiles = ((rows * columns) - bombs);

		// This area allots space for tiles
		// Dynamic memory allocation was necessary, along with a different method of creating/sizing the 2D Array.
		// REMINDER: Make sure to use "delete" (with loop) later to prevent memory leaks!!

		Minefield::Tile** boardOver = new Minefield::Tile * [rows];
		for (int i = 0; i < rows; i++)
		{
			boardOver[i] = new Minefield::Tile[columns];
		}

		// This area iterates through our dynamic 2D array and places a Tile object in each slot
		// Also sets default state of each tile
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				boardOver[i][j] = tile;
				boardOver[i][j].SetState(Minefield::Tile::State::Hidden);
			}
		}

		int indicesLeft = rows;
		int indicesBottom = columns;

		PlaceBombs(rows, columns, bombs, boardOver);
		OutputGameBoard(tile, rows, columns, bombs, boardOver, indicesLeft, indicesBottom, overViaBomb, overViaWin);

		// TILE SELECT LOOP
		while (gameComplete == false)
		{
			int* selectedTileIndex = SelectTile();

			/*RevealTile(selectedTileIndex[0], selectedTileIndex[1], boardOver[selectedTileIndex[0]][selectedTileIndex[1]].state, boardOver);*/
			UpdateGameBoard(selectedTileIndex[0], selectedTileIndex[1], tile, rows, columns, bombs, boardOver, indicesLeft, indicesBottom, safeTiles, overViaBomb, overViaWin, overViaRestart);

			if (GameOver(overViaBomb, overViaWin, overViaRestart) == true)
			{
				if (GameComplete(gameComplete, gameRestart) == false)
				{
					break;
				}
			}
		}

		// CLEAR DYNAMIC MEMORY/MINEFIELD
		for (int i = 0; i < rows; i++)
		{
			delete[] boardOver[i];
		}
		delete[] boardOver;

	} while (gameRestart == true && gameComplete == false); // P.S. I know the "== true" is redundant, but gosh darn it this is MY program!! >:.(

	return 0;
}