#pragma once


// CTranslationDlg 대화 상자

class CTranslationDlg : public CDialogEx // dlg이름 변경 
{
	DECLARE_DYNAMIC(CTranslationDlg)

public:
	CTranslationDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTranslationDlg();
	//void Translate(ByteImage& imgSrc, ByteImage& imgDst, int sx, int sy)
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AFFINETRANSFORM_TRANSLATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nNewSX;
	int m_nNewSY;
};
