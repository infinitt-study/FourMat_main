// CSearchFileView.cpp: 구현 파일
//
#include "stdafx.h"
#include "FourMat.h"
#include "CSearchFileView.h"
#include "splitfrm.h"
#include "CHistoryView.h"
#include "drawdoc.h"
#include "drawvw.h"
// CSearchFileView

IMPLEMENT_DYNCREATE(CSearchFileView, CFormView)

CSearchFileView::CSearchFileView()
	: CFormView(IDD_SEARCH_FORM)
	, m_strFileName(_T(""))
	, m_strFileLocation(_T(""))
	, m_bSub(FALSE)
{
	m_strToken = _T("");
}

CSearchFileView::~CSearchFileView()
{
}

void CSearchFileView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_FILELOCATION, m_strFileLocation);
	DDX_Check(pDX, IDC_CHECK1, m_bSub);
	DDX_Control(pDX, IDC_LIST_RESULT, m_lstResult);
}

BEGIN_MESSAGE_MAP(CSearchFileView, CFormView)
    ON_BN_CLICKED(IDC_BUTTON_START, &CSearchFileView::OnClickedButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_FOLDER_SELECT, &CSearchFileView::OnClickedButtonSingle)
END_MESSAGE_MAP()


// CSearchFileView 진단

#ifdef _DEBUG
void CSearchFileView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSearchFileView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSearchFileView 메시지 처리기


void CSearchFileView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

    CSplitFrame* pSplitFrame = (CSplitFrame *) GetParentFrame();
    pSplitFrame->SetSearchFileView(this);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 리스트 컨트롤에 이미지 연결
	m_img.Create(IDB_LIST, 16, 1, RGB(255, 255, 255));
	m_lstResult.SetImageList(&m_img, LVSIL_SMALL);

	// InsertColumn() : 리스트 컨트롤의 필드에 입력하는 함수
	m_lstResult.InsertColumn(0, "이름", LVCFMT_LEFT, 150);
	m_lstResult.InsertColumn(1, "위치", LVCFMT_LEFT, 200);
	m_lstResult.InsertColumn(2, "크기(byte)", LVCFMT_RIGHT, 80);
	m_lstResult.InsertColumn(3, "생성날짜", LVCFMT_CENTER, 150);

    //체크박스 추가
    DWORD dwExStyle = m_lstResult.GetExtendedStyle();
    m_lstResult.SetExtendedStyle(dwExStyle | LVS_EX_CHECKBOXES | LVS_EX_BORDERSELECT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// GetCurrentDirectory() : 프로그램이 실행되는 위치(폴더)를 얻어옴. 얻어진 결과는 m_strFileLocation에 입력
	char pBuf[256];
	GetCurrentDirectory(256, pBuf);

    //실행되는 위치 -> "목록" 폴더
    strcat(pBuf, "\\목록");

	m_strFileLocation.Format("%s", pBuf);
	UpdateData(FALSE);


    //최초 1회는 자동으로 목록 출력
    m_lstResult.DeleteAllItems();
    m_strToken = m_strFileName;
    m_strToken.MakeUpper();
    SearFileNotSub();
}

// 하위 폴더를 제외한 검색 구현
void CSearchFileView::SearFileNotSub() {

    UpdateData(TRUE);

    CString strTmp, strFolder, strName;
    CFileFindEx cfile;
    int i;
    BOOL b;
    MSG msg;

    // 시작 위치를 지정. 검색 조건은 모든 파일(*.*) 이다.
    if (m_strFileLocation.Right(1) == "\\")
        strTmp = m_strFileLocation + "\\*.*";
    else {
        strTmp = m_strFileLocation + "\\";
        strTmp += "*.*";
    }

    b = cfile.FindFile(strTmp);

    while (b) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        b = cfile.FindNextFile();

        // . ..일 경우
        if (cfile.IsDots())
            continue;

        i = m_lstResult.GetItemCount();

        // 검색 결과가 위치하는 폴더 열기
        strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1);

        // 파일(폴더)이름 얻기
        strName = cfile.GetFileName();

        //얻어진 결과를 대문자로 변경
        strName.MakeUpper();

        if (strName.Find(m_strToken) != -1) {    // 조건에 맞는 경우
            if (cfile.IsDirectory()) {            // 폴더이면
                // 리스트 컨트롤에 데이터 입력
                // 0번 그림과 함께 출력
                m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
                m_lstResult.AddItem(strFolder, i, 1);
                m_lstResult.AddItem("파일폴더", i, 2);
                m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
            }
        }
    }
}

void CSearchFileView::SearFile(CString strStartFolder)
{
    UpdateData(TRUE);
 
    CString strTmp, strFolder, strName;
    CFileFindEx cfile;
    int i;
    BOOL b;
    MSG msg;
 
    // 시작 위치를 지정. 검색 조건은 모든 파일(*.*) 이다.
    if (strStartFolder.Right(1) == "\\")
        strTmp = strStartFolder + "*.*";
    else {
        strTmp = strStartFolder + "\\";
        strTmp += "*.*";
    }
 
    b = cfile.FindFile(strTmp);
 
    while (b) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
 
        b = cfile.FindNextFile();
 
        // . ..일 경우
        if (cfile.IsDots())
            continue;
 
        i = m_lstResult.GetItemCount();
 
        // 검색 결과가 위치하는 폴더 열기
        strFolder = cfile.GetFilePath().Left(cfile.GetFilePath().ReverseFind('\\') + 1);
 
        // 파일(폴더)이름 얻기
        strName = cfile.GetFileName();
 
        //얻어진 결과를 대문자로 변경
        strName.MakeUpper();
 
        if (cfile.IsDirectory()) {            // 폴더이면
            if (strName.Find(m_strToken) != -1) {
                m_lstResult.AddItem(cfile.GetFileName(), i, 0, -1, 0);
                m_lstResult.AddItem(strFolder, i, 1);
                m_lstResult.AddItem("파일폴더", i, 2);
                m_lstResult.AddItem(cfile.GetCreationTimeString(), i, 3);
            }
            SearFile(cfile.GetFilePath());    // 재귀함수 호출
        }
    }
}

void CSearchFileView::OnClickedButtonStart()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    UpdateData(TRUE);
    m_lstResult.DeleteAllItems();

    //m_strToken = m_strFileName;
    //m_strToken.MakeUpper();

    if (m_bSub == TRUE) {
        SearFile(m_strFileLocation);
    }
    else {
        SearFileNotSub();
    }
    UpdateData(FALSE);
}


void CSearchFileView::OnClickedButtonSingle()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    const int nCount = m_lstResult.GetItemCount();
    CString strFolderName;

    int nRow;
    for (int i = nCount - 1; i >= 0; --i) {
        if (m_lstResult.GetCheck(i)) {
            strFolderName = m_lstResult.GetItemText(i, 0);
            nRow = i;
            break;
        }
    }
    if (strFolderName.IsEmpty()) {
        AfxMessageBox(_T("폴더를 선택해 주세요"));
        return;
    }

    //뷰 스위칭
    CSplitFrame* pSplitFrame = (CSplitFrame*)GetParentFrame();

    CDrawDoc* pDrawDoc = (CDrawDoc*)GetDocument();
    pDrawDoc->m_strFolderPath = m_strFileLocation + "\\" + strFolderName;
    pDrawDoc->UpdateAllViews(NULL, HINT_UPDATE_FOLDERPATH);

    pSplitFrame->SwitchView(VIEWID_HISTORY);
}
