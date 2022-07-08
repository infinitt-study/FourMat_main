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

#include "drawobj.h"
#include "summinfo.h"

class CDrawView;

class CDrawDoc : public COleDocument
{
protected: // create from serialization only
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// Attributes
public:
	void SetCurrentFrameNo(BOOL bLeftView, int nDelta) {
		if (bLeftView) {
			m_nCurrentFrameNo -= nDelta;
			m_nCurrentFrameNo = m_nCurrentFrameNo % m_listData.size();
			m_pObjects = m_pageLeftObjects[m_nCurrentFrameNo];
		}
		else {
			m_nCurrentRightFrameNo -= nDelta;
			m_nCurrentRightFrameNo = m_nCurrentRightFrameNo % m_listData.size();
			m_pRightObjects = m_pageRightObjects[m_nCurrentRightFrameNo];
		}
	}

	//수정 -> 연결된거 다 수정
	CDrawObjList* GetObjects(BOOL bLeftView)
	{ 
		return bLeftView ? m_pObjects : m_pRightObjects;
	}



	const CSize& GetSize() const { return m_size; }
	void ComputePageSize();
	int GetMapMode() const { return m_nMapMode; }
	COLORREF GetPaperColor() const { return m_paperColor; }
	CSummInfo *m_pSummInfo;

	
	BOOL m_bPen;
	LOGPEN m_logpen;
	BOOL m_bBrush;
	LOGBRUSH m_logbrush;

	float m_zoom;
	//BOOL CanDeactivateInplace() const
	//{
	//	return m_bCanDeactivateInplace;
	//}

// Operations
public:
	CDrawObj* ObjectAt(const CPoint& point);
	void Draw(CDC* pDC, CDrawView* pView);
	// ------ Draw called for live icon and Win7 taskbar thumbnails
	void Draw (CDC* pDC);
	void FixUpObjectPositions();
	CRect m_rectDocumentBounds;
	// ------

	void Add(CDrawObj* pObj);
	void Remove(CDrawObj* pObj);

	void SetPreviewColor(COLORREF clr);

#ifdef SHARED_HANDLERS
	// Search support
	virtual void InitializeSearchContent();

	// Set properties for search
	void SetTitle(const CString& value);
	void SetAuthor(const CString& value);
	void SetCompany(const CString& value);
	void SetComment(const CString& value);
	void SetCopyright(const CString& value);
	void SetKeywords(const CString& value);
	void SetLastAuthor(const CString& value);
	void SetSearchContents(const CString& value);
#endif

// Implementation
public:
	virtual ~CDrawDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
//	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual void OnUnloadHandler();

//	BOOL m_bCanDeactivateInplace;

public:
	std::vector<CDrawObjList*> m_pageLeftObjects;
	std::vector<CDrawObjList*> m_pageRightObjects;

	CDrawObjList* m_pObjects;
	CDrawObjList* m_pRightObjects;


	CSize m_size;
	int m_nMapMode;
	COLORREF m_paperColor;
	COLORREF m_paperColorLast;

public:
	CString m_strFolderPath;

	CString m_strFilePath;
	CString m_strRightFilePath;

	void LoadDicom(BOOL bLeftView);
	//DicomImage* m_pImage; // 따로 지우기
	BITMAPINFO m_bmiLeft;
	BITMAPINFO m_bmiRight;
	BITMAPINFO& GetBmi(BOOL bLeftView)
	{
		return bLeftView ? m_bmiLeft : m_bmiRight;
	}

	void* GetDib(BOOL bLeftView)
	{
		return bLeftView ? m_listData[m_nCurrentFrameNo] : m_listRightData[m_nCurrentRightFrameNo];
	}


	//std::vector<BITMAPINFO> m_listBitmap;
	std::vector<void*> m_listData;
	std::vector<void*> m_listRightData;

	long m_nCurrentFrameNo; // 다이콤 내부 이미지 현재페이지
	long m_nCurrentRightFrameNo;

	long m_nTotalFrameNo; // 다이콤 내부 이미지 전체페이지
	long m_nTotalRightFrameNo;

protected:
	//{{AFX_MSG(CDrawDoc)
	afx_msg void OnViewPaperColor();
	afx_msg void OnFileSummaryInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAffinetranformMirror();
	afx_msg void OnAffinetranformRotation();
	afx_msg void OnAffinetranformScaling();
	afx_msg void OnAffinetranformSlice();
	afx_msg void OnAffinetranformTranslation();
	afx_msg void OnAffinetransformFlip();
	afx_msg void OnFeatureextractionAddnoise();
	afx_msg void OnFeatureextractionBlur();
	afx_msg void OnFeatureextractionReducenoise();
	afx_msg void OnFeatureextractionSharpening();
	afx_msg void OnFilteringBrightness();
	//afx_msg void OnFilteringContrast();
	afx_msg void OnFilteringRemovenoise();
	afx_msg void OnFilteringTograyscale();
	afx_msg void OnFilteringHistogram();
	afx_msg void OnFilteringWindowlevel();
	afx_msg void OnFilteringInverse();
	void HelperLoadDicom(BOOL bLeftView);
};
