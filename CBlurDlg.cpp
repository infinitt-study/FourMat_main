// CBlurDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CBlurDlg.h"
#include "afxdialogex.h"


// CBlurDlg 대화 상자

IMPLEMENT_DYNAMIC(CBlurDlg, CDialogEx)

CBlurDlg::CBlurDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_BLUR, pParent)
	, m_fSigma(0)
{

}

CBlurDlg::~CBlurDlg()
{
}

void CBlurDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIGMA_SLIDER, m_sliderSigma);
	DDX_Text(pDX, IDC_SIGMA_EDIT, m_fSigma);
	DDV_MinMaxFloat(pDX, m_fSigma, 0.20, 5.00);
}


BEGIN_MESSAGE_MAP(CBlurDlg, CDialogEx)
END_MESSAGE_MAP()


// CBlurDlg 메시지 처리기
