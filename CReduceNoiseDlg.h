#pragma once


// CReduceNoiseDlg 대화 상자

class CReduceNoiseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReduceNoiseDlg)

public:
	CReduceNoiseDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CReduceNoiseDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FEATUREEXTRACTION_REDUCENOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	float m_fLambda;
	float m_fK;
	int m_nIteration;
//	afx_msg void OnPaint();
};
