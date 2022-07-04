// Transformation.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CTransformation.h"
#include "afxdialogex.h"


// Transformation 대화 상자

IMPLEMENT_DYNAMIC(CTransformation, CDialogEx)

CTransformation::CTransformation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_TRANSFORMATION, pParent)
	, m_nNewSX(0)
	, m_nNewSY(0)
{

}

CTransformation::~CTransformation()
{
}

void CTransformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEW_SX, m_nNewSX);
	DDX_Text(pDX, IDC_NEW_SY, m_nNewSY);
}


BEGIN_MESSAGE_MAP(CTransformation, CDialogEx)
END_MESSAGE_MAP()


// Transformation 메시지 처리기
