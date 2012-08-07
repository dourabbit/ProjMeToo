#ifndef _IMAGEWRITER_HPP
#define _IMAGEWRITER_HPP

#include <Data/image.hpp>

namespace Writer{	
	
class ImageWriter{
public:

	enum WRITETYPE {_TIFF,_JPG};
	ImageWriter();
	virtual ~ImageWriter();
	WRITETYPE type;
	virtual int Write(Data::ImageData &img)=0;
  };
}

#endif