#pragma once


// CScalingDlg 대화 상자

class CScalingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScalingDlg)

public:
	CScalingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CScalingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_SCALING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nOldWidth;
	int m_nOldHeight;
	int m_nNewWidth;
	int m_nNewHeight;
	BOOL m_bAspectRatio;
	int m_nInterpolation;
	afx_msg void OnEnChangeNewWidth();
	afx_msg void OnEnChangeNewHeight();
	afx_msg void OnBnClickedAspectRatio();
	virtual BOOL OnInitDialog();
};
