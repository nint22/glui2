/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2CheckBox.cpp/h
 Desc: A simple checkbox implementation.
 
***************************************************************/

// Inclusion guard
#ifndef __G2CHECKBOX_H__
#define __G2CHECKBOX_H__

#include "g2Controller.h"
#include "g2Label.h"

class g2CheckBox : public g2Controller
{
public:
    
    // Checkbox constructor
    g2CheckBox(g2Controller* Parent, g2Theme* MainTheme);
    
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
