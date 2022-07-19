// CCannyEdgeDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CCannyEdgeDlg.h"
#include "afxdialogex.h"


// CCannyEdgeDlg 대화 상자

IMPLEMENT_DYNAMIC(CCannyEdgeDlg, CDialogEx)

CCannyEdgeDlg::CCannyEdgeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_CANNY_EDGE, pParent)
	, m_fSigma(0)
	, m_fLowTh(0)
	, m_fHighTh(0)
{

}

CCannyEdgeDlg::~CCannyEdgeDlg()
{
}

void CCannyEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CANNY_SIGMA, m_fSigma);
	DDX_Text(pDX, IDC_LOW_THRESHOLD, m_fLowTh);
	DDX_Text(pDX, IDC_HIGH_THRESHOLD, m_fHighTh);
}


BEGIN_MESSAGE_MAP(CCannyEdgeDlg, CDialogEx)
END_MESSAGE_MAP()


// CCannyEdgeDlg 메시지 처리기
