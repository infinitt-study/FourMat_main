#include "stdafx.h"
#include "DrawDoc.h"
#include "AccessObject.h"


CAccessObject::CAccessObject()
	: m_strFilePath(_T("")), m_strFileName(_T(""))
	, m_nCurrentFrameNo(0), m_nTotalFrameNo(0), m_nRepFrameNo(0), m_pObjects(NULL)
{
	m_pageObjects.reserve(16); // �����Ͼ�� �ʵ��� �ʱ⼳��
	m_listDIB.reserve(16);
	m_listDIBOrigin.reserve(16);
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
	m_listDIBOrigin.clear();
}

void CAccessObject::Serialize(CArchive& ar) {
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		if (m_nCurrentFrameNo != m_nRepFrameNo) {
			m_nRepFrameNo = m_nCurrentFrameNo;
		}
		ar << m_nRepFrameNo;
	}
	else
	{
		ar >> m_nRepFrameNo;
	}

	m_listDIB[m_nRepFrameNo].Serialize(ar); // ����ó�� ��ȭ�� �κ� ����
}


BOOL CAccessObject::LoadDicomImage(DicomImage* ptrDicomImage, CDrawDoc* pDoc)
{
	//�̹����� ���� ���̸� ��´� 
	int width = (int)ptrDicomImage->getWidth();
	int height = (int)ptrDicomImage->getHeight();
	void* data = nullptr;

	for (int i = 0; i < m_nTotalFrameNo; i++) {
		//�������� ��ġ�� �ִ� ���� ������ ������ �̹��� 24bit�� �����Ͽ� ��´� 
		ptrDicomImage->createWindowsDIB(data, width * height, i, 24);
		//�̹����� �ּҸ� ����Ѵ�

		CFourMatDIB fourMatDIB;
		fourMatDIB.CreateRgbBitmap(width, height, (BYTE*)data);

		m_listDIBOrigin.push_back(fourMatDIB);
		m_listDIB.emplace_back(std::move(fourMatDIB));

		m_pageObjects.push_back(new CDrawObjList());

		//�̹����� �ּҸ� �޸� ���� �Ѵ�
		delete[] data;
		data = nullptr;
	}

	LoadDraw(pDoc);
	SetCurrentFrameNo(-m_nRepFrameNo);

	return true;
}


void CAccessObject::LoadDraw(CDrawDoc* pDoc) {
	CFile file;

	CString strFilePath = pDoc->getFolderPath() + _T("\\") + m_strFileName;
	if (!m_strFileName.IsEmpty()) {
		if (file.Open(strFilePath, CFile::modeRead | CFile::typeBinary)) {
			CArchive ar(&file, CArchive::load);
			ar.m_pDocument = pDoc;
			size_t size;
			ar >> size;
			if (size == m_pageObjects.size()) { // .drw �޾Ƶ帲
				Serialize(ar);

				for each (auto pDrawObjList in m_pageObjects) {
					pDrawObjList->Serialize(ar);
				}
			}
			else {// ����� �ٸ��� .drw ���� ����
				pDoc->SaveDraw(*this);
			}
			ar.Close();
			file.Close();
		}
		else { // .drw ������ ���ٸ� ���� ����
			pDoc->SaveDraw(*this);
		}
	}
}
void CAccessObject::LoadRefDraw(CString filePath, CDrawDoc* pDoc) {
	CFile file;
	CString strFilePath = filePath;

	if (file.Open(strFilePath, CFile::modeRead | CFile::typeBinary)) {
		CArchive ar(&file, CArchive::load);
		ar.m_pDocument = pDoc;

		size_t size;
		ar >> size;
		ar >> m_nRepFrameNo;

		CFourMatDIB fourMatDIB;
		m_listDIB.push_back(fourMatDIB);
		m_listDIB[0].Serialize(ar); // ref �������� ��ǥ�̹����� ���

		ar.Close();
		file.Close();
	}
}

void CAccessObject::SetCurrentFrameNo(int nDelta) 
{
	m_nCurrentFrameNo -= nDelta;
	m_nCurrentFrameNo = long((m_listDIB.size() + m_nCurrentFrameNo) % m_listDIB.size());
	m_pObjects = m_pageObjects[m_nCurrentFrameNo];
}

CString CAccessObject::GetFileDCMName() {
	int nIndex = m_strFileName.ReverseFind(TCHAR('.'));
	return m_strFileName.Left(nIndex);
}

void CAccessObject::DIBInfoDraw(CDC* pDC, CSize& size, CFourMatDIB& dib) {
	CString strFileName = GetFileDCMName();
	CString strPageInfo;
	strPageInfo.Format(_T("%d / %d"), m_nCurrentFrameNo + 1, m_nTotalFrameNo);
	SetTextColor(pDC->m_hDC, RGB(220, 220, 0)); // �۾� �Ͼ�
	SetBkMode(pDC->m_hDC, TRANSPARENT); // ��� ����
	TextOut(pDC->m_hDC, -size.cx / 2 + 5, size.cy / 2 - dib.GetHeight() + 60, strFileName, strFileName.GetLength());
	TextOut(pDC->m_hDC, -size.cx / 2 + 5, size.cy / 2 - dib.GetHeight() + 20, strPageInfo, strPageInfo.GetLength());
}

void CAccessObject::ResetDraw() {
	// �� �ڵ�
	/*BYTE* newDIBits = m_listDIBOrigin[m_nCurrentFrameNo].GetDIBitsAddr();
	m_listDIB[m_nCurrentFrameNo].SetDIBits(newDIBits);*/

	// new deep copy
	std::async([this] {
		// �����ؾ��� �ڵ带 �ۼ�
		BYTE* newDIBits = this->m_listDIBOrigin[this->m_nCurrentFrameNo].GetDIBitsAddr();
		this->m_listDIB[this->m_nCurrentFrameNo].SetDIBits(newDIBits);
		});
	/*
	����ó�� �ʱ�ȭ �κ� -> CFOURMATDIB ������ ����ؼ�
	���α׷��� �����ϴ� ���ȿ� ���������� origin������ ������
	- future, promise �̰� �ΰ� ��� async�ȿ� �������� -> ������ ���� �ʿ���� async�� ����ϸ� ��
	- async(STL)

	*/
}