// Transformation.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CTranslationDlg.h"
#include "afxdialogex.h"


// Translation 대화 상자

IMPLEMENT_DYNAMIC(CTranslationDlg, CDialogEx)

CTranslationDlg::CTranslationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_AFFINETRANSFORM_TRANSLATION, pParent)
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

//void IppTranslate(IppByteImage& imgSrc, IppByteImage& imgDst, int sx, int sy)
//{
//int w = imgSrc.GetWidth();
//int h = imgSrc.GetHeight();
//imgDst.CreateImage(w, h);
//BYTE** pSrc = imgSrc.GetPixels2D();
//BYTE** pDst = imgDst.GetPixels2D();
//int i, j, x, y;
//for (j = 0; j < h; j++)
//for (i = 0; i < w; i++)
//{
//x = i - sx;
//y = j - sy;
//if (x >= 0 && x < w && y >= 0 && y < h)
//pDst[j][i] = pSrc[y][x];
//}
//}

