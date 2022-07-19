// CCompareDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CFourMatDIB.h"
#include "CCompareDlg.h"
#include "afxdialogex.h"

#include "drawdoc.h"
#include "CConvertDataType.h"
#include "CImprovement.h"

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
	, m_dibLeftRef(pDrawDoc->GetFourMatDIB(TRUE))
	, m_dibRightRef(pDrawDoc->GetFourMatDIB(FALSE))
	, m_dib(pDrawDoc->GetFourMatDIB(TRUE))
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


void CCompareDlg::OnPaint() // 출력부분
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	m_pDrawDoc->DIBDraw(TRUE, &dc, 7, 10, 100, 100); //imgLeftSrc
	m_pDrawDoc->DIBDraw(FALSE, &dc, 700, 10, 100, 100); //imgRightSrc

	m_dib.Draw(dc.m_hDC, 200, 10, 400, 400); //imgDst
}


BOOL CCompareDlg::OnInitDialog() // 연산부분
{
	CDialogEx::OnInitDialog();

	ByteImage imgLeftSrc;
	ByteImage imgRightSrc;
	ByteImage imgDst;

	FourMatDIBToByteImage(m_dibLeftRef, imgLeftSrc);
	FourMatDIBToByteImage(m_dibRightRef, imgRightSrc);
	FourMatDIBToByteImage(m_dib, imgDst);

	int w = imgLeftSrc.GetWidth();
	int h = imgLeftSrc.GetHeight();

	int size = imgDst.GetSize();
	BYTE* p1 = imgLeftSrc.GetPixels();
	BYTE* p2 = imgRightSrc.GetPixels();
	BYTE* p3 = imgDst.GetPixels();

	for (int i = 0; i < size; i++) // 평균 연산
	{
		p3[i] = (p1[i] + p2[i]) / 2;
	}

	ByteImageToFourMatDIB(imgDst, m_dib);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
