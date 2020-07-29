#include "pch.h"
#include "GameBoard.h"

GameBoard::GameBoard() : blockOnBoard(NULL),
bRows(3), bColumns(4),
bHeight(35), bWidth(35),
bRemaining(0)
{
	blockColours[0] = RGB(0, 0, 0);
	blockColours[1] = RGB(0, 0, 255);
	blockColours[2] = RGB(0, 255, 0);
	blockColours[3] = RGB(0, 255, 255);
	blockColours[4] = RGB(255, 0, 0);
	blockColours[5] = RGB(255, 0, 255);
	blockColours[6] = RGB(255, 255, 0);
	blockColours[7] = RGB(255, 255, 255);
	blockColours[8] = RGB(255, 255, 64);
}

GameBoard::GameBoard(int R, int C) : blockOnBoard(NULL),
bRows(R), bColumns(C),
bHeight(35), bWidth(35),
bRemaining(0)
{
	blockColours[0] = RGB(0, 0, 0);
	blockColours[1] = RGB(0, 0, 255);
	blockColours[2] = RGB(0, 255, 0);
	blockColours[3] = RGB(0, 255, 255);
	blockColours[4] = RGB(255, 0, 0);
	blockColours[5] = RGB(255, 0, 255);
	blockColours[6] = RGB(255, 255, 0);
	blockColours[7] = RGB(255, 255, 255);
	blockColours[8] = RGB(255, 255, 200);
}

GameBoard::~GameBoard() {
	DeleteBoard();
}

void GameBoard::SetupBoard(int R = 3, int C = 4) {
	if (blockOnBoard == NULL)
		CreateBoard();
	for (int row = 0; row < R; row++)
		for (int col = 0; col < C; col++)
			blockOnBoard[row][col] = (rand() % 8) + 1;
	bRemaining = R * C;
}

COLORREF GameBoard::GetBoardSpace(int row, int col) {
	if (row < 0 || row >= bRows || col < 0 || col >= bColumns)
		return blockColours[0];
	return blockColours[blockOnBoard[row][col]];
}

void GameBoard::DeleteBoard() {
	if (blockOnBoard != NULL) {
		for (int row = 0; row < bRows; row++) {
			if (blockOnBoard[row] != NULL) {
				delete[] blockOnBoard[row];
				blockOnBoard[row] = NULL;
			}
		}
		delete[] blockOnBoard;
		blockOnBoard = NULL;
	}
}

void GameBoard::CreateBoard() {
	if (blockOnBoard != NULL)
		DeleteBoard();
	blockOnBoard = new int*[bRows];
	for (int row = 0; row < bRows; row++) {
		blockOnBoard[row] = new int[bColumns];
		for (int col = 0; col < bColumns; col++)
			blockOnBoard[row][col] = 0;
	}
}

void GameBoard::DeleteBlocks(COLORREF colour) {
	for (int row = 0; row < bRows; row++) {
		for (int col = 0; col < bColumns; col++) {
			if (blockColours[blockOnBoard[row][col]] == colour) {
				blockOnBoard[row][col] = 0;
			}
		}
	}
}

bool GameBoard::IsGameOver() const {
	for (int col = 0; col < bColumns; col++) {
		for (int row = bRows - 1; row >= 0; row--) {
			int bColour = blockOnBoard[row][col];
			if (bColour == 0)
				break;
			else {
				if (row - 1 >= 0 && blockOnBoard[row - 1][col] == bColour)
					return false;
				else if (col + 1 < bColumns && blockOnBoard[row][col + 1] == bColour)
					return false;
			}
		}
	}

	return true;
}