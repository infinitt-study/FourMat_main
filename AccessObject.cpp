#include "stdafx.h"
#include "AccessObject.h"


CAccessObject::CAccessObject()
	: m_strFilePath(_T("")), m_strFileName(_T(""))
	, m_nCurrentFrameNo(0), m_nTotalFrameNo(0), m_nRepFrameNo(0), m_pObjects(NULL)
{
	m_pageObjects.reserve(16); // 복제일어나지 않도록 초기설정
	m_listDIB.reserve(16);
}

CAccessObject::~CAccessObject() {
	for (auto& pObjects : m_pageObjects) {
		POSITION pos = pObjects->GetHeadPosition();
		while (pos != NULL)
			delete pObjects->GetNext(pos);
		pObjects->RemoveAll();
		delete pObjects;
	}
	m_pageObjects.clear();

	m_pObjects = NULL;

	m_listDIB.clear();

}

void CAccessObject::Serialize(CArchive& ar) {
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		//ar << m_position;
		//ar << (WORD)m_bPen;
		//ar.Write(&m_logpen, sizeof(LOGPEN));
		//ar << (WORD)m_bBrush;
		//ar.Write(&m_logbrush, sizeof(LOGBRUSH));

		ar << m_nRepFrameNo;

		// 영상처리 맴버변수 저장 추가
	}
	else
	{
		//WORD wTemp;
		//ar >> m_position;
		//ar >> wTemp; m_bPen = (BOOL)wTemp;
		//ar.Read(&m_logpen, sizeof(LOGPEN));
		//ar >> wTemp; m_bBrush = (BOOL)wTemp;
		//ar.Read(&m_logbrush, sizeof(LOGBRUSH));

		ar >> m_nRepFrameNo;

		// 영상처리 맴버변수 읽기 추가
	}
}