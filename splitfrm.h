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

/////////////////////////////////////////////////////////////////////////////
// CSplitFrame frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "CHistoryView.h"
#include "CSearchFileView.h"

#define VIEWID_DEFAULT AFX_IDW_PANE_FIRST
#define VIEWID_SEARCH AFX_IDW_PANE_FIRST + 10
#define VIEWID_HISTORY AFX_IDW_PANE_FIRST + 20
#define VIEWID_DRAW AFX_IDW_PANE_FIRST + 30

class CSplitFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSplitFrame)

protected:
	CSplitFrame();          // protected constructor used by dynamic creation

// Attributes
protected:
	//CSplitterWndEx    m_wndSplitter;
public:

// Implementation
public:
	virtual ~CSplitFrame();
	//virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	//{{AFX_MSG(CSplitFrame)
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	CView* m_pDrawView;
	CView* m_pWndHistoryView;
	CView* m_pWndSearchFileView;
	
public:
	CString m_strTmpPath;


public:
	//void SetDrawView(CView* pView) {
	//	m_pDrawView = pView;
	//}
	void SetSearchFileView(CView* pView) {
		m_pWndSearchFileView = pView;
	}

	void SwitchView(int nID);
	void OnDrawTest();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

