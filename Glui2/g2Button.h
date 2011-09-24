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
    g2Button(g2Controller* Parent, g2Theme* MainTheme);
    
    // Get access to the label
    g2Label* GetLabel();
    
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
