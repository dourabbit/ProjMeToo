//
//  ImgWriter.h
//  ___PROJECTNAME___
//
//  Created by Chengfu on 12-11-30.
//
//

#ifndef _____PROJECTNAME_____ImgWriter__
#define _____PROJECTNAME_____ImgWriter__

#include <iostream>
#include <string.h>
#include <common.h>
#include <CImg.h>
class ImgWriter{
public:
    ImgWriter();
    ~ImgWriter();
    ImgWriter(std::string path,std::string fileNm);
    int Write(const cimg_library::CImg<ImgDATA>* cimg);
    int Write(const void* data);
private:
    
};

#endif /* defined(_____PROJECTNAME_____ImgWriter__) */
