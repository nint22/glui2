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
    __g2EXPORT g2CheckBox(g2Controller* Parent, g2Theme* MainTheme);
    
    // Get access to the label
    __g2EXPORT g2Label* GetLabel();
    
    // Return the check state
    __g2EXPORT bool IsChecked();
    
    // Set the check state
    __g2EXPORT void SetChecked(bool Check);
    
    // Add a live variable; pass NULL (or leave blank) to disconnect
    __g2EXPORT void SetLiveVariable(bool* LiveCheckState = NULL);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
private:
    
    // Check the user input
    void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
    // Text label
    g2Label* Label;
    
    // Current check status
    bool Checked;
    
    // Live value
    bool* LiveCheckState;
    
};

// End of inclusion guard
#endif
