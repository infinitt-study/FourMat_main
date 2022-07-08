// CRotation.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CRotationDlg.h"
#include "afxdialogex.h"


// CRotation 대화 상자

IMPLEMENT_DYNAMIC(CRotationDlg, CDialogEx)

CRotationDlg::CRotationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_ROTATION, pParent)
	, m_nRotate(0)
	, m_fAngle(0)
{

}

CRotationDlg::~CRotationDlg()
{
}

void CRotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ROTATE90, m_nRotate);
	DDX_Text(pDX, IDC_ANGLE, m_fAngle);
	DDV_MinMaxFloat(pDX, m_fAngle, 0, 360);
}


BEGIN_MESSAGE_MAP(CRotationDlg, CDialogEx)
	ON_EN_SETFOCUS(IDC_ANGLE, &CRotationDlg::OnEnSetfocusAngle)
	ON_BN_CLICKED(IDC_ROTATE_USER, &CRotationDlg::OnBnClickedRotateUser)
END_MESSAGE_MAP()


// CRotation 메시지 처리기


BOOL CRotationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
//세 개의 함수는 모두 ByteImage 타입의 입력 영상 imgSrc를 각각 정해진 각도만큼 회전하여 결과 영상을 imgDst에 저장한다.

//void Rotate90(ByteImage& imgSrc, ByteImage& imgDst)
//{
//	int w = imgSrc.GetWidth();
//	int h = imgSrc.GetHeight();
//	imgDst.CreateImage(h, w);
//	BYTE** pSrc = imgSrc.GetPixels2D();
//	BYTE** pDst = imgDst.GetPixels2D();
//	int i, j;
//	for (j = 0; j < w; j++)
//		for (i = 0; i < h; i++)
//		{
//			pDst[j][i] = pSrc[h - 1 - i][j];
//		}
//}
//void Rotate180(ByteImage& imgSrc, ByteImage& imgDst)
//{
//	int w = imgSrc.GetWidth();
//	int h = imgSrc.GetHeight();
//	imgDst.CreateImage(w, h);
//	BYTE** pSrc = imgSrc.GetPixels2D();
//	BYTE** pDst = imgDst.GetPixels2D();
//	int i, j;
//	for (j = 0; j < h; j++)
//		for (i = 0; i < w; i++)
//		{
//			pDst[j][i] = pSrc[h - 1 - j][w - 1 - i];
//		}
//}
//void Rotate270(ByteImage& imgSrc, ByteImage& imgDst)
//{
//	ByteImage cpy = imgSrc;
//	int w = imgSrc.GetWidth();
//	int h = imgSrc.GetHeight();
//	imgDst.CreateImage(h, w);
//	BYTE** pSrc = imgSrc.GetPixels2D();
//	BYTE** pDst = imgDst.GetPixels2D();
//	int i, j;
//	for (j = 0; j < w; j++)
//		for (i = 0; i < h; i++)
//		{
//			pDst[j][i] = pSrc[i][w - 1 - j];
//		}
//}




void CRotationDlg::OnEnSetfocusAngle()
{
	m_nRotate = 3;
	UpdateData(FALSE);
}



void CRotationDlg::OnBnClickedRotateUser()
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_ANGLE);
	pEdit->SetSel(0, -1);
	pEdit->SetFocus();
}
