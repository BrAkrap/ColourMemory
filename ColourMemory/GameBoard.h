#pragma once

#include "vector"


class GameBoard
{
public:
	GameBoard();
	GameBoard(int row, int col);
	~GameBoard();

	void SetupBoard(int row, int col);
	COLORREF GetBoardSpace(int row, int col);
	int GetHeight() const { return bHeight; }
	int GetWidth() const { return bWidth; }
	int GetRows() const { return bRows; }
	int GetColumns() const { return bColumns; }
	void DeleteBoard();
	void DeleteBlocks(COLORREF colour);
	int GetRemainingCount() const { return bRemaining; }
	bool IsGameOver() const;

private:
	void CreateBoard();
	std::vector<std::vector<int>> blockOnBoard;
	COLORREF blockColours[9];
	int bRows;
	int bColumns;
	int bHeight;
	int bWidth;
	int bRemaining;
};

