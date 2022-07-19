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

#ifndef SHARED_HANDLERS
#include "FourMat.h"
#include "mainfrm.h"
#endif

#include "drawdoc.h"

#ifndef SHARED_HANDLERS
#include "drawvw.h"
#endif

#include "drawobj.h"
//#include "cntritem.h"

#ifndef SHARED_HANDLERS
#include "summpage.h"
#include "statpage.h"
#endif

#include "propkey.h"
#include "splitfrm.h"
#include "CConvertDataType.h"
#include "CAffineTransform.h"
#include "CFilter.h"
#include "CImprovement.h"
#include "CMorphology.h"
//#include "CConvert.h"
#include "CRotationDlg.h"
#include "CScalingDlg.h"
#include "CTranslationDlg.h"
#include "CAddNoiseDlg.h"
#include "CBlurDlg.h"
#include "CReduceNoiseDlg.h"
#include "CBrightnessDlg.h"
#include "CHistogramDlg.h"
#include "CWindowLevelDlg.h"
#include"CGammaDlg.h"

#include <math.h>

const double PI = 3.14159265358979323846;

//#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img) \
//	ByteImage img; \ 
//	DibToImage(m_Dib, img);
//
//#define CONVERT_IMAGE_TO_DIB(img, dib) \
//	Dib dib; \
//	ImageToDib(img, dib);

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, COleDocument)

BEGIN_MESSAGE_MAP(CDrawDoc, COleDocument)
	//{{AFX_MSG_MAP(CDrawDoc)
#ifndef SHARED_HANDLERS
	ON_COMMAND(ID_VIEW_PAPERCOLOR, OnViewPaperColor)
	ON_COMMAND(ID_FILE_SUMMARYINFO, OnFileSummaryInfo)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	//	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	//	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, COleDocument::OnUpdateObjectVerbMenu)
	// MAPI support
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
#endif
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_AFFINETRANFORM_MIRROR, &CDrawDoc::OnAffinetranformMirror)
	ON_COMMAND(ID_AFFINETRANFORM_ROTATION, &CDrawDoc::OnAffinetranformRotation)
	ON_COMMAND(ID_AFFINETRANFORM_SCALING, &CDrawDoc::OnAffinetranformScaling)
	ON_COMMAND(ID_AFFINETRANFORM_TRANSLATION, &CDrawDoc::OnAffinetranformTranslation)
	ON_COMMAND(ID_AFFINETRANSFORM_FLIP, &CDrawDoc::OnAffinetransformFlip)
	ON_COMMAND(ID_FEATUREEXTRACTION_ADDNOISE, &CDrawDoc::OnFeatureextractionAddnoise)
	ON_COMMAND(ID_FEATUREEXTRACTION_BLUR, &CDrawDoc::OnFeatureextractionBlur)
	ON_COMMAND(ID_FEATUREEXTRACTION_REDUCENOISE, &CDrawDoc::OnFeatureextractionReducenoise)
	ON_COMMAND(ID_FEATUREEXTRACTION_SHARPENING, &CDrawDoc::OnFeatureextractionSharpening)
	ON_COMMAND(ID_FILTERING_BRIGHTNESS, &CDrawDoc::OnFilteringBrightness)
	ON_COMMAND(ID_FILTERING_INVERSE, &CDrawDoc::OnFilteringInverse)
	//	ON_COMMAND(ID_FILTERING_TOGRAYSCALE, &CDrawDoc::OnFilteringTograyscale)

	ON_COMMAND(ID_FILTERING_HISTOGRAM, &CDrawDoc::OnFilteringHistogram)
	ON_COMMAND(ID_FILTERING_WINDOWLEVEL, &CDrawDoc::OnFilteringWindowlevel)
	ON_COMMAND(ID_FILTERING_INVERSE, &CDrawDoc::OnFilteringInverse)
	ON_COMMAND(ID_FEATUREEXTRACTION_HISTOGRAMEQUALIZATION, &CDrawDoc::OnFeatureextractionHistogramequalization)
	ON_COMMAND(ID_FEATUREEXTRACTION_HISTOGRAMSTRETCHING, &CDrawDoc::OnFeatureextractionHistogramstretching)
	ON_COMMAND(ID_MOLPHOLOGY_CLOSING, &CDrawDoc::OnMolphologyClosing)
	ON_COMMAND(ID_MOLPHOLOGY_DILATION, &CDrawDoc::OnMolphologyDilation)
	ON_COMMAND(ID_MOLPHOLOGY_EROSION, &CDrawDoc::OnMolphologyErosion)
	ON_COMMAND(ID_MOLPHOLOGY_OPENING, &CDrawDoc::OnMolphologyOpening)
	ON_COMMAND(ID_OBJECT_SAVEDRAW, &CDrawDoc::OnObjectSavedraw)
	ON_COMMAND(ID_FILTERING_GAMMA, &CDrawDoc::OnFilteringGamma)
	ON_COMMAND(ID_FEATUREEXTRACTION_CANNYEDGE, &CDrawDoc::OnFeatureextractionCannyedge)
	ON_COMMAND(ID_FEATUREEXTRACTION_HARRISCORNER, &CDrawDoc::OnFeatureextractionHarriscorner)
	ON_COMMAND(ID_COMPARE_COMPARE, &CDrawDoc::OnCompareCompare)

	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_ROTATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_MIRROR, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_SCALING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANFORM_TRANSLATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_AFFINETRANSFORM_FLIP, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_ADDNOISE, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_BLUR, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_HISTOGRAMEQUALIZATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_HISTOGRAMSTRETCHING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_REDUCENOISE, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FEATUREEXTRACTION_SHARPENING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_BRIGHTNESS, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_GAMMA, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_HISTOGRAM, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_INVERSE, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_FILTERING_WINDOWLEVEL, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_EROSION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_DILATION, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_OPENING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_MOLPHOLOGY_CLOSING, &CDrawDoc::OnUpdateActiveRibbon)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_SAVEDRAW, &CDrawDoc::OnUpdateActiveRibbon)

	ON_UPDATE_COMMAND_UI(ID_COMPARE_COMPARE, &CDrawDoc::OnUpdateCompareCompare)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc construction/destruction

