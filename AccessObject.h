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
	std::vector <CFourMatDIB> m_listDIBOrigin;
	//m_listLeftDIB, m_listRightDIB

	// m_nCurrentFrameNo, m_nCurrentRightFrameNo
	long m_nCurrentFrameNo; // 다이콤 내부 이미지 현재페이지
	long m_nTotalFrameNo; // 다이콤 내부 이미지 전체페이지
	long m_nRepFrameNo; // 다이콤 내부 대표 이미지


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

	// 영상처리 맴버변수 추가 설정 필요
};

//typedef CAccessObject DrawObjInfo;
// LeftDrawObj RightDrawObj

using CAccessObjectPtr = std::shared_ptr<CAccessObject>;