// CHistogramDlg.cpp: 구현 파일
//
#include "stdafx.h"
#include "FourMat.h"
#include "CHistogramDlg.h"
#include "afxdialogex.h"
// CHistogramDlg 대화 상자
IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)
CHistogramDlg::CHistogramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
	, m_nHistogram(0)
{

}
CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CHistogramDlg 메시지 처리기

BOOL CHistogramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	/*m_sliderHistogram.SetRange(0, 255);
	m_sliderHistogram.SetTicFreq(32);
	m_sliderHistogram.SetPageSize(32);*/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHistogramDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//if (m_sliderHistogram.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	//{
	//	m_nHistogram = m_sliderHistogram.GetPos();
	//	UpdateData(FALSE);
	//}

	//CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

