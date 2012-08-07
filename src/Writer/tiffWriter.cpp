#include <stdio.h>
#include <3rdParty/tiff-3.9.4/tiffio.h>
#include <Writer/tiffWriter.h>
using namespace Writer;
TiffWriter::TiffWriter(){
	printf("\n\nResult: \n");
};



int TiffWriter::Write(const Data::ImageData* img,std::string outputPath){
  
  TIFF *imageOutput = NULL;
  // Open the TIFF file
  if((imageOutput = TIFFOpen(outputPath.c_str(), "w"))  == NULL){
    printf("Could not open output.tif for writing\n");
    return 0; //exit(42);
  }

  // We need to set some values for basic tags before we can add any data
  TIFFSetField(imageOutput, TIFFTAG_IMAGEWIDTH, 25 * 8);
  TIFFSetField(imageOutput, TIFFTAG_IMAGELENGTH, 144);
  TIFFSetField(imageOutput, TIFFTAG_BITSPERSAMPLE, 1);
  TIFFSetField(imageOutput, TIFFTAG_SAMPLESPERPIXEL, 1);
  TIFFSetField(imageOutput, TIFFTAG_ROWSPERSTRIP, 144);

  TIFFSetField(imageOutput, TIFFTAG_COMPRESSION, COMPRESSION_CCITTFAX4);
  TIFFSetField(imageOutput, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISWHITE);
  TIFFSetField(imageOutput, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
  TIFFSetField(imageOutput, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

  TIFFSetField(imageOutput, TIFFTAG_XRESOLUTION, 150.0);
  TIFFSetField(imageOutput, TIFFTAG_YRESOLUTION, 150.0);
  TIFFSetField(imageOutput, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);
  
  // Write the information to the file
  TIFFWriteEncodedStrip(imageOutput, 0, img->pRawImg, 25 * 144);

  // Close the file
  TIFFClose(imageOutput);
}