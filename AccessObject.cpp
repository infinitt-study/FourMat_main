#include "stdafx.h"
#include "DrawDoc.h"
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
		if (m_nCurrentFrameNo != m_nRepFrameNo) {
			m_nRepFrameNo = m_nCurrentFrameNo;
		}
		ar << m_nRepFrameNo;

		// 영상처리 맴버변수 저장 추가
	}
	else
	{
		ar >> m_nRepFrameNo;

		// 영상처리 맴버변수 읽기 추가
	}
}


bool CAccessObject::LoadDicomImage(DicomImage* ptrDicomImage, CDrawDoc* pDoc)
{
	//이미지의 폭과 높이를 얻는다 
	int width = (int)ptrDicomImage->getWidth();
	int height = (int)ptrDicomImage->getHeight();
	void* data = nullptr;

	for (int i = 0; i < m_nTotalFrameNo; i++) {
		//프레임의 위치에 있는 영상 정보를 윈도우 이미지 24bit로 생성하여 얻는다 
		ptrDicomImage->createWindowsDIB(data, width * height, i, 24);
		//이미지의 주소를 출력한다

		CFourMatDIB fourMatDIB;
		fourMatDIB.CreateRgbBitmap(width, height, (BYTE*)data);

		m_listDIB.emplace_back(std::move(fourMatDIB));

		m_pageObjects.push_back(new CDrawObjList());

		//이미지의 주소를 메모리 해제 한다
		delete[] data;
		data = nullptr;
	}

	LoadDraw(pDoc);
	SetCurrentFrameNo(-m_nRepFrameNo);

	return true;
}


void CAccessObject::LoadDraw(CDrawDoc* pDoc) {
	CFile file;

	CString strFilePath = pDoc->m_strFolderPath + _T("\\") + m_strFileName;
	if (!m_strFileName.IsEmpty()) {
		if (file.Open(strFilePath, CFile::modeRead | CFile::typeBinary)) {
			CArchive ar(&file, CArchive::load);
			ar.m_pDocument = pDoc;
			size_t size;
			ar >> size;
			if (size == m_pageObjects.size()) { // .drw 받아드림
				for each (auto pDrawObjList in m_pageObjects) {
					pDrawObjList->Serialize(ar);
				}

				Serialize(ar);

			}
			// 사이즈가 다르면 .drw 안받아드림

			ar.Close();
			file.Close();

		}
	}
}

void CAccessObject::SetCurrentFrameNo(int nDelta) 
{
	m_nCurrentFrameNo -= nDelta;
	m_nCurrentFrameNo = long((m_listDIB.size() + m_nCurrentFrameNo) % m_listDIB.size());
	m_pObjects = m_pageObjects[m_nCurrentFrameNo];
}
