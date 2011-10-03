/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2DropDown.cpp/h
 Desc: A drop-down selection system that will show a table of
 options. The table currently will keep rendering down (even off-
 screen) if the table is too long. This may be updated in the future
 with a scroll option.
 
***************************************************************/

// Inclusion guard
#ifndef __G2DROPDOWN_H__
#define __G2DROPDOWN_H__

#include "g2Controller.h"
#include "g2TextField.h"

class g2DropDown : public g2Controller
{
public:
    
    // Drop down
    g2DropDown(g2Controller* Parent, g2Theme* MainTheme);
    
    // Explicitly set the width of the drop down
    void SetWidth(int Width);
    
    // Add a live variable; pass NULL (or leave blank) to disconect
    void SetLiveVariable(int* LiveIndex = NULL);
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text field to the left of the button
    g2TextField* TextField;
    
    // The target width of the current drop down
    int Width;
    
    // Live value
    int* LiveIndex;
    
};

// End of inclusion guard
#endif
