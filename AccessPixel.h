#pragma once
#include <memory.h>
#include "RGBBYTE.h"


template<typename T>
class AccessPixel // �پ��� �ڷ����� image 
{
protected:
	int     width;  // ������ ���� ũ�� (�ȼ� ����)
	int     height; // ������ ���� ũ�� (�ȼ� ����)
	T** pixels; // �ȼ� ������

public:
	// �����ڿ� �Ҹ���
	AccessPixel();
	AccessPixel(int w, int h);
	AccessPixel(const AccessPixel<T>& img);
	~AccessPixel();

	// �̹��� ������ �Ҹ�
	void    CreateImage(int w, int h);
	void    DestroyImage();

	// �ȼ� �� ����
	T* GetPixels()   const {
		if (pixels) return pixels[0];
		else return NULL;
	}// 1���� �ȼ� ����  
	T** GetPixels2D() const { return pixels; } // 2���� �ȼ��� ����  

	// ���� ������ ������
	AccessPixel<T>& operator=(const AccessPixel<T>& img); //operator ����   

	// �ȼ� �� ����
	template<typename U> void Convert(const AccessPixel<U>& img, bool use_limit = false);

	// ���� ���� ��ȯ
	int     GetWidth()    const { return width; } // �� ���� 
	int     GetHeight()   const { return height; } // ���� ����  
	int     GetSize()     const { return width * height; } // ���� ���� �ȼ� ������ �����ǰ�? 
	bool    IsValid()     const { return (pixels != NULL); } //�ȼ� ���� �ִ°�  ?  
};

template<typename T>
AccessPixel<T>::AccessPixel()
	:width(0), height(0), pixels(NULL)  // �ȼ� ���� ���� �� 
{
}

template<typename T>
AccessPixel<T>::AccessPixel(int w, int h)
	: width(w), height(h), pixels(NULL)
{
	pixels = new T * [sizeof(T*) * height]; // �ȼ��� ���� �� 
	pixels[0] = new T[sizeof(T) * width * height]; // 2d �̹��� �ȼ� �� ���� 

	for (int i = 1; i < height; i++)
		pixels[i] = pixels[i - 1] + width; 

	memset(pixels[0], 0, sizeof(T) * width * height); // �ȼ� �� �ʱ�ȭ
}

template<class T>
AccessPixel<T>::AccessPixel(const AccessPixel<T>& img) //�ȼ� ���� ���� ���� ������ 
	: width(img.width), height(img.height), pixels(NULL)
{
	if (img.IsValid()) {
		pixels = new T * [sizeof(T*) * height];
		pixels[0] = new T[sizeof(T) * width * height];

		for (int i = 1; i < height; i++)
			pixels[i] = pixels[i - 1] + width;

		memcpy(pixels[0], img.pixels[0], sizeof(T) * width * height); // �ȼ� �� ����
	}
}

template<typename T>
AccessPixel<T>::~AccessPixel() //�Ҹ��� 
{
	if (pixels != NULL) {
		delete[] pixels[0]; // �޸� ���� 
		delete[] pixels;
	}
}

template<typename T>
void AccessPixel<T>::CreateImage(int w, int h)
{
	DestroyImage();// �ʱ�ȭ 

	width = w;
	height = h; // ���̿� ���� ��´�. 

	pixels = new T * [sizeof(T*) * height]; // ���̿� ���� ũ�⸦ �Ҵ� ? 
	pixels[0] = new T[sizeof(T) * width * height]; // ���̿� ���� ũ�⸦ �Ҵ� 

	for (int i = 1; i < height; i++)
		pixels[i] = pixels[i - 1] + width; //�ȼ� ��ü  ���? 

	memset(pixels[0], 0, sizeof(T) * width * height); // �ȼ� �� �ʱ�ȭ
}

template<typename T>
void AccessPixel<T>::DestroyImage() // �ȼ� �� �ʱ�ȭ 
{
	if (pixels != NULL) {
		delete[] pixels[0];
		delete[] pixels;
		pixels = NULL;
	}

	width = height = 0;
}

template<typename T>
AccessPixel<T>& AccessPixel<T>::operator=(const AccessPixel<T>& img)
{
	if (this == &img)
		return *this;

	CreateImage(img.width, img.height); // �̹��� �ȼ����� �ش� �ּҿ�  ���� �����ͷ� ���� �Ѵ�. 
	memcpy(pixels[0], img.pixels[0], sizeof(T) * width * height); // �ȼ��� �ʱ�ȭ 

	return *this;
}

template<typename T> template<typename U>
void AccessPixel<T>::Convert(const AccessPixel<U>& img, bool use_limit)
{
	CreateImage(img.GetWidth(), img.GetHeight()); // �̹����� ���̿� ���� ��´�. 

	int size = GetSize(); //���� * �� 
	T* p1 = GetPixels(); // 1���� �ȼ� �� ��� 
	U* p2 = img.GetPixels(); // �̹����� �ȼ��� ��� 

	if (use_limit)
		for (int i = 0; i < size; i++) 
			p1[i] = static_cast<T>(limit(p2[i])); // ??? 
	else
		for (int i = 0; i < size; i++)
			p1[i] = static_cast<T>(p2[i]);
}

// �پ��� �ڷ����� ���� GetPixel ����

typedef AccessPixel<BYTE>    ByteImage;
typedef AccessPixel<int>     IntImage;
typedef AccessPixel<float>   FloatImage;
typedef AccessPixel<double>  DoubleImage;
typedef AccessPixel<RGBBYTE> RgbImage;

template<typename T>
inline T limit(const T& value)
{
	return ((value > 255) ? 255 : ((value < 0) ? 0 : value)); // �ȼ� �� 0< value < 255 
}