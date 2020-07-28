
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

void CColourMemoryView::OnDraw(CDC* /*pDC*/)
{
	CColourMemoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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


// CColourMemoryView message handlers
