/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2RadioGroup.cpp/h
 Desc: A mutually-exclusive selection system.
 
***************************************************************/

// Inclusion guard
#ifndef __G2RADIOGROUP_H__
#define __G2RADIOGROUP_H__

#include "g2Controller.h"
#include "g2Label.h"

class g2RadioGroup : public g2Controller
{
public:
    
    // Radio group constructor
    __g2EXPORT g2RadioGroup(g2Controller* Parent, g2Theme* MainTheme);
    
    // Release internals
    __g2EXPORT ~g2RadioGroup();
    
    // Set the options via an array of strings
    __g2EXPORT void SetOptions(const char** OptionLabels, int OptionCount);
    
    // Get the current selection; defaults to 0
    __g2EXPORT int GetSelectionIndex();
    
    // Add a live variable; pass NULL (or leave blank) to disconnect
    __g2EXPORT void SetLiveVariable(int* LiveIndex = NULL);
    
    // Define controller geometry
    __g2EXPORT bool InController(int x, int y);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Get the mouse position; used to go either up or down on spinner
    __g2EXPORT void MouseHover(int x, int y);
    
private:
    
    // Text label array, one for each option
    g2Label** Labels;
    
    // Number of options
    int OptionCount;
    
    // Active index we have selected
    int ActiveIndex;
    
    // Internal mouse position; needed for constant increase / decrease
    int MouseX, MouseY;
    
    // Live value
    int* LiveIndex;
};

// End of inclusion guard
#endif
