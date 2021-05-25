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
		int rows, columns, bombs;

		Minefield minefield;
		Minefield::Tile tile;
		FPlayerTileChoiceIndex TileChoiceIndex;

		GreetPlayer();
		PromptPlayerForBoardSize(rows, columns, bombs);

		int safeTiles = ((rows * columns) - bombs);

		Minefield::Tile** boardOver = new Minefield::Tile * [rows];
		InitializeGameBoard(rows, columns, tile, boardOver);
		
		int indicesLeft = rows;
		int indicesBottom = columns;

		PlaceBombs(rows, columns, bombs, boardOver);
		OutputGameBoard(rows, columns, bombs, boardOver, indicesLeft, indicesBottom, overViaBomb, overViaWin);

		// TILE SELECT LOOP
		while (gameComplete == false)
		{
			SelectTile(TileChoiceIndex);
			UpdateGameBoard(TileChoiceIndex.playerRowChoice, TileChoiceIndex.playerColumnChoice, tile, rows, columns, bombs, boardOver, indicesLeft, indicesBottom, safeTiles, overViaBomb, overViaWin, overViaRestart);

			if (GameOver(overViaBomb, overViaWin, overViaRestart) == true)
			{
				if (GameComplete(gameComplete, gameRestart) == false)
				{
					break;
				}
			}
		}

		ClearBoardMemory(rows, boardOver);
	} while (gameRestart == true && gameComplete == false); // P.S. I know the "== true" is redundant, but gosh darn it this is MY program!! >:.(

	return 0;
}