// CGammaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CGammaDlg.h"
#include "afxdialogex.h"


// CGammaDlg 대화 상자

IMPLEMENT_DYNAMIC(CGammaDlg, CDialogEx)

CGammaDlg::CGammaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTERING_GAMMA, pParent)
	, m_fGamma(0)
{

}

CGammaDlg::~CGammaDlg()
{
}

void CGammaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAMMA_SLIDER, m_sliderGamma);
	DDX_Text(pDX, IDC_GAMMA_EDIT, m_fGamma);
	DDV_MinMaxFloat(pDX, m_fGamma, 0.20, 5.00);
}


BEGIN_MESSAGE_MAP(CGammaDlg, CDialogEx)
END_MESSAGE_MAP()


// CGammaDlg 메시지 처리기
