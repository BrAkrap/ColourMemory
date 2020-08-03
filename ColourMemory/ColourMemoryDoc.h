
// ColourMemoryDoc.h : interface of the CColourMemoryDoc class
//


#pragma once
#include "GameBoard.h"

class CColourMemoryDoc : public CDocument
{
protected: // create from serialization only
	CColourMemoryDoc() noexcept;
	DECLARE_DYNCREATE(CColourMemoryDoc)

// Attributes
public:

// Operations
public:
	COLORREF GetBoardSpace(int row, int col) { return board.GetBoardSpace(row, col); }
	void SetupBoard(int row, int col) { board.SetupBoard(row, col); }
	int GetHeight() { return board.GetHeight(); }
	void SetHeight(int h) { board.SetHeight(h); }
	int GetWidth() { return board.GetWidth(); }
	void SetWidth(int w) { board.SetWidth(w); }
	int GetRows() { return board.GetRows(); }
	void SetRows(int row) { board.SetRows(row); }
	int GetColumns() { return board.GetColumns(); }
	void SetColumns(int col) { board.SetColumns(col); }
	void DeleteBoard() { board.DeleteBoard(); }
	void DeleteBlocks(COLORREF colour) { return board.DeleteBlocks(colour); }
	int GetRemainingCount() { return board.GetRemainingCount(); }
	bool IsGameOver() { return board.IsGameOver(); }
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CColourMemoryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GameBoard board;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
