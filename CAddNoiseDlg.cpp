// CAddNoiseDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "FourMat.h"
#include "CAddNoiseDlg.h"
#include "afxdialogex.h"
#include "drawdoc.h"
#include "mainfrm.h"

// CAddNoiseDlg 대화 상자

IMPLEMENT_DYNAMIC(CAddNoiseDlg, CDialogEx)

CAddNoiseDlg::CAddNoiseDlg(CDrawDoc* pDrawDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FEATUREEXTRACTION_ADDNOISE, pParent)
	, m_nNoiseType(0)
	, m_nAmount(0)
	,m_pDrawDoc(pDrawDoc)

{
	
}

CAddNoiseDlg::~CAddNoiseDlg()
{
}

void CAddNoiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_NOISE_RADIO1, m_nNoiseType);
	DDX_Text(pDX, IDC_NOISE_AMOUNT, m_nAmount);
	DDV_MinMaxInt(pDX, m_nAmount, 0, 100);
}


BEGIN_MESSAGE_MAP(CAddNoiseDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAddNoiseDlg 메시지 처리기


BOOL CAddNoiseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_AMOUNT))->SetRange(0, 100);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CAddNoiseDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//CFourMatDIB::
	//Cdrawdoc doc;
	//CDrawDoc* pDrawDoc = (CDrawDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();//
	//이미지 정보 접근 
	
	m_pDrawDoc->DIBDraw(true,&dc,100,260,200,-200);


	
	
}





