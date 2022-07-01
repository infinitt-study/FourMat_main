#pragma once
#include <afx.h>
class CFileFindEx :
    public CFileFind
{
public:
    CFileFindEx(void);
    ~CFileFindEx(void);
    CString GetLengthString();                           // 파일의 크기를 스트링으로 넘겨줌
    CString GetCreationTimeString(CString strTmp = "-"); // 파일 생성 시간을 스트링으로 넘겨줌
};

