/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2LabelEdit.cpp/h
 Desc: An interactive text field; based on source originally
 written for the console and g2TextField, but then coalescted
 together. You can enable / disabled text highlighting, text
 filtering (i.e. only allow numerical-input_, copy / pasting
 too and back from the host OS (Win and OSX feature only), and
 on-screen clipping based on offset.
 
***************************************************************/

// Inclusion guard
#ifndef __G2LABEL_H__
#define __G2LABEL_H__

#include "g2Controller.h"

// Number if pixels between characters draw on-screen
static const int CharacterSpacing = 2;

class g2LabelEdit : public g2Controller
{
public:
    
    // Label constructor and destructor
    __g2EXPORT g2LabelEdit(g2Controller* Parent, g2Theme* MainTheme);
    __g2EXPORT ~g2LabelEdit();
    
    // Set the text string; new lines WILL be printed on following lines
    __g2EXPORT void SetText(const char* Text = NULL);
    
    // Return a constant buffer to the given string; should never be modified
    // The returned buffer may or may not exist soon after the direct call; you should
    // copy the buffer as soon as possible if it is to not be immediately used
    __g2EXPORT const char* GetText();
    
    // Set the size of the output (as a ratio)
    __g2EXPORT void SetSize(float Scale);
    
    // Get the width of the text label in pixels
    __g2EXPORT int GetWidth();
    
    // Set a shadow (true to render a shadow with text)
    __g2EXPORT void SetShadow(bool State);
    
    // Get the shadow state (true if shadow is visible)
    __g2EXPORT bool GetShadow();
    
protected:
    
    // Update
    __g2EXPORT void Update(float dT);
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Handle all key events the user executes
    __g2EXPORT void KeyEvent(unsigned char key, bool IsSpecial);
    
private:
    
    // Set a filter for this text
    bool InFilter(char c);
    
    // The internal text buffer
    char* TextBuffer;
    
    // Internal size scale
    float Scale;
    
    // Shadow state
    bool Shadow;
    
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
};

// End of inclusion guard
#endif
