#include "stdafx.h"
//#include "CFilterMedian.h"
//#include <algorithm>
//void FilterMedian(ByteImage& imgSrc, ByteImage& imgDst)
//{
//	int w = imgSrc.GetWidth();
//	int h = imgSrc.GetHeight();
//	imgDst = imgSrc;
//	BYTE** pSrc = imgSrc.GetPixels2D();
//	BYTE** pDst = imgDst.GetPixels2D();
//	int i, j;
//	BYTE m[9];
//	for (j = 1; j < h - 1; j++)
//		for (i = 1; i < w - 1; i++)
//		{
//			m[0] = pSrc[j - 1][i - 1]; m[1] = pSrc[j - 1][i]; m[2] = pSrc[j - 1][i +
//				1];
//			m[3] = pSrc[j][i - 1]; m[4] = pSrc[j][i]; m[5] = pSrc[j][i + 1];
//			m[6] = pSrc[j + 1][i - 1]; m[7] = pSrc[j + 1][i]; m[8] = pSrc[j + 1][i +
//				1];
//			std::sort(m, m + 9);
//			pDst[j][i] = m[4];
//		}
//}