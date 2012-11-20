#include <Data/image.hpp>

using namespace Data;
ImageData::ImageData(int &width, int &height,IMGDATA* pRaw):pRawImg(pRaw){
	this->width = width;
	this->height = height;
}

ImageData::~ImageData(){

	delete[] this->pRawImg;
}
	
