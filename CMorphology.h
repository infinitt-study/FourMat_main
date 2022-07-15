#pragma once
//#include "stdafx.h"
//#include <vector>
//#include "AccessPixel.h"
//#include "Feature.h"
//
//class LabelInfo
//{
//public:
//	std::vector<Point> pixels;
//	int cx, cy;
//	int minx, miny, maxx, maxy;
//
//public:
//	LabelInfo() : cx(0), cy(0), minx(9999), miny(9999), maxx(0), maxy(0)
//	{
//		pixels.clear();
//	}
//};
//
////void Binarization(ByteImage& imgSrc, ByteImage& imgDst, int threshold);
////int  BinarizationIterative(ByteImage& imgSrc);
////
////int  Labeling(ByteImage& imgSrc, IntImage& imgDst, std::vector<LabelInfo>& labels);
////
////void ContourTracing(ByteImage& imgSrc, int sx, int sy, std::vector<Point>& cp);
//
//void MorphologyErosion(ByteImage& imgSrc, ByteImage& imgDst);
//void MorphologyDilation(ByteImage& imgSrc, ByteImage& imgDst);
//void MorphologyOpening(ByteImage& imgSrc, ByteImage& imgDst);
//void MorphologyClosing(ByteImage& imgSrc, ByteImage& imgDst);
//
//void MorphologyGrayErosion(ByteImage& imgSrc, ByteImage& imgDst);
//void MorphologyGrayDilation(ByteImage& imgSrc, ByteImage& imgDst);
//void MorphologyGrayOpening(ByteImage& imgSrc, ByteImage& imgDst);
//void MorphologyGrayClosing(ByteImage& imgSrc, ByteImage& imgDst);