CDrawDoc::CDrawDoc()
{
	EnableCompoundFile();

	//	m_bCanDeactivateInplace = TRUE;
	m_nMapMode = MM_ANISOTROPIC;
	m_paperColorLast = m_paperColor = RGB(255, 255, 255);
	m_pSummInfo = NULL;
	ComputePageSize();

	m_strFolderPath.Empty();

	m_strFilePath.Empty();
	m_strRightFilePath.Empty();

	m_strFileName.Empty();
	m_strRightFileName.Empty();
}

CDrawDoc::~CDrawDoc()
{
	OnUnloadHandler();
}

void CDrawDoc::OnUnloadHandler()
{
	for (auto& pObjects : m_pageLeftObjects) {
		POSITION pos = pObjects->GetHeadPosition();
		while (pos != NULL)
			delete pObjects->GetNext(pos);
		pObjects->RemoveAll();
		delete pObjects;
	}
	m_pageLeftObjects.clear();

	for (auto& pObjects : m_pageRightObjects) {
		POSITION pos = pObjects->GetHeadPosition();
		while (pos != NULL)
			delete pObjects->GetNext(pos);
		pObjects->RemoveAll();
		delete pObjects;
	}
	m_pageRightObjects.clear();

	delete m_pSummInfo;
	m_pSummInfo = NULL;

}

BOOL CDrawDoc::OnNewDocument() //doc 변수 초기화  
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// reinitialization code
	//(SDI documents will reuse this document)
	if (m_pSummInfo != NULL)
		delete m_pSummInfo;
	m_pSummInfo = new CSummInfo;
	// Title, Subject, Author, Keywords default to empty string
	// Comments, Template, SavedBy default to empty string
	// LastSave, LastPrint, EditTime, RevNum default to 0
	m_pSummInfo->StartEditTimeCount();
	m_pSummInfo->RecordCreateDate();
	m_pSummInfo->SetNumPages(1);
	// NumWords, NumChars default to 0
	m_pSummInfo->SetAppname(_T("FourMat")); // 속성 변경해보기
	// Security defaults to 0

	m_bPen = TRUE;
	m_logpen.lopnStyle = PS_INSIDEFRAME;
	m_logpen.lopnWidth.x = 1;
	m_logpen.lopnWidth.y = 1;
	m_logpen.lopnColor = RGB(0, 0, 0);

	m_bBrush = TRUE;
	m_logbrush.lbStyle = BS_SOLID;
	m_logbrush.lbColor = RGB(192, 192, 192);
	m_logbrush.lbHatch = HS_HORIZONTAL;

	m_nCurrentFrameNo = 0;
	m_nCurrentRightFrameNo = 0;

	m_pObjects = nullptr;

	m_strFolderPath.Empty();
	m_strFilePath.Empty();
  
	m_zoom = 1.0f;

	m_bFirstLoad = true;
	m_bIsChange = false;

	return TRUE;
}

BOOL CDrawDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (m_pSummInfo != NULL)
		delete m_pSummInfo;
	m_pSummInfo = new CSummInfo;
	m_pSummInfo->StartEditTimeCount();
	m_zoom = 1;
	m_nCurrentFrameNo = 0;
	m_nCurrentRightFrameNo = 0;

	m_pObjects = nullptr;

	return COleDocument::OnOpenDocument(lpszPathName);
}

BOOL CDrawDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	m_pSummInfo->RecordSaveDate();
	m_pSummInfo->IncrRevNum();
	m_pSummInfo->SetLastAuthor(m_pSummInfo->GetAuthor());
	m_pSummInfo->AddCountToEditTime();
	m_pSummInfo->StartEditTimeCount();
	return COleDocument::OnSaveDocument(lpszPathName);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc serialization

void CDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_paperColor;
		//m_objects.Serialize(ar);
		m_pSummInfo->WriteToStorage(m_lpRootStg);
	}
	else
	{
		ar >> m_paperColor;
		m_paperColorLast = m_paperColor;
		//m_objects.Serialize(ar);
		m_pSummInfo->ReadFromStorage(m_lpRootStg);
	}

	// By calling the base class COleDocument, we enable serialization
	//  of the container document's COleClientItem objects automatically.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc implementation

