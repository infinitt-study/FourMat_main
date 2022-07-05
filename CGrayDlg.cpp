// CGrayDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CGrayDlg.h"
#include "afxdialogex.h"


// CGrayDlg 대화 상자

IMPLEMENT_DYNAMIC(CGrayDlg, CDialogEx)

CGrayDlg::CGrayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERING_GRAY, pParent)
	, m_nGray(0)
{

}

CGrayDlg::~CGrayDlg()
{
}

void CGrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAY_SLIDER, m_sliderGray);
	DDX_Text(pDX, IDC_GRAY_EDIT, m_nGray);
	DDV_MinMaxInt(pDX, m_nGray, 0, 255);
}


BEGIN_MESSAGE_MAP(CGrayDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CGrayDlg 메시지 처리기


BOOL CGrayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_sliderGray.SetRange(0, 255);
	m_sliderGray.SetTicFreq(32);
	m_sliderGray.SetPageSize(32);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CGrayDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_sliderGray.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nGray = m_sliderGray.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
