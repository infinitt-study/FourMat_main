#pragma once


// CBlurDlg 대화 상자

class CBlurDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBlurDlg)

public:
	CBlurDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBlurDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREEXTRACTION_BLUR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderSigma;
	float m_fSigma;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeSigmaEdit();
};
