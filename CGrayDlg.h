#pragma once


// CGrayDlg 대화 상자

class CGrayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGrayDlg)

public:
	CGrayDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGrayDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERING_GRAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderGray;
	int m_nGray;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
