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

// Hints for UpdateAllViews/OnUpdate
#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_DRAWOBJ     1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3
#define HINT_UPDATE_FOLDERPATH	4
#define HINT_UPDATE_FILEPATH	5

class CDrawObj;

class CDrawView : public CScrollView
{
	friend class CDrawObjFriend;

public:
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)

// Attributes
public:
	CDrawDoc* GetDocument()
	{ return(CDrawDoc*)m_pDocument; }
	void SetPageSize(CSize size);
	CRect GetInitialPosition();

// Operations
public:
	void DocToClient(CRect& rect);
	void DocToClient(CPoint& point);
	void ClientToDoc(CPoint& point);
	void ClientToDoc(CRect& rect);
	void Select(CDrawObj* pObj, BOOL bAdd = FALSE);
	void SelectWithinRect(CRect rect, BOOL bAdd = FALSE);
	void Deselect(CDrawObj* pObj);
	void CloneSelection();
	void UpdateActiveItem();
	void InvalObj(CDrawObj* pObj);
	void Remove(CDrawObj* pObj);
	void PasteNative(COleDataObject& dataObject);
	void PasteEmbedded(COleDataObject& dataObject, CPoint point );

	void PreviewFillColor(COLORREF color);
	void PreviewLineColor(COLORREF color);
	void PreviewLineWeight(int nWeight);

	void PreviewStyle(COLORREF clrFill, COLORREF clrLine);

	void StorePreviewState();
	void RestorePreviewState(BOOL bReset = TRUE);
	void ResetPreviewState();

// Implementation
protected:
	// added for drop-target functionality
	COleDropTarget m_dropTarget;        // for drop target functionality
	CPoint m_dragPoint;                 // current position
	CSize m_dragSize;                   // size of dragged object
	CSize m_dragOffset;                 // offset between pt and drag object corner
	DROPEFFECT m_prevDropEffect;
	BOOL m_bDragDataAcceptable;

	BOOL GetObjectInfo(COleDataObject* pDataObject, CSize* pSize, CSize* pOffset);
	// end of drop-target additions

	struct XPreviewStateItem
	{
		BOOL m_bPen;
		LOGPEN m_logpen;
		BOOL m_bBrush;
		LOGBRUSH m_logbrush;

		XPreviewStateItem(const CDrawObj& rObj)
		{
			Store(rObj);
		}

		void Store(const CDrawObj& rObj);
		void Restore(CDrawObj& rObj) const;
	};
	typedef CArray<XPreviewStateItem*, XPreviewStateItem*> XPreviewState;

	XPreviewState m_PreviewState;

public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);  // overriden to record time/date
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnActivateView(BOOL bActivate, CView* pActiveView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void DrawGrid(CDC* pDC);

	// added for drop-target functionality
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD grfKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD grfKeyState, CPoint point);
	virtual void OnDragLeave();
	static CLIPFORMAT m_cfObjectDescriptor;
	// end of drop-target additions

	static CLIPFORMAT m_cfDraw; // custom clipboard format

	CDrawObjList m_selection;
	BOOL m_bGrid;
	COLORREF m_gridColor;
	BOOL m_bActive; // is the view active?

protected:
	virtual void OnInitialUpdate(); // called first time after construct

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// OLE Container support
public:
	virtual BOOL IsSelected(const CObject* pDocItem) const;

protected:
	//{{AFX_MSG(CDrawView)
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEdit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDrawSelect();
	afx_msg void OnDrawRoundRect();
	//afx_msg void OnDrawTest();

	afx_msg void OnDrawRect();
	afx_msg void OnDrawLine();
	afx_msg void OnDrawEllipse();
	afx_msg void OnUpdateDrawEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRoundRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSingleSelect(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditClear();
	afx_msg void OnUpdateAnySelect(CCmdUI* pCmdUI);
	afx_msg void OnDrawPolygon();
	afx_msg void OnUpdateDrawPolygon(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnObjectFillColor();
	afx_msg void OnUpdateObjectFillColor(CCmdUI* pCmdUI);
	afx_msg void OnObjectNoFill();
	afx_msg void OnUpdateObjectNoFill(CCmdUI* pCmdUI);
	afx_msg void OnObjectLineColor();
	afx_msg void OnUpdateObjectLineColor(CCmdUI* pCmdUI);
	afx_msg void OnObjectNoLine();
	afx_msg void OnUpdateObjectNoLine(CCmdUI* pCmdUI);
	afx_msg void OnObjectLineWeight(UINT nID);
	afx_msg void OnUpdateObjectLineWeight(CCmdUI* pCmdUI);
	afx_msg void OnObjectProperties();
	afx_msg void OnUpdateObjectProperties(CCmdUI* pCmdUI);
	afx_msg void OnObjectStyles();
	afx_msg void OnUpdateObjectStyles(CCmdUI* pCmdUI);
	afx_msg void OnObjectMoveBack();
	afx_msg void OnObjectMoveForward();
	afx_msg void OnObjectMoveToBack();
	afx_msg void OnObjectMoveToFront();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateSelection(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	COLORREF GetColorFromColorButton(int nButtonID);

public:
	CString m_strPath;
	afx_msg void OnFilteringBrightness();
	afx_msg void OnFilteringContrast();
	afx_msg void OnFilteringHistogram();
	afx_msg void OnFilteringRemovenoise();
	afx_msg void OnFilteringTograyscale();
	afx_msg void OnAffinetransformRotation();
	afx_msg void OnAffinetransformScaling();
	afx_msg void OnAffinetransformSlice();
	afx_msg void OnAffinetransformMirror();
	afx_msg void OnAffinetransformTranslation();
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnAffinetransformFlip();
};

class CLeftDrawView : public CDrawView
{

};

class CRightDrawView : public CDrawView
{

};