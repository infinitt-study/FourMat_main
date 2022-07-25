#pragma once


#include "drawobj.h"
#include "CFourMatDIB.h"


class CAccessObject : public CObject
{

public:
	CAccessObject();
	~CAccessObject();

	void Serialize(CArchive& ar);

public:
	std::vector<CDrawObjList*> m_pageObjects;

	CDrawObjList* m_pObjects;

	CString m_strFilePath;
	CString m_strFileName;

	std::vector <CFourMatDIB> m_listDIB;
	std::vector <CFourMatDIB> m_listDIBOrigin;

	long m_nCurrentFrameNo; // ������ ���� �̹��� ����������
	long m_nTotalFrameNo; // ������ ���� �̹��� ��ü������
	long m_nRepFrameNo; // ������ ���� ��ǥ �̹���


	BOOL LoadDicomImage(DicomImage* ptrDicomImage, CDrawDoc* pDoc);
	void LoadDraw(CDrawDoc* pDoc);
	void LoadRefDraw(CString filePath, CDrawDoc* pDoc);

	void SetCurrentFrameNo(int nDelta);

	CString GetFileDCMName();

	void DIBInfoDraw(CDC* pDC, CSize& size, CFourMatDIB& dib);
	void ResetDraw();

	BOOL IsFrameChanged() const {
		return (m_nCurrentFrameNo != m_nRepFrameNo);
	}

	// ����ó�� �ɹ����� �߰� ���� �ʿ�
};

//typedef CAccessObject DrawObjInfo;
// LeftDrawObj RightDrawObj

using CAccessObjectPtr = std::shared_ptr<CAccessObject>;