#pragma once


// CTransformation 대화 상자

class CTransformation : public CDialogEx
{
	DECLARE_DYNAMIC(CTransformation)

public:
	CTransformation(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTransformation();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_TRANSFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nNewSX;
	int m_nNewSY;
};
