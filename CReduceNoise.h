#pragma once


// CReduceNoise 대화 상자

class CReduceNoise : public CDialogEx
{
	DECLARE_DYNAMIC(CReduceNoise)

public:
	CReduceNoise(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CReduceNoise();

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
};
