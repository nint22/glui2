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
#include "g2LabelEdit.h"

// Number of pixels to offset the editable text
static const int g2TextField_LabelEditOffset = 5;

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
    __g2EXPORT const char* const GetText();
    
    // Get the text-input / handling object
    __g2EXPORT g2LabelEdit* GetLabelEdit();
    
    // Set the width of the button in pixels
    __g2EXPORT void SetWidth(int Width);
    
    // Get the width of the text field
    __g2EXPORT int GetWidth();
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
private:
    
    // Handle to the text-editing object
    g2LabelEdit* TextEdit;
    
    // Current width
    int Width;
    
};

// End of inclusion guard
#endif
