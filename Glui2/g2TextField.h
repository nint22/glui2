/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2TextField.cpp/h
 Desc: An interactive text field that may be type-restricted;
 single row of text only. End-developers should always use
 the "SetText" method of this class to set the text for the
 field; using the "SetText" from GetLabel() will cause
 editing inconsistences.
 
***************************************************************/

// Inclusion guard
#ifndef __G2TEXTFIELD_H__
#define __G2TEXTFIELD_H__

#include "g2Controller.h"
#include "g2Label.h"

class g2TextField : public g2Controller
{
public:
    
    // Standard constructor
    g2TextField(g2Controller* Parent, g2Theme* MainTheme);
    
    // Set the text
    void SetText(const char* Text);
    
    // Set the width of the button in pixels
    void SetWidth(int Width);
    
    // Get the width of the text field
    int GetWidth();
    
    // Get the text object
    g2Label* GetLabel();
    
protected:
    
    // Update
    void Update(float dT);
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
    // Handle user inputs
    void KeyEvent(unsigned char key, bool IsSpecial);
    
private:
    
    // The actively rendered label
    g2Label* Label;
    
    // Text buffer and max size
    static const int TextBufferLength = 1024;
    char TextBuffer[TextBufferLength];
    
    // The total time the cursor has been in the current cursor style
    float CursorTime;
    
    // The current cursor state (on is '_', off is ' ')
    bool CursorState;
    
    // Location of the cursor
    float CursorOffset;
    
    // Index position of the cursor
    int CursorIndex;
    
    // Text location offsets
    int OffsetWidth, OffsetHeight;
    
    // Width of an individual character
    int CharWidth;
    
    // Width of the text field
    int Width;
};

// End of inclusion guard
#endif
