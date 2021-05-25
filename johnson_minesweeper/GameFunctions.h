#pragma once
#include "Minefield.cpp"

enum class ETileInteractions
{
	ETI_Reveal,
	ETI_Highlight,
	ETI_Flag,
	ETI_Restart
};

struct FPlayerTileChoiceIndex
{
	int playerRowChoice;
	int playerColumnChoice;
};

void GreetPlayer();
void PromptPlayerForBoardSize(int& rows, int& columns, int& bombs);
void InitializeGameBoard(int rows, int columns, Minefield::Tile tile, Minefield::Tile* boardOver[]);
void PlaceBombs(int rows, int columns, int bombs, Minefield::Tile* boardOver[]);
void OutputGameBoard(int rows, int columns, int bombs, Minefield::Tile* boardOver[], int indicesLeft, int indicesBottom, bool& overViaBomb, bool& overViaWin);
void SelectTile(FPlayerTileChoiceIndex& TileChoiceIndex);
int TileOptions();
void UpdateGameBoard(int tileIndexROW, int tileIndexCOLUMN, Minefield::Tile tile, int rows, int columns, int bombs, Minefield::Tile* boardOver[], int indicesLeft, int indicesBottom, int& safeTiles, bool& overViaBomb, bool& overViaWin, bool& overViaRestart);
void SetChosenTileInteraction(int optionChosen, ETileInteractions& ChosenTileInteraction);
bool BombCheck(int& tileIndexROW, int& tileIndexCOLUMN, Minefield::Tile* boardOver[], bool& overViaBomb);
void SafeTileCheck(int rows, int columns, Minefield::Tile* boardOver[], int& safeTiles, bool& overViaWin);
bool GameOver(bool& overViaBomb, bool& overViaWin, bool& overViaRestart);
bool GameComplete(bool& gameComplete, bool& gameRestart);
void ClearBoardMemory(int& rows, Minefield::Tile* boardOver[]);