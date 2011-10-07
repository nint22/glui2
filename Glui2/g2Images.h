/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Images.cpp/h
 Desc: Derived from SOIL (Simple OpenGL Image Library), this
 is a simplified and cleaned version that opens a given image
 and attempts to directly load it into OpenGL's memory. Manages
 an internal dictionary of loaded images so multiple open
 events of the same image will be optimized.
 
 Original author is Jonathan Dummer; http://www.lonesock.net/
 
***************************************************************/

// Inclusion guard
#ifndef __G2IMAGES_H__
#define __G2IMAGES_H__

#include "g2Utilities.h"

class g2Images
{
public:
    
    // Standard constructor and destructor
    __g2EXPORT g2Images();
    __g2EXPORT ~g2Images();
    
};

// End of inclusion guard
#endif
