#pragma once

//#include "drawvw.h"
// CSlice 대화 상자

class CSlice : public CDialogEx
{
	DECLARE_DYNAMIC(CSlice)

public:
	CSlice(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSlice();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_SLICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
