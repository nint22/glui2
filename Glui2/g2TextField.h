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
 editing inconsistencies.
 
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
    __g2EXPORT g2TextField(g2Controller* Parent, g2Theme* MainTheme);
    
    // Set the text
    __g2EXPORT void SetText(const char* Text);
    
    // Return a constant buffer to the given string; should never be modified
    // The returned buffer may or may not exist soon after the direct call; you should
    // copy the buffer as soon as possible if it is to not be immediately used
    __g2EXPORT const char* GetText();
    
    // Set the width of the button in pixels
    __g2EXPORT void SetWidth(int Width);
    
    // Get the width of the text field
    __g2EXPORT int GetWidth();
    
    // Get the text object
    __g2EXPORT g2Label* GetLabel();
    
    // Set a filter; an array of characters that are the only allowed input
    // characters. Pass null to remove the filter
    __g2EXPORT void SetFilter(const char* Filter);
    
    // Define controller geometry
    __g2EXPORT bool InController(int x, int y);
    
protected:
    
    // Update
    __g2EXPORT void Update(float dT);
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Handle user inputs
    __g2EXPORT void KeyEvent(unsigned char key, bool IsSpecial);
    
private:
    
    // Returns true if the given character is in the filter
    // Returns false if the given character is NOT in the filter
    bool InFilter(char c);
    
    // The actively rendered label
    g2Label* Label;
    
    // Text buffer and max size
    static const int TextBufferLength = 1024;
    char TextBuffer[TextBufferLength];
    
    // Filter buffer
    char* FilterBuffer;
    
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