void CDrawDoc::Draw(BOOL bLeftView, CDC* pDC, CDrawView* pView)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return;

	POSITION pos = pObjects->GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = pObjects->GetNext(pos);
		pObj->Draw(pDC);
#ifndef SHARED_HANDLERS
		if (pView != NULL && pView->m_bActive && !pDC->IsPrinting() && pView->IsSelected(pObj))
			pObj->DrawTracker(pDC, CDrawObj::selected);
#endif
	}
}

void CDrawDoc::DIBDraw(BOOL bLeftView, CDC* pDC)
{
	//CFourMatDIB& dib = GetFourMatDIB(bClickedView);
	CFourMatDIB& dib = bLeftView ? m_listLeftDIB[m_nCurrentFrameNo] : m_listRightDIB[m_nCurrentRightFrameNo];
	dib.Draw(pDC->m_hDC, -m_size.cx / 2, m_size.cy / 2 - dib.GetHeight(), dib.GetWidth(), dib.GetHeight(), SRCCOPY);
}

void CDrawDoc::DIBDraw(BOOL bClickedView, CDC* pDC, int x, int y)
{
	CFourMatDIB& dib = GetFourMatDIB(bClickedView);
	dib.Draw(pDC->m_hDC, -m_size.cx / 2, m_size.cy / 2 - dib.GetHeight(), dib.GetWidth(), dib.GetHeight(), SRCCOPY); // dlg -> paint dc  
}
void CDrawDoc::DIBDraw(BOOL bClickedView, CDC* pDC, int x, int y, int w, int h)
{
	CFourMatDIB& dib = GetFourMatDIB(bClickedView);
	dib.Draw(pDC->m_hDC, x, y, w, h, 0, 0, dib.GetWidth(), dib.GetHeight(), SRCCOPY); // dlg -> paint dc  

}
void CDrawDoc::Add(BOOL bLeftView, CDrawObj* pObj)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return;

	pObjects->AddTail(pObj);
	pObj->m_pDocument = this;
	SetModifiedFlag(false);
	m_bIsChange = true;
}

void CDrawDoc::Remove(BOOL bLeftView, CDrawObj* pObj)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return;

	// Find and remove from document
	POSITION pos = pObjects->Find(pObj);
	if (pos != NULL)
		pObjects->RemoveAt(pos);
	// set document modified flag
	SetModifiedFlag(false);
	m_bIsChange = true;

#ifndef SHARED_HANDLERS
	// call remove for each view so that the view can remove from m_selection
	pos = GetFirstViewPosition();
	while (pos != NULL) {
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CDrawView))) {
			((CDrawView*)pView)->Remove(pObj);
		}
	}
#endif
}

// point is in logical coordinates
CDrawObj* CDrawDoc::ObjectAt(BOOL bLeftView, const CPoint& point)
{
	CDrawObjList* pObjects = GetObjects(bLeftView);
	if (pObjects == nullptr) return nullptr;

	CRect rect(point, CSize(1, 1));
	POSITION pos = pObjects->GetTailPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = pObjects->GetPrev(pos);
		if (pObj->Intersects(rect))
			return pObj;
	}

	return NULL;
}

void CDrawDoc::ComputePageSize()
{
	CSize new_size(850, 1100);  // 8.5" x 11" default

	CPrintDialog dlg(FALSE);
	if (AfxGetApp()->GetPrinterDeviceDefaults(&dlg.m_pd))
	{
		// GetPrinterDC returns a HDC so attach it
		CDC dc;
		HDC hDC = dlg.CreatePrinterDC();
		ASSERT(hDC != NULL);
		dc.Attach(hDC);

		// Get the size of the page in loenglish
		new_size.cx = MulDiv(dc.GetDeviceCaps(HORZSIZE), 1000, 254); //pixel to inch 
//지정된 디스플레이 디바이스의 기능에 대한 지정된 종류의 디바이스 관련 정보를 검색합니다.
		new_size.cy = MulDiv(dc.GetDeviceCaps(VERTSIZE), 1000, 254);
	}

#ifndef SHARED_HANDLERS
	// if size changed then iterate over views and reset
	if (new_size != m_size)
	{
		m_size = new_size;
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL) {
			CView* pView = GetNextView(pos);
			if (pView->IsKindOf(RUNTIME_CLASS(CDrawView))) {
				((CDrawView*)pView)->SetPageSize(m_size);
			}
		}
	}
#endif
}



