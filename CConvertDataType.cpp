#include "stdafx.h"
#include "CConvertDataType.h"

void FourMatDIBToImage(CFourMatDIB& dib, ByteImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 8);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w + 3) & ~3;
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	BYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w);
	}
}

void FourMatDIBToImage(CFourMatDIB& dib, RgbImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w * 3 + 3) & ~3;
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	RGBBYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		memcpy(pixels[i], &pDIBits[(h - 1 - i) * ws], w * 3);
	}
}

void FourMatDIBToGrayImage(const CFourMatDIB& dib, ByteImage& img)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws1 = (w + 3) & ~3;
	int ws2 = (w * 3 + 3) & ~3;
	BYTE* pDIBits = dib.GetDIBitsAddr();

	img.CreateImage(w, h);
	BYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		for (int j=0;j<w;j++) {
			pixels[i][j] = byte(0.3 * pDIBits[(h - 1 - i) * ws2 + j * 3] +
				0.59 * pDIBits[(h - 1 - i) * ws2 + j * 3 + 1] +
				0.11 * pDIBits[(h - 1 - i) * ws2 + j * 3 + 2]);
		}
	}
}

void FourMatGrayToDIBImage(const ByteImage& img, CFourMatDIB& dib)
{
	assert(dib.IsValid());
	assert(dib.GetBitCount() == 24);

	int w = dib.GetWidth();
	int h = dib.GetHeight();
	int ws = (w * 3 + 3) & ~3;
	BYTE* pDIBits = dib.GetDIBitsAddr();
	BYTE** pixels = img.GetPixels2D();

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++) {
			pDIBits[(h - 1 - i) * ws + j * 3 + 0] = pixels[i][j];
			pDIBits[(h - 1 - i) * ws + j * 3 + 1] = pixels[i][j];
			pDIBits[(h - 1 - i) * ws + j * 3 + 2] = pixels[i][j];
		}
	}
}

void ImageToFourMatDIB(ByteImage& img, CFourMatDIB& dib)
{
	assert(img.IsValid());

	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w + 3) & ~3;
	BYTE** pixels = img.GetPixels2D();

	dib.CreateGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int i = 0; i < h; i++)
	{
		memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w);
	}
}

void ImageToFourMatDIB(FloatImage& img, CFourMatDIB& dib)
{
	assert(img.IsValid());

	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w + 3) & ~3;
	float** pixels = img.GetPixels2D();

	dib.CreateGrayBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	int i, j;
	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pDIBits[(h - 1 - j) * ws + i] = static_cast<BYTE>(limit(pixels[j][i] + 0.5f));
		}
}

void ImageToFourMatDIB(RgbImage& img, CFourMatDIB& dib)
{
	assert(img.IsValid());

	int w = img.GetWidth();
	int h = img.GetHeight();
	int ws = (w * 3 + 3) & ~3;
	RGBBYTE** pixels = img.GetPixels2D();

	dib.CreateRgbBitmap(w, h);
	BYTE* pDIBits = dib.GetDIBitsAddr();

	for (int i = 0; i < h; i++)
	{
		memcpy(&pDIBits[(h - 1 - i) * ws], pixels[i], w * 3);
	}
}
