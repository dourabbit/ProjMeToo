#ifndef _TEST_HPP
#define _TEST_HPP

#include <Data/image.hpp>

#include <string>
namespace Writer{	
	
class TiffWriter{
public:

	TiffWriter();
	~TiffWriter();
	int Write(const Data::ImageData* img, std::string outputPath);
  };
}

#endif