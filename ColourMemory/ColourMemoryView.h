
// ColourMemoryView.h : interface of the CColourMemoryView class
//

#pragma once


class CColourMemoryView : public CView
{
protected: // create from serialization only
	CColourMemoryView() noexcept;
	DECLARE_DYNCREATE(CColourMemoryView)

// Attributes
public:
	CColourMemoryDoc* GetDocument() const;
	COLORREF C;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	void ResizeWindow();
	virtual ~CColourMemoryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLevelEasy();
	afx_msg void OnLevelMedium();
	afx_msg void OnLevelHard();
	afx_msg void OnUpdateLevelEasy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevelMedium(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevelHard(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in ColourMemoryView.cpp
inline CColourMemoryDoc* CColourMemoryView::GetDocument() const
   { return reinterpret_cast<CColourMemoryDoc*>(m_pDocument); }
#endif

