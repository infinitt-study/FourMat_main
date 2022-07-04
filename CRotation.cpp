// CRotation.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CRotation.h"
#include "afxdialogex.h"


// CRotation 대화 상자

IMPLEMENT_DYNAMIC(CRotation, CDialogEx)

CRotation::CRotation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AFFINETRANSFORM_ROTATION, pParent)
	, m_nRotate(0)
	, m_fAngle(0)
{

}

CRotation::~CRotation()
{
}

void CRotation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ROTATE90, m_nRotate);
	DDX_Text(pDX, IDC_ANGLE, m_fAngle);
	DDV_MinMaxFloat(pDX, m_fAngle, 0, 360);
}


BEGIN_MESSAGE_MAP(CRotation, CDialogEx)
END_MESSAGE_MAP()


// CRotation 메시지 처리기


BOOL CRotation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
