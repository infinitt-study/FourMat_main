// Transformation.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CTranslationDlg.h"
#include "afxdialogex.h"


// Translation 대화 상자

IMPLEMENT_DYNAMIC(CTranslationDlg, CDialogEx)

CTranslationDlg::CTranslationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_TRANSLATION, pParent)
	, m_nNewSX(0)
	, m_nNewSY(0)
{

}

CTranslationDlg::~CTranslationDlg()
{
}

void CTranslationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEW_SX, m_nNewSX);
	DDX_Text(pDX, IDC_NEW_SY, m_nNewSY);
}


BEGIN_MESSAGE_MAP(CTranslationDlg, CDialogEx)
END_MESSAGE_MAP()


// Transformation 메시지 처리기



