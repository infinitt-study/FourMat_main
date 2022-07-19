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
	// m_pageLeftObjects, m_pageRightObjects
	CDrawObjList* m_pObjects;
	// m_pObjects, m_pRightObjects

	CString m_strFilePath;
	CString m_strFileName;
	// m_strFilePath, m_strRightFilePath

	std::vector <CFourMatDIB> m_listDIB;
	//m_listLeftDIB, m_listRightDIB

	// m_nCurrentFrameNo, m_nCurrentRightFrameNo
	long m_nCurrentFrameNo; // ������ ���� �̹��� ����������
	long m_nTotalFrameNo; // ������ ���� �̹��� ��ü������
	long m_nRepFrameNo; // ������ ���� ��ǥ �̹���


	bool LoadDicomImage(DicomImage* ptrDicomImage, CDrawDoc* pDoc);
	void LoadDraw(CDrawDoc* pDoc);
	void SetCurrentFrameNo(int nDelta);

	// ����ó�� �ɹ����� �߰� ���� �ʿ�
};

typedef CAccessObject DrawObjInfo;
// LeftDrawObj RightDrawObj