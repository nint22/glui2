/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2TextBox.cpp/h
 Desc: An interactive text box (much like the g2TextField) that
 expects large blocks of text.
 
***************************************************************/

// Inclusion guard
#ifndef __G2TEXTBOX_H__
#define __G2TEXTBOX_H__

#include "g2Controller.h"

class g2TextBox : public g2Controller
{
public:
    
    // Standard constructor
    g2TextBox(g2Controller* Parent, g2Theme* MainTheme);
    
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
