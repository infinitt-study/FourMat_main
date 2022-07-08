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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CSliceDlg 메시지 처리기

/*
HDC hSrc = CreateCompatibleDC(NULL);
SelectObject(hSrc, m_Handle);

HDC hNew = CreateCompatibleDC(hSrc);
HBITMAP hBmp = CreateCompatibleBitmap(hSrc, cropArea.right - cropArea.left, cropArea.bottom - cropArea.top);
HBITMAP hOld = (HBITMAP)SelectObject(hNew, hBmp);

bool retVal = (BitBlt(hNew, 0, 0, cropArea.right - cropArea.left, cropArea.bottom - cropArea.top, hSrc, cropArea.left, cropArea.top, SRCCOPY))?true:false;

SelectObject(hNew, hOld);

DeleteDC(hSrc);
DeleteDC(hNew);

DeleteObject(m_Handle);

m_Handle = hBmp;

return retVal;
*/

void CSliceDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSliceDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);
}
