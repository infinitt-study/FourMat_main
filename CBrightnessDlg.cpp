// CBrightnessDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CBrightnessDlg.h"
#include "afxdialogex.h"


// CBrightnessDlg 대화 상자

IMPLEMENT_DYNAMIC(CBrightnessDlg, CDialogEx)

CBrightnessDlg::CBrightnessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERING_BRIGHTNESS, pParent)
	, m_nBrightness(0)
	, m_nContrast(0)
{

}

CBrightnessDlg::~CBrightnessDlg()
{
}

void CBrightnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDV_MinMaxInt(pDX, m_nBrightness, -255, 255);
	DDX_Text(pDX, IDC_BRIGHT_EDIT, m_nBrightness);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderBrightness);
	DDX_Text(pDX, IDC_CONTRAST_EDIT, m_nContrast);
	DDV_MinMaxInt(pDX, m_nContrast, -100, 100);
	DDX_Control(pDX, IDC_CONTRAST_SLIDER, m_sliderContrast);
}


BEGIN_MESSAGE_MAP(CBrightnessDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CBrightnessDlg 메시지 처리기


BOOL CBrightnessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 밝기 조절 슬라이더 컨트롤 초기화
	m_sliderBrightness.SetRange(-255, 255);
	m_sliderBrightness.SetTicFreq(32);
	m_sliderBrightness.SetPageSize(32);
	// 명암비 조절 슬라이더 컨트롤 초기화
	m_sliderContrast.SetRange(-100, 100);
	m_sliderContrast.SetTicFreq(20);
	m_sliderContrast.SetPageSize(20);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBrightnessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_sliderBrightness.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nBrightness = m_sliderBrightness.GetPos();
		UpdateData(FALSE);
	}
	// 명암비 조절 슬라이드바에서 발생한 WM_HSCROLL 메시지 처리
	else if (m_sliderContrast.GetSafeHwnd() == pScrollBar->GetSafeHwnd())
	{
		m_nContrast = m_sliderContrast.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
