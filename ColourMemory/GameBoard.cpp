#include "pch.h"
#include "vector"
#include "GameBoard.h"

GameBoard::GameBoard() : blockOnBoard(),
bRows(3), bColumns(4),
bHeight(50), bWidth(50),
bRemaining(0)
{
	blockColours[0] = RGB(255, 255, 255);
	blockColours[1] = RGB(0, 0, 0);
	blockColours[2] = RGB(0, 0, 255);
	blockColours[3] = RGB(0, 255, 0);
	blockColours[4] = RGB(0, 255, 255);
	blockColours[5] = RGB(255, 0, 0);
	blockColours[6] = RGB(255, 0, 255);
	blockColours[7] = RGB(255, 255, 0);
	blockColours[8] = RGB(255, 222, 173);

	SetupBoard(3, 4);
}

GameBoard::GameBoard(int R, int C) : blockOnBoard(),
bRows(R), bColumns(C),
bHeight(50), bWidth(50),
bRemaining(0)
{
	blockColours[0] = RGB(255, 255, 255);
	blockColours[1] = RGB(0, 0, 0);
	blockColours[2] = RGB(0, 0, 255);
	blockColours[3] = RGB(0, 255, 0);
	blockColours[4] = RGB(0, 255, 255);
	blockColours[5] = RGB(255, 0, 0);
	blockColours[6] = RGB(255, 0, 255);
	blockColours[7] = RGB(255, 255, 0);
	blockColours[8] = RGB(255, 222, 173);

	SetupBoard(R, C);
}

GameBoard::~GameBoard() {
	DeleteBoard();
}

void GameBoard::SetupBoard(int R = 3, int C = 4) {
	SetRows(R);
	SetColumns(C);
	blockOnBoard.resize(R, std::vector<int>(C));
	
	if (blockOnBoard.empty())
		CreateBoard();

	std::vector<int> boardColours(R * C / 2 + 1, 0);	// broja� boja, samo dvije iste boje mogu biti na plo�i
	int newColour;
	for (int row = 0; row < R; row++) {
		for (int col = 0; col < C; col++) {
			newColour = rand() % ((R * C) / 2) + 1;

			if (boardColours[newColour] < 2)
				boardColours[newColour]++;
			else {
				while (!(boardColours[newColour] < 2)) {
					newColour = rand() % ((R * C) / 2) + 1;
				}
				boardColours[newColour]++;
			}
			blockOnBoard[row][col] = newColour;
		}
	}
	bRemaining = R * C / 2;
}

COLORREF GameBoard::GetBoardSpace(int row, int col) {
	if (row < 0 || row >= bRows || col < 0 || col >= bColumns)
		return blockColours[0];
	return blockColours[blockOnBoard[row][col]];
}

void GameBoard::DeleteBoard() {
	if (!blockOnBoard.empty()) {
		for (int row = 0; row < bRows; row++) {
			if (!blockOnBoard[row].empty()) {
				blockOnBoard[row].clear();
			}
		}
		blockOnBoard.clear();
	}
}

void GameBoard::CreateBoard() {
	if (!blockOnBoard.empty())
		DeleteBoard();
	for (int row = 0; row < bRows; row++) {
		for (int col = 0; col < bColumns; col++)
			blockOnBoard[row][col] = blockColours[0];
	}
}

void GameBoard::DeleteBlocks(COLORREF colour) {
	for (int row = 0; row < bRows; row++) {
		for (int col = 0; col < bColumns; col++) {
			if (blockColours[blockOnBoard[row][col]] == colour) {
				blockOnBoard[row][col] = blockColours[1];
			}
		}
	}
	if (colour == RGB(255, 255, 255))
		return;
	bRemaining--;
}

bool GameBoard::IsGameOver() const {
	if (bRemaining == 0)
		return true;
	return false;
}

void GameBoard::SetRemainingCount(int remaining) {
	this->bRemaining = remaining;
}