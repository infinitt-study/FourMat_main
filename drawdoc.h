#include "drawobj.h"
#include "summinfo.h"

#include "AccessPixel.h"
#include "RGBBYTE.h"
#include "CFourMatDIB.h"

#include "AccessObject.h"

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
			m_leftDrawObj.SetCurrentFrameNo(nDelta);
		}
		else {
			m_rightDrawObj.SetCurrentFrameNo(nDelta);
		}
	}

	CDrawObjList* GetObjects(BOOL bLeftView)
	{ 
		return bLeftView ? m_leftDrawObj.m_pObjects : m_rightDrawObj.m_pObjects;
	}


	const CSize& GetSize() const { return m_size; }
	void ComputePageSize();
	int GetMapMode() const { return m_nMapMode; }
	COLORREF GetPaperColor() const { return m_paperColor; }
	CSummInfo* m_pSummInfo;

	
	BOOL m_bPen;
	LOGPEN m_logpen;
	BOOL m_bBrush;
	LOGBRUSH m_logbrush;
	/*LOWORD m_xPosition;
	HIWORD m_yPosition;*/


	float m_zoom;
	//BOOL CanDeactivateInplace() const
	//{
	//	return m_bCanDeactivateInplace;
	//}

// Operations
public:
	CDrawObj* ObjectAt(BOOL bLeftView, const CPoint& point);
	void Draw(BOOL bLeftView, CDC* pDC, CDrawView* pView);
	// ------ Draw called for live icon and Win7 taskbar thumbnails
	void Draw(BOOL bLeftView, CDC* pDC);
	void DIBDraw(BOOL bLeftView, CDC* pDC);
	void DIBDraw(BOOL bLeftView, CDC* pDC, int x, int y, int w, int h);
	CRect m_rectDocumentBounds;
	// ------

	void Add(BOOL bLeftView, CDrawObj* pObj);
	void Remove(BOOL bLeftView, CDrawObj* pObj);

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
	// 클래스 분활
	CAccessObject m_leftDrawObj;
	CAccessObject m_rightDrawObj;

	CSize m_size;
	int m_nMapMode;
	COLORREF m_paperColor;
	COLORREF m_paperColorLast;
  
	CImage m_bmp;
	LONG    m_nWidth;      // 비트맵 가로 크기 (픽셀 단위)
	LONG    m_nHeight;     // 비트맵 세로 크기 (픽셀 단위)
	WORD    m_nBitCount;   // 픽셀 당 비트 수
	DWORD   m_nDibSize;    // DIB 전체 크기 (BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터)
	BYTE* m_pDib;        // DIB 시작 주소 (BITMAPINFOHEADER 시작 주소)
	int m_nPitch;
	BYTE* lpvBits;
	BOOL m_bFirstLoad;
	BOOL m_bClickedView;
  
	// 추가된 변수 및 메소드
	CString m_strFolderPath;

	void LoadDicom(BOOL bLeftView);
	void SaveDraw(CString strFileName, std::vector<CDrawObjList*>& pageObjects);
	void LoadDraw(CString strFileName, std::vector<CDrawObjList*>& pageObjects);

	bool m_bIsChange; // 변경사항 있있으면 true


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
	afx_msg void OnAffinetranformTranslation();
	afx_msg void OnAffinetransformFlip();
	afx_msg void OnFeatureextractionAddnoise();
	afx_msg void OnFeatureextractionBlur();
	afx_msg void OnFeatureextractionReducenoise();
	afx_msg void OnFeatureextractionSharpening();
	afx_msg void OnFilteringBrightness();
	afx_msg void OnFilteringHistogram();
	afx_msg void OnFilteringWindowlevel();
	afx_msg void OnFilteringInverse();

	void HelperLoadDicom(BOOL bLeftView);

	afx_msg void OnFeatureextractionHistogramequalization();
	afx_msg void OnFeatureextractionHistogramstretching();
	afx_msg void OnMolphologyClosing();
	afx_msg void OnMolphologyDilation();
	afx_msg void OnMolphologyErosion();
	afx_msg void OnMolphologyOpening();
	afx_msg void OnObjectSavedraw();
	afx_msg void OnFilteringGamma();

	CFourMatDIB& SelectFourMatDIB(BOOL bClickedView);
	void EnableDrawView(CCmdUI* pCmdUI);

	afx_msg void OnUpdateAffinetranformRotation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAffinetranformMirror(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAffinetranformScaling(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAffinetranformTranslation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAffinetransformFlip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeatureextractionAddnoise(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeatureextractionBlur(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeatureextractionHistogramequalization(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeatureextractionHistogramstretching(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeatureextractionReducenoise(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFeatureextractionSharpening(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilteringBrightness(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilteringGamma(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilteringHistogram(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilteringInverse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilteringWindowlevel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMolphologyErosion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMolphologyDilation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMolphologyOpening(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMolphologyClosing(CCmdUI* pCmdUI);
	afx_msg void OnFeatureextractionCannyedge();
	afx_msg void OnFeatureextractionHarriscorner();
	afx_msg void OnCompareCompare(); // 비교 dlg
};
