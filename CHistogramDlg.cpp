// CHistogramDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CHistogramDlg.h"
#include "afxdialogex.h"


// CHistogramDlg 대화 상자

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)

int m_Histogram[256];

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISTOGRAM, pParent)
{
	memset(m_Histogram, 0, sizeof(int) * 256);
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistogramDlg 메시지 처리기


void CHistogramDlg::OnPaint()
{

	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CGdiObject* pOldPen = dc.SelectStockObject(DC_PEN);
	// 히스토그램 박스
	dc.SetDCPenColor(RGB(128, 128, 128));
	dc.MoveTo(20, 20);
	dc.LineTo(20, 120);
	dc.LineTo(275, 120);
	dc.LineTo(275, 20);
	// 각 그레이스케일에 해당하는 히스토그램 출력
	dc.SetDCPenColor(RGB(0, 0, 0));
	for (int i = 0; i < 256; i++)
	{
		dc.MoveTo(20 + i, 120);
		dc.LineTo(20 + i, 120 - m_Histogram[i]);
	}
	// 그레이스케일 레벨 출력
	for (int i = 0; i < 256; i++)
	{
		dc.SetDCPenColor(RGB(i, i, i));
		dc.MoveTo(20 + i, 130);
		dc.LineTo(20 + i, 145);
	}
	dc.SelectObject(pOldPen);
}
