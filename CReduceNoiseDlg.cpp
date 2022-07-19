// CReduceNoiseDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CReduceNoiseDlg.h"
#include "afxdialogex.h"


// CReduceNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CReduceNoiseDlg, CDialogEx)

CReduceNoiseDlg::CReduceNoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_REDUCENOISE, pParent)
	, m_fLambda(0)
	, m_fK(0)
	, m_nIteration(0)
{

}

CReduceNoiseDlg::~CReduceNoiseDlg()
{

}

void CReduceNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DIFFUSION_LAMBDA, m_fLambda);
	DDV_MinMaxFloat(pDX, m_fLambda, 0, 0.25);
	DDX_Text(pDX, IDC_DIFFUSION_K, m_fK);
	DDX_Text(pDX, IDC_DIFFUSION_ITER, m_nIteration);
	DDV_MinMaxInt(pDX, m_nIteration, 0, 100);
}


BEGIN_MESSAGE_MAP(CReduceNoiseDlg, CDialogEx)
//	ON_WM_PAINT()
END_MESSAGE_MAP()


// CReduceNoiseDlg 메시지 처리기

