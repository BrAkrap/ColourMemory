#include "pch.h"
#include "vector"
#include "GameBoard.h"

GameBoard::GameBoard() : blockOnBoard(),
bRows(3), bColumns(4),
bHeight(35), bWidth(35),
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

	blockOnBoard.resize(3, std::vector<int>(4));
	SetupBoard(3, 4);
}

GameBoard::GameBoard(int R, int C) : blockOnBoard(),
bRows(R), bColumns(C),
bHeight(35), bWidth(35),
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

	blockOnBoard.resize(R, std::vector<int>(C));
	SetupBoard(R, C);
}

GameBoard::~GameBoard() {
	DeleteBoard();
}

void GameBoard::SetupBoard(int R = 3, int C = 4) {
	SetRows(R);
	SetColumns(C);
	
	if (blockOnBoard.empty())
		CreateBoard();

	std::vector<int> boardColours(R * C / 2 + 1, 0);	// brojaè boja, samo dvije iste boje mogu biti na ploèi
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
	bRemaining--;
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