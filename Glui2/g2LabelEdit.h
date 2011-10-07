/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2LabelEdit.cpp/h
 Desc: An editable g2Label; allows for boxed rendering (i.e. only
 renders within the target width).
 
***************************************************************/

// Inclusion guard
#ifndef __G2LABELEDIT_H__
#define __G2LABELEDIT_H__

#include "g2Controller.h"

class g2LabelEdit : public g2Controller
{
public:
    
    // Label constructor
    __g2EXPORT g2LabelEdit(g2Controller* Parent, g2Theme* MainTheme);
    
    // Label destructor
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
    
protected:
    
    // Render
    __g2EXPORT void Render();
    
private:
    
    // The internal text buffer
    char* TextBuffer;
    
    // Internal size scale
    float Scale;
    
};

// End of inclusion guard
#endif
