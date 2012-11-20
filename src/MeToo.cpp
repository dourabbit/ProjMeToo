// MeToo.cpp : Defines the entry point for the console application.
//
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "stdafx.h"
#include <common.h>

#include <Data/image.hpp>
#include <Writer/imageWriter.hpp>
#include <Writer/tiffWriter.h>
using namespace Data;
using namespace Writer;
//int main(int argc, _TCHAR* argv[])
//{


	//Test Tiff
	//int width = 144;
	//int height = 25;
	//IMGDATA* pRaw = &_testBuffer[0];
	////TiffWriter* pWriter = new TiffWriter();
	//TiffWriter* t = new TiffWriter();
	//ImageData* imgData = new ImageData(width,height,pRaw);
	//std::string outputPath = "RenderOutput.tif";
	//t->Write(imgData,outputPath);
	////ImageWriter* p = new ImageWriter();
	//return 0;
//}

