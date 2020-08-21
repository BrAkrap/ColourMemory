
// ColourMemoryView.cpp : implementation of the CColourMemoryView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ColourMemory.h"
#endif

#include "ColourMemoryDoc.h"
#include "ColourMemoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColourMemoryView

IMPLEMENT_DYNCREATE(CColourMemoryView, CView)

BEGIN_MESSAGE_MAP(CColourMemoryView, CView)
	ON_WM_LBUTTONDOWN()

	ON_COMMAND(ID_LEVEL_EASY, &CColourMemoryView::OnLevelEasy)
	ON_COMMAND(ID_LEVEL_MEDIUM, &CColourMemoryView::OnLevelMedium)
	ON_COMMAND(ID_LEVEL_HARD, &CColourMemoryView::OnLevelHard)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_EASY, &CColourMemoryView::OnUpdateLevelEasy)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_MEDIUM, &CColourMemoryView::OnUpdateLevelMedium)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_HARD, &CColourMemoryView::OnUpdateLevelHard)
END_MESSAGE_MAP()

// CColourMemoryView construction/destruction

CColourMemoryView::CColourMemoryView() noexcept
{
	// TODO: add construction code here

}

CColourMemoryView::~CColourMemoryView()
{
}

BOOL CColourMemoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CColourMemoryView drawing

void CColourMemoryView::OnDraw(CDC* pDC)
{
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	int nDCSave = pDC->SaveDC();
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	pDC->FillSolidRect(&rcClient, clr);
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	for (int row = 0; row < pDoc->GetRows(); row++) {
		for (int col = 0; col < pDoc->GetColumns(); col++) {
			clr = pDoc->GetBoardSpace(row, col);
			CRect rcBlock;

			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

			if (pDoc->GetAction() == true && pDoc->GetCurrentPoint() == CPoint(row, col)) {
				pDC->FillSolidRect(&rcBlock, clr);

				rcBlock.left = pDoc->GetPreviousPoint().y * pDoc->GetWidth();
				rcBlock.top = pDoc->GetPreviousPoint().x * pDoc->GetHeight();
				rcBlock.right = rcBlock.left + pDoc->GetWidth();
				rcBlock.bottom = rcBlock.top + pDoc->GetHeight();

				pDC->FillSolidRect(&rcBlock, pDoc->GetPreviousColour());
			}
			else if (pDoc->GetAction() == true && pDoc->GetBoardSpace(row, col) == RGB(255, 255, 255))
				pDC->FillSolidRect(&rcBlock, RGB(255, 255, 255));
			else
				pDC->FillSolidRect(&rcBlock, RGB(192, 192, 192));
			pDC->Rectangle(&rcBlock);
		}
	}


	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// CColourMemoryView diagnostics

#ifdef _DEBUG
void CColourMemoryView::AssertValid() const
{
	CView::AssertValid();
}

void CColourMemoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CColourMemoryDoc* CColourMemoryView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColourMemoryDoc)));
	return (CColourMemoryDoc*)m_pDocument;
}
#endif //_DEBUG

void CColourMemoryView::OnInitialUpdate() {
	CView::OnInitialUpdate();

	ResizeWindow();
}

void CColourMemoryView::ResizeWindow() {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	if (!pDoc)
		return;

	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	int heightDiff = rcWindow.Height() - rcClient.Height();
	int widthDiff = rcWindow.Width() - rcClient.Width();
	rcWindow.right = rcWindow.left + pDoc->GetWidth() * pDoc->GetColumns() + widthDiff;
	rcWindow.bottom = rcWindow.top + pDoc->GetHeight() * pDoc->GetRows() + heightDiff;

	GetParentFrame()->MoveWindow(&rcWindow);
}

void CColourMemoryView::OnLButtonDown(UINT nFlags, CPoint point) {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
		return;

	pDoc->SetAction(true);

	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();

	if ((row == pDoc->GetPreviousPoint().y / pDoc->GetHeight() && col == pDoc->GetPreviousPoint().x / pDoc->GetWidth()) && pDoc->GetSecondChoice() == true) {
		return;
	}
	else {
		pDoc->SetCurrentPoint(CPoint(row, col));
		pDoc->SetCurrentColour(pDoc->GetBoardSpace(row, col));
	}

	if (pDoc->GetSecondChoice() == false) {
		pDoc->SetPreviousPoint(point);
		pDoc->SetPreviousColour(pDoc->GetCurrentColour());
		pDoc->SetSecondChoice(true);
		Invalidate();
	}
	else {
		if (pDoc->GetBoardSpace(row, col) == pDoc->GetPreviousColour() && (row != (pDoc->GetPreviousPoint().y / pDoc->GetHeight()) || col != (pDoc->GetPreviousPoint().x / pDoc->GetWidth()))) {
			pDoc->DeleteBlocks(pDoc->GetCurrentColour());
			UpdateWindow();
			Invalidate();
			if (pDoc->IsGameOver()) {
				CString message;
				message.Format(_T("Congratulations!"));
				MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
				pDoc->SetAction(false);
				pDoc->SetupBoard(pDoc->GetRows(), pDoc->GetColumns());
			}
		}
		pDoc->SetSecondChoice(false);
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}

void CColourMemoryView::OnLevelEasy() {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetRemainingCount(3);
	pDoc->SetupBoard(2, 3);
	ResizeWindow();
	Invalidate();
	UpdateWindow();
}

void CColourMemoryView::OnLevelMedium() {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetRemainingCount(6);
	pDoc->SetupBoard(3, 4);
	ResizeWindow();
	Invalidate();
	UpdateWindow();
}

void CColourMemoryView::OnLevelHard() {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetRemainingCount(8);
	pDoc->SetupBoard(4, 4);
	ResizeWindow();
	Invalidate();
	UpdateWindow();
}

void CColourMemoryView::OnUpdateLevelEasy(CCmdUI *pCmdUI) {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->SetCheck(pDoc->GetRows() == 2 && pDoc->GetColumns() == 3);
}

void CColourMemoryView::OnUpdateLevelMedium(CCmdUI *pCmdUI) {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->SetCheck(pDoc->GetRows() == 3 && pDoc->GetColumns() == 4);
}

void CColourMemoryView::OnUpdateLevelHard(CCmdUI *pCmdUI) {
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pCmdUI->SetCheck(pDoc->GetRows() == 4 && pDoc->GetColumns() == 4);	
}
// CColourMemoryView message handlers