void CDrawDoc::OnViewPaperColor()
{
#ifndef SHARED_HANDLERS
	COLORREF color = ((CMainFrame*)AfxGetMainWnd())->GetColorFromColorButton(ID_VIEW_PAPERCOLOR);
	m_paperColor = color == (COLORREF)-1 ? RGB(255, 255, 255) : color;
	m_paperColorLast = m_paperColor;

	SetModifiedFlag(false);
	m_bIsChange = true;

	UpdateAllViews(NULL);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc diagnostics

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc commands

void CDrawDoc::OnFileSummaryInfo()
{
#ifndef SHARED_HANDLERS
	ASSERT_VALID(this);

	CPropertySheet sheet(_T("Document Properties"));
	CSummPage summ;
	CStatPage stat;
	sheet.AddPage(&summ);
	sheet.AddPage(&stat);

	summ.m_strAppname = m_pSummInfo->GetAppname();
	summ.m_strTitle = m_pSummInfo->GetTitle();
	summ.m_strSubj = m_pSummInfo->GetSubject();
	summ.m_strAuthor = m_pSummInfo->GetAuthor();
	summ.m_strKeywd = m_pSummInfo->GetKeywords();
	summ.m_strCmt = m_pSummInfo->GetComments();
	summ.m_strTempl = m_pSummInfo->GetTemplate();

	stat.m_strSavedBy = m_pSummInfo->GetLastAuthor();
	stat.m_strRevNum = m_pSummInfo->GetRevNum();
	stat.m_strEditTime = m_pSummInfo->GetEditTime();
	stat.m_strLastPrint = m_pSummInfo->GetLastPrintDate();
	stat.m_strCreateDate = m_pSummInfo->GetCreateDate();
	stat.m_strLastSave = m_pSummInfo->GetLastSaveDate();
	stat.m_strNumPages = m_pSummInfo->GetNumPages();
	stat.m_strNumWords = m_pSummInfo->GetNumWords();
	stat.m_strNumChars = m_pSummInfo->GetNumChars();
	stat.m_strSecurity = m_pSummInfo->GetSecurity();

	if (sheet.DoModal() != IDOK)
		return;

	m_pSummInfo->SetAuthor(summ.m_strAuthor);
	m_pSummInfo->SetKeywords(summ.m_strKeywd);
	m_pSummInfo->SetSubject(summ.m_strSubj);
	m_pSummInfo->SetComments(summ.m_strCmt);
	m_pSummInfo->SetTemplate(summ.m_strTempl);
	m_pSummInfo->SetTitle(summ.m_strTitle);

	SetModifiedFlag(false);
	m_bIsChange = true;
#endif
}

void CDrawDoc::SetPreviewColor(COLORREF clr)
{
	m_paperColor = clr == -1 ? m_paperColorLast : clr;
	UpdateAllViews(NULL);
}

void CDrawDoc::LoadDicom(BOOL bLeftView) {

	HelperLoadDicom(bLeftView);
}

void CDrawDoc::HelperLoadDicom(BOOL bLeftView)
{
	DcmFileFormat fileformat;
	OFFilename filePath;

	if (bLeftView) {
		filePath = (OFFilename)m_strFilePath;
		m_nCurrentFrameNo = 0;
		m_nTotalFrameNo = 0;
	}
	else {
		filePath = (OFFilename)m_strRightFilePath;
		m_nCurrentRightFrameNo = 0;
		m_nTotalRightFrameNo = 0;
	}

	if (fileformat.loadFile(filePath).good()) {
		DcmDataset* dataset = fileformat.getDataset();
		OFString strTransferSyntaxUID = nullptr;
		DcmMetaInfo* pDcmMetaInfo = fileformat.getMetaInfo();

		pDcmMetaInfo->findAndGetOFString(DCM_TransferSyntaxUID, strTransferSyntaxUID);
		// 압축된 파일(여러장은 무조건 압축 되어 있음)
		if (std::string::npos != strTransferSyntaxUID.find("1.2.840.10008.1.2.4.50")) {
			//jpeg 일 경우  1.2.840.10008.1.2.4.50    JPEG Baseline (Process 1): Default Transfer Syntax for Lossy JPEG 8 - bit Image Compression
			//여러장의 이미지가 존재함 프레임 수를 읽는다 
			bLeftView ? dataset->findAndGetLongInt(DCM_NumberOfFrames, m_nTotalFrameNo) : dataset->findAndGetLongInt(DCM_NumberOfFrames, m_nTotalRightFrameNo);
		}

		// 압축안된 파일
		else if (std::string::npos != strTransferSyntaxUID.find("1.2.840.10008.1.2")) {
			//dicom 기본 영상으로 1개의 프레임 만 존재함 ("1.2.840.10008.1.2")
			bLeftView ? m_nTotalFrameNo = 1 : m_nTotalRightFrameNo = 1;
		}


		E_TransferSyntax xfer = dataset->getOriginalXfer();
		//데이터 셋으로 이미지를 압축 해제 해서 생성한다 
		DicomImage* ptrDicomImage = bLeftView ? new DicomImage(dataset, xfer, CIF_DecompressCompletePixelData, 0, m_nTotalFrameNo) : new DicomImage(dataset, xfer, CIF_DecompressCompletePixelData, 0, m_nTotalRightFrameNo);

		if (ptrDicomImage) {
			//이미지의 폭과 높이를 얻는다 
			int width = (int)ptrDicomImage->getWidth();
			int height = (int)ptrDicomImage->getHeight();
			void* data = nullptr;

			long& nTotalFrameNo = bLeftView ? m_nTotalFrameNo : m_nTotalRightFrameNo;
			//			BITMAPINFO& bmi = bLeftView ? m_bmiLeft : m_bmiRight;
			//			std::vector<void*>& listData = bLeftView ? m_listData : m_listRightData;
			std::vector<CFourMatDIB>& listData = bLeftView ? m_listLeftDIB : m_listRightDIB;
			std::vector<CDrawObjList*>& objectList = bLeftView ? m_pageLeftObjects : m_pageRightObjects;
			CString strFileName = bLeftView ? m_strFileName : m_strRightFileName;

			for (int i = 0; i < nTotalFrameNo; i++) {
				//프레임의 위치에 있는 영상 정보를 윈도우 이미지 24bit로 생성하여 얻는다 
				ptrDicomImage->createWindowsDIB(data, width * height, i, 24);
				//이미지의 주소를 출력한다

				CFourMatDIB fourMatDIB;
				fourMatDIB.CreateRgbBitmap(width, height, (BYTE*)data);

				listData.emplace_back(std::move(fourMatDIB));

				objectList.push_back(new CDrawObjList());

				//이미지의 주소를 메모리 해제 한다
				delete[] data;
				data = nullptr;
			}

			LoadDraw(strFileName, objectList);

			UpdateAllViews(NULL, HINT_LAOD_DICOMIMAGE);
		}
		SetCurrentFrameNo(bLeftView, 0);
		delete ptrDicomImage;
	}

	/*BYTE* CDrawDoc::GetBitmapItsAddr() const
	{
		if (m_bmi == NULL)
			return NULL;

		LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_bmi;
		return ((BYTE*)m_bmi + lpbmi->biSize + (sizeof(RGBQUAD) * GetPaletteNums()));
	}*/
}


//BOOL CDrawDoc::CanCloseFrame(CFrameWnd* pFrame)
//{
////	m_bCanDeactivateInplace = FALSE;
//
//	BOOL bRes = COleDocument::CanCloseFrame(pFrame);
//
////	m_bCanDeactivateInplace = TRUE;
//
//	return bRes;
//}

void CDrawDoc::FixUpObjectPositions()
{
	CPoint ptLeftTop(0, 0);
	CPoint ptRightBottom(0, 0);

	// find bounding rectangle of all objects 
	for (POSITION pos = m_pObjects->GetHeadPosition(); pos != NULL;)
	{
		CDrawObj* pObj = m_pObjects->GetNext(pos);
		CRect rectPos = pObj->m_position;
		rectPos.NormalizeRect();
		ptLeftTop.x = min(rectPos.left, ptLeftTop.x);
		ptLeftTop.y = min(rectPos.top, ptLeftTop.y);
		ptRightBottom.x = max(rectPos.right, ptRightBottom.x);
		ptRightBottom.y = max(rectPos.bottom, ptRightBottom.y);
	}

	m_rectDocumentBounds.SetRect(ptLeftTop, ptRightBottom);

	// make some borders
	m_rectDocumentBounds.InflateRect(4, 4);

	// center all objects within bounding rectangle
	for (POSITION pos = m_pObjects->GetHeadPosition(); pos != NULL;)
	{
		CDrawObj* pObj = m_pObjects->GetNext(pos);
		pObj->MoveTo(CPoint(-ptLeftTop.x - m_rectDocumentBounds.Width() / 2, -ptLeftTop.y - m_rectDocumentBounds.Height() / 2));
	}
}

#ifdef SHARED_HANDLERS
void CDrawDoc::InitializeSearchContent()
{
	SetAuthor(m_pSummInfo->GetAuthor());
	SetTitle(m_pSummInfo->GetTitle());
	SetComment(m_pSummInfo->GetComments());
	SetKeywords(m_pSummInfo->GetKeywords());
	SetLastAuthor(m_pSummInfo->GetLastAuthor());

	if (m_objects.GetCount() == 0)
	{
		return;
	}

	CString strContent;

	LPCTSTR szTypes[] =
	{
		_T("line"),
		_T("rectangle"),
		_T("rounded rectangle"),
		_T("ellipse"),
		_T("polyline"),
		_T("ole object"),
	};

	struct XColor
	{
		LPCTSTR szName;
		COLORREF clr;
	};

	XColor szColors[] =
	{
		{_T("black")  , RGB(0,   0,   0)},
		{_T("gray")   , RGB(128, 128, 128)},
		{_T("white")  , RGB(255, 255, 255)},
		{_T("maroon") , RGB(128,   0,   0)},
		{_T("green")  , RGB(0, 128,   0)},
		{_T("olive")  , RGB(128, 128,   0)},
		{_T("navy")   , RGB(0,   0, 128)},
		{_T("purple") , RGB(128,   0, 128)},
		{_T("teal")   , RGB(0, 128, 128)},
		{_T("red")    , RGB(255,   0,   0)},
		{_T("lime")   , RGB(0, 255,   0)},
		{_T("yellow") , RGB(255, 255,   0)},
		{_T("blue")   , RGB(0,   0, 255)},
		{_T("fuchsia"), RGB(255,   0, 255)},
		{_T("aqua")   , RGB(0, 255, 255)}
	};
	BYTE nColorIndex[] = { 0, 128, 255 };

	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObject = m_objects.GetNext(pos);
		if (pObject == NULL)
		{
			continue;
		}

		int typeObj = -1;
		//0 - line
		//1 - rectangle
		//2 - rounded rectangle
		//3 - ellipse
		//4 - polyline
		//5 - ole object

		int typeClr = -1;
		//0  - black
		//1  - gray
		//2  - white
		//3  - maroon
		//4  - green
		//5  - olive
		//6  - navy
		//7  - purple
		//8  - teal
		//9  - red
		//10 - lime
		//11 - yellow
		//12 - blue
		//13 - fuchsia
		//14 - aqua

		COLORREF clr = (COLORREF)-1;

		if (DYNAMIC_DOWNCAST(CDrawRect, pObject) != NULL)
		{
			CDrawRect* pDraw = (CDrawRect*)pObject;
			switch (pDraw->GetShape())
			{
			case CDrawRect::line:
				typeObj = 0;
				if (pDraw->IsEnableLine())
				{
					clr = pDraw->GetLineColor();
				}
				break;
			case CDrawRect::rectangle:
				typeObj = 1;
				break;
			case CDrawRect::roundRectangle:
				typeObj = 2;
				break;
			case CDrawRect::ellipse:
				typeObj = 3;
				break;
			}

			if (typeObj != 0)
			{
				if (pDraw->IsEnableFill())
				{
					clr = pDraw->GetFillColor();
				}
			}
		}
		else if (DYNAMIC_DOWNCAST(CDrawPoly, pObject) != NULL)
		{
			typeObj = 4;

			CDrawPoly* pDraw = (CDrawPoly*)pObject;
			if (pDraw->IsEnableFill())
			{
				clr = pDraw->GetFillColor();
			}
		}
		else if (DYNAMIC_DOWNCAST(CDrawOleObj, pObject) != NULL)
		{
			typeObj = 5;
		}

		if (typeObj == -1)
		{
			continue;
		}

		CString strClr;
		if (clr != (COLORREF)-1)
		{
			COLORREF clrOrig = clr;
			clr = RGB
			(
				nColorIndex[GetRValue(clr) / 86],
				nColorIndex[GetGValue(clr) / 86],
				nColorIndex[GetBValue(clr) / 86]
			);
			for (int i = 0; i < sizeof(szColors) / sizeof(XColor); i++)
			{
				if (szColors[i].clr == clr)
				{
					strClr = szColors[i].szName;
					break;
				}
			}

			if (strClr.IsEmpty())
			{
				strClr.Format(_T("#%0X"), clrOrig);
			}
		}
		else
		{
			strClr = _T("empty");
		}

		CString str;
		str = strClr + _T(" ") + szTypes[typeObj];

		if (strContent.IsEmpty())
		{
			strContent = str;
		}
		else if (strContent.Find(str) == -1)
		{
			strContent += _T("; ") + str;
		}
	}

	if (strContent.IsEmpty())
	{
		strContent = _T("empty document");
	}

	SetSearchContents(strContent);
}
void CDrawDoc::SetTitle(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Title.fmtid, PKEY_Title.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Title, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetAuthor(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Author.fmtid, PKEY_Author.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Author, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetCompany(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Company.fmtid, PKEY_Company.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Company, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetComment(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Comment.fmtid, PKEY_Comment.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Comment, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetCopyright(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Copyright.fmtid, PKEY_Copyright.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Copyright, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetKeywords(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Keywords.fmtid, PKEY_Keywords.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Keywords, value);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetLastAuthor(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Document_LastAuthor.fmtid, PKEY_Document_LastAuthor.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Document_LastAuthor, value, CHUNK_VALUE, 0, 0, 0, CHUNK_EOP);
		SetChunkValue(pChunk);
	}
}

void CDrawDoc::SetSearchContents(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = new CMFCFilterChunkValueImpl;
		pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
		SetChunkValue(pChunk);
	}
}

#endif

//리본 버튼 클릭 메세지
CFourMatDIB& CDrawDoc::GetFourMatDIB(BOOL bClickedView)
{
	std::vector <CFourMatDIB>& listDib = bClickedView ? m_listLeftDIB : m_listRightDIB;
	long currentFrameNo = bClickedView ? m_nCurrentFrameNo : m_nCurrentRightFrameNo;

	return listDib[currentFrameNo];
}

void CDrawDoc::OnAffinetranformMirror()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, imgSrc);
	Mirror(imgSrc, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

	/*AfxPrintInfo(_T("[좌우 대칭] 입력 영상: %s"), GetTitle());
	AfxNewBitmap(dib);*/
}


void CDrawDoc::OnAffinetranformRotation()
{
	CRotationDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		ByteImage imgDst;

		FourMatDIBToByteImage(dib, imgSrc);
		switch (dlg.m_nRotate)
		{
		case 0: Rotate90(imgSrc, imgDst); break;
		case 1: Rotate180(imgSrc, imgDst); break;
		case 2: Rotate270(imgSrc, imgDst); break;
		case 3: Rotate(imgSrc, imgDst, (double)dlg.m_fAngle); break;
		}
		FourMatGrayToDIBImage(imgDst, dib);
		//TCHAR* rotate[] = { _T("90도"), _T("180도"), _T("270도") };
		//if (dlg.m_nRotate != 3)
			//AfxPrintInfo(_T("[회전 변환] 입력 영상: %s, 회전 각도: %s"), GetTitle(), rotate[dlg.m_nRotate]);
		//else
			//AfxPrintInfo(_T("[회전 변환] 입력 영상: %s, 회전 각도: %4.2f도"), GetTitle(), dlg.m_fAngle);
		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

	}
}


