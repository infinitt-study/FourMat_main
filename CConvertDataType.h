#pragma once
#include "AccessPixel.h"
#include "CFourMatDIB.h"

void FourMatDIBToImage(CFourMatDIB& dib, ByteImage& img);
void FourMatDIBToRgbImage(CFourMatDIB& dib, RgbImage& img);
void FourMatDIBToByteImage(const CFourMatDIB& dib, ByteImage& img);
void FourMatDIBToFloatImage(const CFourMatDIB& dib, FloatImage& img);
void FourMatGrayToDIBImage(const ByteImage& img, CFourMatDIB& dib);

void ByteImageToFourMatDIB(ByteImage& img, CFourMatDIB& dib);
void FloatImageToFourMatDIB(FloatImage& img, CFourMatDIB& dib);
void RgbImageToFourMatDIB(RgbImage& img, CFourMatDIB& dib);


