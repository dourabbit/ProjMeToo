//
//  ImgWriter.cpp
//  ___PROJECTNAME___
//
//  Created by Chengfu on 12-11-30.
//
//

#include "ImgWriter.hpp"
#include <string>
//#include <common.h>



ImgWriter::ImgWriter(){

};

ImgWriter::~ImgWriter(){

};

int ImgWriter::Write(const void* data){

    unsigned buf_size = 500000; // Put the file size here !//??????????????
    
    
    ImgData* imgData = (ImgData*)data;
    
    CImg<unsigned char> img;
    std::fprintf(stderr," - Do simple processing\n");
    const unsigned char purple[] = { 255, 0, 0 };
    const unsigned char black[] = { 0, 0, 0 };
    img.mirror('y').draw_text(0,0,"   Hello!   ",purple,black,1,57);
    
    // Display image to see if everything's fine.
    //img.display("Using 'jpeg_buffer.h' plugin");
    
    // Define a new JOCTET array where the processed image has to be saved
    // (we don't know its dimension before compressing it, therefore we have to allocate enough memory )
    std::fprintf(stderr," - Construct output JPEG-coded buffer\n");
    JOCTET *buffer_output = new JOCTET[2*buf_size];
    
    // Save processed image into this JOCTET buffer, compressed as jpeg.
    // This is done again by using the plug-in function.
    img.save_jpeg_buffer(buffer_output,buf_size,60);
    // Note that here, the variable 'buf_size' contains the length of the
    // data which have been written in the given output buffer.
    
    // Copy the content of the above array into a new file
    // (it should give you a valid JPEG file then !)
    const char *filename_output = ((std::string *)data)->c_str();
    std::fprintf(stderr," - Save output file '%s'\n",filename_output);
    std::FILE* file_output = std::fopen(filename_output,"wb");
    std::fwrite(buffer_output, sizeof(JOCTET), buf_size, file_output);
    std::fclose(file_output);
    delete[] buffer_output;
    
    std::fprintf(stderr," - All done !\n");
    return 0;

}