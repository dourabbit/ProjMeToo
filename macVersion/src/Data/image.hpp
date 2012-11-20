#ifndef _IMAGE_HPP
#define _IMAGE_HPP
	

#include <common.h>

namespace Data{
class ImageData{
public:
	int height;
	int width;
	
	IMGDATA* pRawImg;

	ImageData(int &width, int &height,IMGDATA* pRaw);
	~ImageData();
};
}
#endif