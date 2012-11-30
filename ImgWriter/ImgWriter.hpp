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
using namespace cimg_library;
class ImgWriter{
public:
    ImgWriter();
    ~ImgWriter();
    //int  Write(const CImg<ImgDATA>* cimg);
    static int SDLCALL Write(const void* data);
    static CImg<ImgDATA> convert2Img();
    static std::string fileNm;
private:
    
};

#endif /* defined(_____PROJECTNAME_____ImgWriter__) */