void CDrawDoc::OnAffinetranformScaling()
{
	CScalingDlg dlg;
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	dlg.m_nOldWidth = dib.GetWidth();
	dlg.m_nOldHeight = dib.GetHeight();
	if (dlg.DoModal() == IDOK)
	{
		ByteImage imgSrc;
		ByteImage imgDst;

		FourMatDIBToByteImage(dib, imgSrc);
		switch (dlg.m_nInterpolation)
		{
		case 0: ResizeNearest(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		case 1: ResizeBilinear(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		case 2: ResizeCubic(imgSrc, imgDst, dlg.m_nNewWidth, dlg.m_nNewHeight); break;
		}
		FourMatGrayToDIBImage(imgDst, dib);
		//	AfxPrintInfo(_T("[크기 변환] 입력 영상: %s, , 새 가로 크기: %d, 새 세로크기: % d, 보간법 : % s"),GetTitle(), dlg.m_nNewWidth, dlg.m_nNewHeight[dlg.m_nInterpolation]);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
	/*	TCHAR* interpolation[] = { _T("최근방 이웃 보간법"), _T("양선형 보간법"
			), _T("3차 회선 보간법") };
		AfxPrintInfo(_T("[크기 변환] 입력 영상: %s, , 새 가로 크기: %d, 새 세로
			크기: % d, 보간법 : % s"),
			GetTitle(), dlg.m_nNewWidth, dlg.m_nNewHeight, interpolation[dlg.m_n
			Interpolation]);
		AfxNewBitmap(dib);
	}*/

}


void CDrawDoc::OnAffinetranformTranslation()
{
	CTranslationDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		ByteImage imgDst;

		FourMatDIBToByteImage(dib, imgSrc);
		Translate(imgSrc, imgDst, dlg.m_nNewSX, dlg.m_nNewSY);
		FourMatGrayToDIBImage(imgDst, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}


void CDrawDoc::OnAffinetransformFlip()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, imgSrc);
	Flip(imgSrc, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

	/*AfxPrintInfo(_T("[상하 대칭] 입력 영상: %s"), GetTitle());
	AfxNewBitmap(dib);*/
}



void CDrawDoc::OnFeatureextractionAddnoise()
{
	CAddNoiseDlg dlg(this);
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		ByteImage imgDst;
		FourMatDIBToByteImage(dib, imgSrc);

		if (dlg.m_nNoiseType == 0)
			NoiseGaussian(imgSrc, imgDst, dlg.m_nAmount);
		else
			NoiseSaltNPepper(imgSrc, imgDst, dlg.m_nAmount);

		FourMatGrayToDIBImage(imgDst, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

		/*TCHAR* noise[] = { _T("가우시안"), _T("소금&후추") };
		AfxPrintInfo(_T("[잡음 추가] 입력 영상: %s, 잡음 종류: %s, 잡음 양: %d"),
			GetTitle(), noise[dlg.m_nNoiseType], dlg.m_nAmount);
		AfxNewBitmap(dib);*/
	}
}


void CDrawDoc::OnFeatureextractionBlur()
{
	CBlurDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgsrc;
		FloatImage imgDst;
		FourMatDIBToByteImage(dib, imgsrc);
		FilterGaussian(imgsrc, imgDst, dlg.m_fSigma);

		FloatImageToFourMatDIB(imgDst, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
		/*AfxPrintInfo(_T("[가우시안 필터] 입력 영상: %s, Sigma: %4.2f"), GetTitle(), dlg.m_fSigma);
		AfxNewBitmap(dib);*/
	}
}


void CDrawDoc::OnFeatureextractionReducenoise()
{
	CReduceNoiseDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage imgSrc;
		FloatImage imgDst;
		FourMatDIBToByteImage(dib, imgSrc);
		FilterDiffusion(imgSrc, imgDst, dlg.m_fLambda, dlg.m_fK, dlg.m_nIteration);
		FloatImageToFourMatDIB(imgDst, dib);
		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
		/*
			AfxPrintInfo(_T("[미디언 필터] 입력 영상: %s"), GetTitle());
		AfxNewBitmap(dib);*/
	}
}


void CDrawDoc::OnFeatureextractionSharpening()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage imgSrc;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, imgSrc);
	FilterLaplacian(imgSrc, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

	/*AfxPrintInfo(_T("[라플라시안 필터] 입력 영상: %s"), GetTitle());
	AfxNewBitmap(dib);//bitmap new  
	*/ 
}


void CDrawDoc::OnFilteringBrightness()
{
	CBrightnessDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage img;

		FourMatDIBToByteImage(dib, img);
		Brightness(img, dlg.m_nBrightness);
		Contrast(img, dlg.m_nContrast);
		FourMatGrayToDIBImage(img, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
	
}





void CDrawDoc::OnFilteringHistogram()
{
	CHistogramDlg dlg;
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);

	dlg.SetImage(dib);
	dlg.DoModal();

		
}


void CDrawDoc::OnFilteringWindowlevel()
{
	/*CWindowLevel dlg;
	if (dlg.DoModal() == IDOK)
	{

	}*/
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CDrawDoc::OnFilteringInverse()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;

	FourMatDIBToByteImage(dib, img);
	Inverse(img);
	FourMatGrayToDIBImage(img, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}

void CDrawDoc::OnFeatureextractionHistogramequalization()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;

	FourMatDIBToByteImage(dib, img);
	HistogramEqualization(img);
	FourMatGrayToDIBImage(img, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);

}


void CDrawDoc::OnFeatureextractionHistogramstretching()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	FourMatDIBToByteImage(dib, img);
	HistogramStretching(img);
	FourMatGrayToDIBImage(img, dib);

	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}


