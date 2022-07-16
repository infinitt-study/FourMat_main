#include "stdafx.h"
#include "CMorphology.h"
#include "CImprovement.h"

#include <map>


void MorphologyErosion(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			if (pSrc[j][i] != 0)
			{
				if (pSrc[j - 1][i] == 0 || pSrc[j - 1][i + 1] == 0 ||
					pSrc[j][i - 1] == 0 || pSrc[j][i + 1] == 0 ||
					pSrc[j + 1][i - 1] == 0 || pSrc[j + 1][i] == 0 ||
					pSrc[j + 1][i + 1] == 0 || pSrc[j - 1][i - 1] == 0)
				{
					pDst[j][i] = 0;
				}
			}
		}
}

void MorphologyDilation(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			if (pSrc[j][i] == 0)
			{
				if (pSrc[j - 1][i] != 0 || pSrc[j - 1][i + 1] != 0 ||
					pSrc[j][i - 1] != 0 || pSrc[j][i + 1] != 0 ||
					pSrc[j + 1][i - 1] != 0 || pSrc[j + 1][i] != 0 ||
					pSrc[j + 1][i + 1] != 0 || pSrc[j - 1][i - 1] != 0)
				{
					pDst[j][i] = 255;
				}
			}
		}
}

void MorphologyOpening(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyErosion(imgSrc, imgTmp);
	MorphologyDilation(imgTmp, imgDst);
}

void MorphologyClosing(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyDilation(imgSrc, imgTmp);
	MorphologyErosion(imgTmp, imgDst);
}

void MorphologyGrayErosion(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j, m, n, x, y, pmin;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pmin = 255;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x] < pmin)
							pmin = pSrc[y][x];
					}
				}

			pDst[j][i] = pmin;
		}
}

void MorphologyGrayDilation(ByteImage& imgSrc, ByteImage& imgDst)
{
	int i, j, m, n, x, y, pmax;
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pDst = imgDst.GetPixels2D();
	BYTE** pSrc = imgSrc.GetPixels2D();

	for (j = 0; j < h; j++)
		for (i = 0; i < w; i++)
		{
			pmax = 0;

			for (n = -1; n <= 1; n++)
				for (m = -1; m <= 1; m++)
				{
					x = i + m;
					y = j + n;

					if (x >= 0 && x < w && y >= 0 && y < h)
					{
						if (pSrc[y][x] > pmax)
							pmax = pSrc[y][x];
					}
				}

			pDst[j][i] = pmax;
		}
}

void MorphologyGrayOpening(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyGrayErosion(imgSrc, imgTmp);
	MorphologyGrayDilation(imgTmp, imgDst);
}

void MorphologyGrayClosing(ByteImage& imgSrc, ByteImage& imgDst)
{
	ByteImage imgTmp;
	MorphologyGrayDilation(imgSrc, imgTmp);
	MorphologyGrayErosion(imgTmp, imgDst);
}

