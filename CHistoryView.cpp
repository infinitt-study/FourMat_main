// CHistoryView.cpp: 구현 파일
//

//#include "pch.h"
#include "stdafx.h"
#include "FourMat.h"
#include "CHistoryView.h"
#include <iostream>
#include <io.h>
#include <string.h>
using namespace std;

// CHistoryView

IMPLEMENT_DYNCREATE(CHistoryView, CFormView)

CHistoryView::CHistoryView()
	: CFormView(IDD_HISTORY_FORM)
{

}

CHistoryView::~CHistoryView()
{
}

void CHistoryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HISTORY, m_lstHistory);
}

BEGIN_MESSAGE_MAP(CHistoryView, CFormView)
END_MESSAGE_MAP()


// CHistoryView 진단

#ifdef _DEBUG
void CHistoryView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHistoryView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHistoryView 메시지 처리기


void CHistoryView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 리스트 컨트롤에 이미지 연결
	m_imgHistory.Create(48, 48, ILC_COLOR32, 5, 5);
	//m_imgHistory.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	CImage image;
	image.Load(_T("res\\image1.bmp"));
	CBitmap bitmap;
	bitmap.Attach(image.Detach());

	m_imgHistory.Add(&bitmap, RGB(0, 0, 0));

	m_lstHistory.SetImageList(&m_imgHistory, LVSIL_NORMAL);

	m_lstHistory.InsertColumn(0, _T("이름"), LVCFMT_LEFT, 200);
	m_lstHistory.InsertColumn(1, _T("일자"), LVCFMT_LEFT, 100);

	//폴더 내 파일목록 조회
	string path = CT2CA(m_strPath);

	struct _finddata_t fd;	intptr_t handle;
	if ((handle = _findfirst(path.c_str(), &fd)) == -1L) {
		cout << "No file in directory!" << endl;
		MessageBox(_T("파일 없음"));
		return;
	}

	int nRow = 0;
	do
	{
		//if (strstr(fd.name, ".bmp") != NULL || strstr(fd.name, ".png") != NULL) {
		//	m_lstHistory.InsertItem(nRow, fd.name, 0);
		//	nRow++;
		//}
		m_lstHistory.InsertItem(nRow, fd.name, 0);
		nRow++;


	} while (_findnext(handle, &fd) == 0);
	_findclose(handle);
}