void CDrawDoc::OnMolphologyClosing()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyClosing(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}


void CDrawDoc::OnMolphologyDilation()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyGrayDilation(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}

void CDrawDoc::OnMolphologyErosion()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyGrayErosion(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}


void CDrawDoc::OnMolphologyOpening()
{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgDst;
	FourMatDIBToByteImage(dib, img);
	MorphologyOpening(img, imgDst);
	FourMatGrayToDIBImage(imgDst, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
}

void CDrawDoc::OnObjectSavedraw()
{
	if (!m_bIsChange) {
		AfxMessageBox(_T("변경된 사항이 없습니다."));
		return;
	}
	SaveDraw(m_strFileName, m_pageLeftObjects);
	if (!m_strRightFileName.IsEmpty()) {
		SaveDraw(m_strRightFileName, m_pageRightObjects);
	}
	AfxMessageBox(_T("파일을 저장했습니다."));
	m_bIsChange = false;
}

void CDrawDoc::SaveDraw(CString strFileName, std::vector<CDrawObjList*>& pageObjects) {
	CFile file;

	CString strFilePath = m_strFolderPath + _T("\\") + strFileName;
	if (file.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {
		// modeCreate : 파일을 새로 만들거나 기존의 파일을 초기화
		CArchive ar(&file, CArchive::store);

		ar << pageObjects.size();
		for each (auto pDrawObjList in pageObjects) {
			pDrawObjList->Serialize(ar);
		}
		ar.Close();
		file.Close();
	}
}
void CDrawDoc::LoadDraw(CString strFileName, std::vector<CDrawObjList*>& pageObjects) {
	CFile file;

	CString strFilePath = m_strFolderPath + _T("\\") + strFileName;
	if (!strFileName.IsEmpty()) {
		if (file.Open(strFilePath, CFile::modeRead | CFile::typeBinary)) {
			CArchive ar(&file, CArchive::load);
			ar.m_pDocument = this;
			size_t size;
			ar >> size;
			if (size == pageObjects.size()) { // .drw 받아드림
				for each (auto pDrawObjList in pageObjects) {
					pDrawObjList->Serialize(ar);
				}
				//ar >> m_nRepFrameNo;
			}
			else { // .drw 안받아드림
			}
			ar.Close();
			file.Close();

		}
	}
}

void CDrawDoc::OnFilteringGamma()
{
	CGammaDlg dlg;
	if (dlg.DoModal() == IDOK)
	{

		CFourMatDIB& dib = m_listLeftDIB[m_nCurrentFrameNo];
		ByteImage img;

		FourMatDIBToByteImage(dib, img);
		GammaCorrection(img, dlg.m_fGamma);
		FourMatGrayToDIBImage(img, dib);

		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}



//뷰에 따른 리본 버튼 활성화 비활성화 구분 - UPDATE_COMMAND_UI, Enable()
void CDrawDoc::EnableDrawView(CCmdUI* pCmdUI)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CSplitFrame* pSplitFrame = (CSplitFrame*)pMainFrame->GetActiveFrame();
	CView* pView = pSplitFrame->GetActiveView();
	pCmdUI->Enable(pView->IsKindOf(RUNTIME_CLASS(CDrawView)));
}

void CDrawDoc::OnUpdateActiveRibbon(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	EnableDrawView(pCmdUI);
}

#include "CCannyEdgeDlg.h"
void CDrawDoc::OnFeatureextractionCannyedge()
{
	CCannyEdgeDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
	CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
	ByteImage img;
	ByteImage imgEdge;
	FourMatDIBToByteImage(dib, img);
	EdgeCanny(img, imgEdge, dlg.m_fSigma, dlg.m_fLowTh, dlg.m_fHighTh);
	FourMatGrayToDIBImage(imgEdge, dib);
	UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}

#include "CHarrisCornerDlg.h"
void CDrawDoc::OnFeatureextractionHarriscorner()
{
	CHarrisCornerDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CFourMatDIB& dib = GetFourMatDIB(m_bClickedView);
		ByteImage img;
		FourMatDIBToByteImage(dib, img);
		std::vector<Point> corners;
		HarrisCorner(img, corners, dlg.m_nHarrisTh);

		BYTE** ptr = img.GetPixels2D();
		int x, y;
		for (Point cp : corners)
		{
			x = cp.x;
			y = cp.y;
			ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 0;
			ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 0;
			ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 0;
		}
		FourMatGrayToDIBImage(img, dib);
		AfxMessageBox("확인");
		UpdateAllViews(NULL, HINT_DICOM_IMAGE_REDRAW);
	}
}

#include "CCompareDlg.h"
void CDrawDoc::OnCompareCompare() // 비교 dlg
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//CDrawDoc* pDrawDoc = (CDrawDoc*)GetDocument();

	CCompareDlg dlg(this);
	dlg.DoModal();
}


void CDrawDoc::OnUpdateCompareCompare(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(!m_strRightFilePath.IsEmpty());
}
