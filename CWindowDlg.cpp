// CWindowDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CWindowDlg.h"
#include "afxdialogex.h"


// CWindowDlg 대화 상자

IMPLEMENT_DYNAMIC(CWindowDlg, CDialogEx)

CWindowDlg::CWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERING_WINDOW_LEVEL, pParent)
	, m_nWindow(0)
	, m_nLevel(0)
{

}

CWindowDlg::~CWindowDlg()
{
}

void CWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WINDOW_SLIDER, m_sliderWindow);
	DDX_Text(pDX, IDC_WINDOW_EDIT, m_nWindow);
	DDV_MinMaxInt(pDX, m_nWindow, 0, 255);
	DDX_Control(pDX, IDC_LEVEL_SLIDER, m_sliderLevel);
	DDX_Text(pDX, IDC_LEVEL_EDIT, m_nLevel);
	DDV_MinMaxInt(pDX, m_nLevel, 0, 255);
}


BEGIN_MESSAGE_MAP(CWindowDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CWindowDlg 메시지 처리기


BOOL CWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.


	m_sliderWindow.SetRange(0, 255);
	m_sliderWindow.SetTicFreq(32);
	m_sliderWindow.SetPageSize(32);

	m_sliderLevel.SetRange(0, 255);
	m_sliderLevel.SetTicFreq(32);
	m_sliderLevel.SetPageSize(32);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CWindowDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_sliderWindow.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nWindow = m_sliderWindow.GetPos();
		UpdateData(FALSE);
	}

	if (m_sliderLevel.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nLevel = m_sliderLevel.GetPos();
		UpdateData(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
