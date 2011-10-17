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
#include "g2Button.h"
#include "g2Label.h"

// Alpha value when a button isn't selected
static const float g2DropDown_DeselectedAlpha = 0.5f;

class g2DropDown : public g2Controller
{
public:
    
    // Drop down
    __g2EXPORT g2DropDown(g2Controller* Parent, g2Theme* MainTheme);
    
    // Explicitly set the width of controller
    __g2EXPORT void SetWidth(int Width);
    
    // Return the width of the controller
    __g2EXPORT int GetWidth();
    
    // Set the options via an array of strings
    __g2EXPORT void SetOptions(const char** OptionLabels, int OptionCount);
    
    // Set the current selection
    __g2EXPORT void SetSelectionIndex(int Index);
    
    // Get the current selection; defaults to 0
    __g2EXPORT int GetSelectionIndex();
    
    // Add a live variable; pass NULL (or leave blank) to disconnect
    __g2EXPORT void SetLiveVariable(int* LiveIndex = NULL);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
public:
    
    // Used when releasing a drag
    __g2EXPORT void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
    // Keep the mouse known so we update the indexing
    __g2EXPORT void MouseHover(int x, int y);
    
private:
    
    // Button label array, one for each option
    g2Button** Buttons;
    
    // Active selection text field
    g2Button* ButtonField;
    
    // Number of options
    int OptionCount;
    
    // Active and selected index we have selected
    // Active index is what is returned to the end-developer
    // while active selection is that which the user may be switching to
    int ActiveIndex;
    int ActiveSelection;
    
    // Actively dragging
    bool IsDragging;
    
    // Live value
    int* LiveIndex;
    
};

// End of inclusion guard
#endif
