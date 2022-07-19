#pragma once

#include <windows.h>

class CFourMatDIB : public CObject 
{
public:
	// �����ڿ� �Ҹ���
	CFourMatDIB();
	CFourMatDIB(const CFourMatDIB& dib);
	CFourMatDIB(CFourMatDIB&& dib);
	~CFourMatDIB();

	// ��Ʈ�� ������ �Ҹ�
	BOOL CreateGrayBitmap(LONG nWidth, LONG nHeight);
	BOOL CreateRgbBitmap(LONG nWidth, LONG nHeight);
	BOOL CreateRgbBitmap(LONG nWidth, LONG nHeight, BYTE* pImageData);
	void DestroyBitmap();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o

	
	// ��Ʈ�� ȭ�� ���
	void Draw(HDC hdc, int dx = 0, int dy = 0);
	void Draw(HDC hdc, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);
	void Draw(HDC hdc, int dx, int dy, int dw, int dh, int sx, int sy, int sw,
		int sh, DWORD dwRop = SRCCOPY);

	// Windows ȯ�濡�� Ŭ������� �����ϱ� �� �ٿ��ֱ�
	BOOL CopyToClipboard();
	BOOL PasteFromClipboard();

	// ���� ������ ������
	CFourMatDIB& operator=(const CFourMatDIB& dib);

	// ��Ʈ�� ���� ��ȯ
	LONG        GetWidth()    const { return m_nWidth; }
	LONG        GetHeight()	  const { return m_nHeight; }
	WORD        GetBitCount() const { return m_nBitCount; }
	DWORD       GetDibSize()  const { return m_nDibSize; }
	LPBITMAPINFO GetBitmapInfoAddr() const { return (LPBITMAPINFO)m_pDib; }
	BYTE*		GetDIBitsAddr() const;
	int         GetPaletteNums() const;
	BOOL        IsValid() const { return (m_pDib != NULL); }

	// �̹��� �缳��
	void SetDIBits(BYTE* m_pDib);
	
private:
	LONG    m_nWidth;      // ��Ʈ�� ���� ũ�� (�ȼ� ����)
	LONG    m_nHeight;     // ��Ʈ�� ���� ũ�� (�ȼ� ����)
	WORD    m_nBitCount;   // �ȼ� �� ��Ʈ ��
	DWORD   m_nDibSize;    // DIB ��ü ũ�� (BITMAPINFOHEADER + ���� ���̺� + �ȼ� ������)
	BYTE* m_pDib;        // DIB ���� �ּ� (BITMAPINFOHEADER ���� �ּ�)
};

