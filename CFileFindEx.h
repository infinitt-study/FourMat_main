#pragma once
#include <afx.h>
class CFileFindEx :
    public CFileFind
{
public:
    CFileFindEx(void);
    ~CFileFindEx(void);
    CString GetLengthString();                           // ������ ũ�⸦ ��Ʈ������ �Ѱ���
    CString GetCreationTimeString(CString strTmp = "-"); // ���� ���� �ð��� ��Ʈ������ �Ѱ���
};

