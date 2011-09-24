/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Spinner.cpp/h
 Desc: An integer or float based spinner that allows the user
 to chose a value between two min/max limits. The user may
 either hit up or down images or directly input the text.
 
***************************************************************/

// Inclusion guard
#ifndef __G2SPINNER_H__
#define __G2SPINNER_H__

#include "g2Controller.h"
#include "g2TextField.h.h"

// Define the two spinner types: int or float

class g2Spinner : public g2Controller
{
public:
    
    // Progress bar constructor
    g2Spinner(g2Controller* Parent, g2Theme* MainTheme, g2SpinnerType Type);
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text label
    g2TextField* TextField;
    
    // The spinner type (usually int or float)
    g2SpinnerType Type;
    
};

// End of inclusion guard
#endif
