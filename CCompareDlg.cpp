// CCompareDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CCompareDlg.h"
#include "afxdialogex.h"

#include "drawdoc.h"

// CCompareDlg 대화 상자

IMPLEMENT_DYNAMIC(CCompareDlg, CDialogEx)

//CCompareDlg::CCompareDlg(CWnd* pParent /*=nullptr*/)
//	: CDialogEx(IDD_HISTORY_COMPARE, pParent)
//{
//
//}

CCompareDlg::CCompareDlg(CDrawDoc* pDrawDoc, CWnd* pParent)
	: CDialogEx(IDD_HISTORY_COMPARE, pParent)
	, m_pDrawDoc(pDrawDoc)
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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CCompareDlg 메시지 처리기


void CCompareDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	m_pDrawDoc->DIBDraw(TRUE, &dc, 7, 10, 100, 100);
	m_pDrawDoc->DIBDraw(FALSE, &dc, 700, 10, 100, 100);

	//m_pResultDrawDoc()

	/*m_pDrawDoc->DIBDraw(TRUE, &dc, 100, 10, 500, 500);
	m_pDrawDoc->DIBDraw(FALSE, &dc, 100, 10, 500, 500);*/
}
