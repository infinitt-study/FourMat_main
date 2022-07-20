// CAlbumDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CHistoryView.h"
#include "drawdoc.h"

#include "CAlbumDlg.h"
#include "afxdialogex.h"


// CAlbumDlg 대화 상자

IMPLEMENT_DYNAMIC(CAlbumDlg, CDialogEx)

CAlbumDlg::CAlbumDlg(CDrawDoc* pDrawDoc, std::vector <CAccessObjectPtr>& listRefDrawObj
	, int nDrwCount, CString fileName, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTORY_ALBUM, pParent)
	, m_pDrawDoc(pDrawDoc)
	, m_listRefDrawObj(listRefDrawObj)
	, m_nDrwTotalNo(nDrwCount)
	, m_nCurrentNo(0)
	, m_strFileName(fileName)
{
}

CAlbumDlg::~CAlbumDlg()
{
}

void CAlbumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlbumDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CAlbumDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CAlbumDlg::OnBnClickedButtonRight)
END_MESSAGE_MAP()


BOOL CAlbumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_HIDE);
	if (m_nCurrentNo >= m_nDrwTotalNo - 1) GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAlbumDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	CFourMatDIB& m_nCurrentDIB = m_listRefDrawObj[m_nCurrentNo]->m_listDIB[0];
	
	//m_nCurrentDIB.Draw(dc.m_hDC, 150, 5, 400, 400, SRCCOPY);
	m_nCurrentDIB.Draw(dc.m_hDC, 150, 405, 400, -400, SRCCOPY);

	SetTextColor(dc.m_hDC, RGB(0, 0, 0)); // 글씨 검정
	SetBkMode(dc.m_hDC, TRANSPARENT); // 배경 투명
	SetTextAlign(dc.m_hDC, TA_CENTER);

	CRect rect;
	GetClientRect(rect);
	CString strPageInfo;
	strPageInfo.Format(_T("%d / %d"), m_nCurrentNo + 1, m_nDrwTotalNo);
	TextOut(dc.m_hDC, rect.Width() / 2, rect.Height() - 40, m_strFileName, m_strFileName.GetLength());
	TextOut(dc.m_hDC, rect.Width() / 2, rect.Height() - 20 , strPageInfo, strPageInfo.GetLength());
	
}


void CAlbumDlg::OnBnClickedButtonLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nCurrentNo--;
	if(m_nCurrentNo == 0) GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_SHOW);
	Invalidate();
}


void CAlbumDlg::OnBnClickedButtonRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nCurrentNo++;
	if(m_nCurrentNo == m_nDrwTotalNo - 1) GetDlgItem(IDC_BUTTON_RIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LEFT)->ShowWindow(SW_SHOW);
	Invalidate();
}

