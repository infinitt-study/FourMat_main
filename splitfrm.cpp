// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "FourMat.h"
#include "splitfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame

IMPLEMENT_DYNCREATE(CSplitFrame, CMDIChildWndEx)

CSplitFrame::CSplitFrame()
{
	m_pWndSearchFileView = new CSearchFileView();
	m_pWndHistoryView = new CHistoryView();
}

CSplitFrame::~CSplitFrame()
{
	delete m_pWndSearchFileView;
	delete m_pWndHistoryView;
}

//BOOL CSplitFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
//{
//	return m_wndSplitter.Create(this, 2, 2, CSize(10, 10), pContext);
//}

BEGIN_MESSAGE_MAP(CSplitFrame, CMDIChildWndEx)
	//{{AFX_MSG_MAP(CSplitFrame)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	//}}AFX_MSG_MAP


	ON_COMMAND(ID_DRAW_TEST, OnDrawTest)
END_MESSAGE_MAP()

void CSplitFrame::OnFilePrint ()
{
	if (m_dockManager.IsPrintPreviewValid ())
	{
		PostMessage (WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CSplitFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid ())
	{
		PostMessage (WM_COMMAND, AFX_ID_PREVIEW_CLOSE);      // Force Print Preview Close
	}
}

void CSplitFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_dockManager.IsPrintPreviewValid ());
}

void CSplitFrame::SwitchView(int nID)
{
	CView* pOldView = GetActiveFrame()->GetActiveView();
	CView* pNewView = NULL;

	switch (nID)
	{
	case VIEWID_SEARCH:
		pNewView = (CView*)m_pWndSearchFileView;
		break;

	case VIEWID_HISTORY:
		pNewView = (CView*)m_pWndHistoryView;
		break;

	}

	if (pNewView)
	{
		if (pOldView == pNewView)			return;

		pOldView->ShowWindow(SW_HIDE);
		pOldView->SetDlgCtrlID(nID);

		pNewView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
		pNewView->ShowWindow(SW_SHOW);
		GetActiveFrame()->SetActiveView(pNewView);
		GetActiveFrame()->RecalcLayout();
	}
}

void CSplitFrame::OnDrawTest()
{
	SwitchView(VIEWID_SEARCH);
}


BOOL CSplitFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pWndSearchFileView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_SEARCH, pContext);
	m_pWndHistoryView->Create(NULL, NULL, WS_CHILD, CFrameWnd::rectDefault, this, VIEWID_HISTORY, pContext);

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}
