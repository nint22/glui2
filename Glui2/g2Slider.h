/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Slider.cpp/h
 Desc: Slider bar implementation. Note that the user must
 explicitly drag the button, and thus the "InController(...)"
 function only checks the drag button (which is internally
 rendered here, and not a derivative of g2Button).
 
***************************************************************/

// Inclusion guard
#ifndef __G2SLIDER_H__
#define __G2SLIDER_H__

#include "g2Controller.h"
#include "g2Label.h"

class g2Slider : public g2Controller
{
public:
    
    // Progress bar constructor
    g2Slider(g2Controller* Parent, g2Theme* MainTheme);
    
    // Get access to the label that is centered on the button
    g2Label* GetLabel();
    
    // Set the current progress of this progress bar; accepts
    // values from 0 to 1 (floats)
    void SetProgress(float Progress);
    
    // Add a live variable; pass NULL (or leave blank) to disconect
    void SetLiveVariable(float* LiveValue = NULL);
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text label
    g2Label* Label;
    
    // Current progress
    float Progress;
    
    // Live value
    float* LiveValue;
    
};

// End of inclusion guard
#endif
