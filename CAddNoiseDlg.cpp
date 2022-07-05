// CAddNoiseDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CAddNoiseDlg.h"
#include "afxdialogex.h"


// CAddNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CAddNoiseDlg, CDialogEx)

CAddNoiseDlg::CAddNoiseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_ADDNOISE, pParent)
	, m_nNoiseType(0)
	, m_nAmount(0)
{

}

CAddNoiseDlg::~CAddNoiseDlg()
{
}

void CAddNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_NOISE_RADIO1, m_nNoiseType);
	DDX_Text(pDX, IDC_NOISE_AMOUNT, m_nAmount);
	DDV_MinMaxInt(pDX, m_nAmount, 0, 100);
}


BEGIN_MESSAGE_MAP(CAddNoiseDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddNoiseDlg 메시지 처리기
