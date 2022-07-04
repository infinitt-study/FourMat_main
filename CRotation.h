#pragma once


// CRotation 대화 상자

class CRotation : public CDialogEx
{
	DECLARE_DYNAMIC(CRotation)

public:
	CRotation(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CRotation();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_ROTATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nRotate;
	float m_fAngle;
	virtual BOOL OnInitDialog();
};
