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
    
    // Return the check state
    bool IsChecked();
    
    // Set the check state
    void SetChecked(bool Check);
    
    // Add a live variable; pass NULL (or leave blank) to disconect
    void SetLiveVariable(bool* LiveCheckState = NULL);
    
    // Define controller geometry
    bool InController(int x, int y);
    
protected:
    
    // Render
    void Render();
    
private:
    
    // Text label
    g2Label* Label;
    
    // Current check status
    bool Checked;
    
    // The pixel offset from the label icon itself
    static const int TextOffset = 18;
    
    // Live value
    bool* LiveCheckState;
    
};

// End of inclusion guard
#endif
