#pragma once

//#include "drawvw.h"
// CSliceDlg 대화 상자

class CSliceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSliceDlg)

public:
	CSliceDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSliceDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_SLICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
