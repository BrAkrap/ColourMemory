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
	void SetHeight(int h) { bHeight = h; }
	int GetWidth() const { return bWidth; }
	void SetWidth(int w) { bWidth = w; }
	int GetRows() const { return bRows; }
	void SetRows(int row) { bRows = (row >= 2 && row <= 4) ? row : 3; }
	int GetColumns() const { return bColumns; }
	void SetColumns(int col) { bColumns = (col >= 3 && col <= 4) ? col : 4; }
	COLORREF GetPreviousColour() { return previousColour; }
	void SetPreviousColour(COLORREF colour) { previousColour = colour; }
	CPoint GetPreviousPoint() { return previousPoint; }
	void SetPreviousPoint(CPoint point) { previousPoint = point; }
	CPoint GetCurrentPoint() { return currentPoint; }
	void SetCurrentPoint(CPoint point) { currentPoint = point; }
	bool GetSecondChoice() { return secondChoice; }
	void SetSecondChoice(bool choice) { secondChoice = choice; }
	bool GetAction() { return action; }
	void SetAction(bool action) { this->action = action; }
	void DeleteBoard();
	void DeleteBlocks(COLORREF colour);
	void SetRemainingCount(int remaining);
	int GetRemainingCount() const { return bRemaining; }
	bool IsGameOver() const;

private:
	void CreateBoard();
	std::vector<std::vector<int>> blockOnBoard;
	COLORREF blockColours[9];
	COLORREF previousColour;
	CPoint previousPoint;
	bool secondChoice = false;
	bool action = false;
	CPoint currentPoint;
	int bRows;
	int bColumns;
	int bHeight;
	int bWidth;
	int bRemaining;
};

