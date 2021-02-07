#pragma once

#ifndef RESIMSTRUCTS_H
#define RESIMSTRUCTS_H
#endif // !RESIMSTRUCTS_H

// COLOR TYPES
#define PNG_GREYSCALE  0
#define PNG_RGB 2
#define PNG_INDEXED 3
#define PNG_GREYSCALEALPHA 4
#define PNG_RGBALPHA 6
// COLOR TYPES


struct PNGHeader
{
	unsigned char PNGSignature[8];

	// 4 Byte reserved data(FourCC)
	size_t crc;

	// IHDR
	unsigned char ImageHeader[4]; 
	size_t width;
	size_t height;		

	// This might be 1,2,4,8... 1 bit = 2 tones
	unsigned char bitDepth;

	// ColorTypes are predefined at this header check them for more info  
	// if color type is 3 then there must be a PLTE chunk
	unsigned char colorType;


	// This must be only 0
	unsigned char compressionMethod;

	// 1-0
	unsigned char filterMethod;	   

	unsigned char interlaceMethod; // if 1 -> Adam7

};