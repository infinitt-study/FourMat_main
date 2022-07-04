// CSlice.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CSlice.h"
#include "afxdialogex.h"

//#include "drawvw.h"

// CSlice 대화 상자

IMPLEMENT_DYNAMIC(CSlice, CDialogEx)

CSlice::CSlice(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_SLICE, pParent)
{

}

CSlice::~CSlice()
{
}

void CSlice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSlice, CDialogEx)
END_MESSAGE_MAP()


// CSlice 메시지 처리기
