/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2TextField.cpp/h
 Desc: An interactive text field that may be type-restricted;
 single row of text only.
 
***************************************************************/

// Inclusion guard
#ifndef __G2TEXTFIELD_H__
#define __G2TEXTFIELD_H__

#include "g2Controller.h"

class g2TextField : public g2Controller
{
public:
    
    // Standard constructor
    g2TextField(g2Controller* Parent, g2Theme* MainTheme);
    
    // Set the text
    void SetText(const char* Text);
    
protected:
    
    // Update
    void Update(float dT);
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
    // Handle user inputs
    void KeyEvent(unsigned char key);
    
private:
    
    // Maximum input length
    static const int MaxInputLength = 1024;
    
    // Current input buffer (on-screen)
    char InputBuffer[MaxInputLength];
    
    // The total time the cursor has been in the current cursor style
    float CursorTime;
    
    // The current cursor state (on is '_', off is ' ')
    bool CursorState;
};

// End of inclusion guard
#endif
