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
    const g2Label* GetLabel();
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text label
    g2Label* Label;
    
};

// End of inclusion guard
#endif
