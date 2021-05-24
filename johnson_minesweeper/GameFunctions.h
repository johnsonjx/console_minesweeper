#pragma once
#include "Minefield.cpp"

void GreetPlayer();
void PlaceBombs(int rows, int columns, int bombs, Minefield::Tile* boardOver[]);
void OutputGameBoard(Minefield::Tile& tileInput, int rows, int columns, int bombs, Minefield::Tile* boardOver[], int indicesLeft, int indicesBottom, bool& overViaBomb, bool& overViaWin);
int* SelectTile();
int TileOptions();
void UpdateGameBoard(int tileIndexROW, int tileIndexCOLUMN, Minefield::Tile& tileInput, int rows, int columns, int bombs, Minefield::Tile* boardOver[], int indicesLeft, int indicesBottom, int& safeTiles, bool& overViaBomb, bool& overViaWin, bool& overViaRestart);
bool BombCheck(int& tileIndexROW, int& tileIndexCOLUMN, Minefield::Tile* boardOver[], bool& overViaBomb);
void SafeTileCheck(int rows, int columns, Minefield::Tile* boardOver[], int& safeTiles, bool& overViaWin);
bool GameOver(bool& overViaBomb, bool& overViaWin, bool& overViaRestart);
bool GameComplete(bool& gameComplete, bool& gameRestart);