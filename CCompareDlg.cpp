// CCompareDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CCompareDlg.h"
#include "afxdialogex.h"


// CCompareDlg 대화 상자

IMPLEMENT_DYNAMIC(CCompareDlg, CDialogEx)

CCompareDlg::CCompareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTORY_COMPARE, pParent)
{

}

CCompareDlg::~CCompareDlg()
{
}

void CCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCompareDlg, CDialogEx)
END_MESSAGE_MAP()


// CCompareDlg 메시지 처리기
