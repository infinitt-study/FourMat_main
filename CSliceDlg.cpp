// CSlice.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CSliceDlg.h"
#include "afxdialogex.h"

//#include "drawvw.h"

// CSlice 대화 상자

IMPLEMENT_DYNAMIC(CSliceDlg, CDialogEx)

CSliceDlg::CSliceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_SLICE, pParent)
{

}

CSliceDlg::~CSliceDlg()
{
}

void CSliceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSliceDlg, CDialogEx)
END_MESSAGE_MAP()


// CSliceDlg 메시지 처리기
