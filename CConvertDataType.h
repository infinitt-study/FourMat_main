#pragma once
#include "AccessPixel.h"
#include "CFourMatDIB.h"

void FourMatDIBToImage(CFourMatDIB& dib, ByteImage& img);
void FourMatDIBToImage(CFourMatDIB& dib, RgbImage& img);
void FourMatDIBToGrayImage(CFourMatDIB& dib, ByteImage& img);

void ImageToFourMatDIB(ByteImage& img, CFourMatDIB& dib);
void ImageToFourMatDIB(FloatImage& img, CFourMatDIB& dib);
void ImageToFourMatDIB(RgbImage& img, CFourMatDIB& dib);

