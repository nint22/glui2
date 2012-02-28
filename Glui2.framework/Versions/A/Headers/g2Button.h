/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Button.cpp/h
 Desc: A simple button implementation.
 
***************************************************************/

// Inclusion guard
#ifndef __G2BUTTON_H__
#define __G2BUTTON_H__

#include "g2Controller.h"
#include "g2Label.h"

class g2Button : public g2Controller
{
public:
    
    // Button constructor
    __g2EXPORT g2Button(g2Controller* Parent, g2Theme* MainTheme);
    
    // Get access to the label
    __g2EXPORT g2Label* GetLabel();
    
    // Set the button's text; note that the button will grow if needed
    __g2EXPORT void SetText(const char* Text);
    
    // Set the width of the button in pixels
    __g2EXPORT void SetWidth(int Width);
    
    // Return the current width
    __g2EXPORT int GetWidth();
    
    // Set the button's icon source
    // The given icon name is a component defined in the theme file
    // which requires an origin and size; Pass to arguments to reset icon
    __g2EXPORT void SetIcon(const char* IconName = NULL);
    
    // Set the text's alignment, accepts either none / left alignment (default), centered, or right alignment
    __g2EXPORT void SetAlignment(g2Anchor Alignment = g2Anchor_None);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
private:
    
    // Text label
    g2Label* Label;
    
    // Text label's alignment (either left [default], center, or right)
    g2Anchor LabelAnchor;
    
    // Target width of this instance
    int Width;
    
    // Icon name, if length 0 then no icon
    char UsingIcon[g2Config_KeySize];
    
    // Static text offset; only computed once
    int LabelOffsetX, LabelOffsetY;
};

// End of inclusion guard
#endif
