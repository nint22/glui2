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
    g2RadioGroup(g2Controller* Parent, g2Theme* MainTheme);
    
    // Release internals
    ~g2RadioGroup();
    
    // Set the options via an array of strings
    void SetOptions(const char** OptionLabels, int OptionCount);
    
    // Get the current selection; defaults to 0
    int GetSelectionIndex();
    
    // Add a live variable; pass NULL (or leave blank) to disconect
    void SetLiveVariable(int* LiveIndex = NULL);
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text label array, one for each option
    g2Label** Labels;
    
    // Number of options
    int OptionCount;
    
    // Active index we have selected
    int ActiveIndex;
    
    // Live value
    int* LiveIndex;
};

// End of inclusion guard
#endif
