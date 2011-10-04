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

class g2DropDown : public g2Controller
{
public:
    
    // Drop down
    g2DropDown(g2Controller* Parent, g2Theme* MainTheme);
    
    // Explicitly set the width of controller
    void SetWidth(int Width);
    
    // Return the width of the controller
    int GetWidth();
    
    // Set the options via an array of strings
    void SetOptions(const char** OptionLabels, int OptionCount);
    
    // Set the current selection
    void SetSelectionIndex(int Index);
    
    // Get the current selection; defaults to 0
    int GetSelectionIndex();
    
    // Add a live variable; pass NULL (or leave blank) to disconect
    void SetLiveVariable(int* LiveIndex = NULL);
    
    // Define controller geometry
    bool InController(int x, int y);
    
protected:
    
    // Render
    void Render();
    
public:
    
    // Used when releasing a drag
    void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
    // Keep the mouse known so we update the indexing
    void MouseHover(int x, int y);
    
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
    
    // Alpha value when a button isn't selected
    static const float DeselectedAlpha = 0.5f;
    
    // Live value
    int* LiveIndex;
    
};

// End of inclusion guard
#endif
