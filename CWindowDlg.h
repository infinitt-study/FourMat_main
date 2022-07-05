#pragma once


// CWindowDlg 대화 상자

class CWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWindowDlg)

public:
	CWindowDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CWindowDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERING_WINDOW_LEVEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderWindow;
	int m_nWindow;
	CSliderCtrl m_sliderLevel;
	int m_nLevel;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
