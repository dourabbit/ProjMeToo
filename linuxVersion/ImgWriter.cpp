//
//  ImgWriter.cpp
//  ___PROJECTNAME___
//
//  Created by Chengfu on 12-11-30.
//
//

#include "ImgWriter.hpp"
#include "worker.hpp"

// Define plugin and include the CImg Library.
#define cimg_plugin "plugins/jpeg_buffer.h"
#include "CImg.h"
using namespace cimg_library;

//#include "gridfsTest.hpp"

ImgWriter::ImgWriter(){

};

ImgWriter::~ImgWriter(){

};

int ImgWriter::Write(const Block* data){
//    const Block* block = (Block*) data;
//    unsigned buf_size = 500000; // Put the file size here !
//
//    unsigned char* data_buffer = new unsigned char [2*2*3];
//    memset(data_buffer,'\0',2*2*3);
//    
//    int i=0;
//    
//    //R
//    for(int x =0;x<4;x++){
//        //R
//        *(data_buffer+x) = 0;
//        //G
//        *(data_buffer+4+x) = 255;
//        //B
//        *(data_buffer+8+x) = 0;
//    }
//    
//    CImg<unsigned char> img(data_buffer,2,2,1,3,false);;    
//    
//    std::fprintf(stderr," - Construct output JPEG-coded buffer\n");
//    JOCTET *buffer_output = new JOCTET[2*buf_size];
//    
//    img.save_jpeg_buffer(buffer_output,buf_size,100);
//    const char *filename_output = block->blockNm.c_str();
//    std::fprintf(stderr," - Save output file '%s'\n",filename_output);
//    std::FILE* file_output = std::fopen(filename_output,"wb");
//    std::fwrite(buffer_output, sizeof(JOCTET), buf_size, file_output);
//    std::fclose(file_output);
//    delete[] buffer_output;
//    
//    
//    
//    
//    
//    return 0;
    const Block* block = (Block*) data;
    unsigned int buf_size = 500000;
    JOCTET *buffer_output = new JOCTET[buf_size];
    
    string a = block->blockNm;
    CImg<unsigned char> img(block->_buffer,block->width,block->height,1,3,true);
    img.save_jpeg_buffer(buffer_output,buf_size,100);
    const char *filename_output = block->blockNm.c_str();
    std::fprintf(stderr," - Save output file '%s'\n",filename_output);
    std::FILE* file_output = std::fopen(filename_output,"wb");
    std::fwrite(buffer_output, sizeof(JOCTET), buf_size, file_output);
    std::fclose(file_output);
    delete[] buffer_output;
    
    std::fprintf(stderr," - All done !\n");
    
   // gridfs* file = new gridfs();
   // file->save();
    
    
    return 0;

}