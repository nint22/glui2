/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Images.cpp/h
 Desc: C-Style image loading and saving functions. Based on
 interfacing with stb_image from author Sean Barrett and his
 published code on http://nothings.org/
 
 Loads all of the following formats: (based on stb_images)
 
 JPEG baseline (no JPEG progressive)
 PNG 8-bit only
 
 TGA (not sure what subset, if a subset)
 BMP non-1bpp, non-RLE
 PSD (composited view only, no extra channels)
 
 GIF (*comp always reports as 4-channel)
 HDR (radiance rgbE format)
 PIC (Softimage PIC)
 
***************************************************************/

// Inclusion guard
#ifndef __G2IMAGES_H__
#define __G2IMAGES_H__

#include "g2Utilities.h"
#include "stb_image.h"
#include <map>
#include <string>

// Open a given image and copy it into the OpenGL image buffers;
// if the image has not yet been opened before, then a unique reference
// is made, otherwise a copy isn't made but the same reference is returned
// Return a negative value if unable to open file / image
GLuint g2LoadImage(const char* ImagePath, int* Width = NULL, int* Height = NULL, int* Channels = NULL, bool Wrap = false);

// End of inclusion guard
#endif
