/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Label.cpp/h
 Desc: A text output; the text is generated and drawn using a
 bitmap. This bitmap is defined in the configuration file
 and must be mapped out as a 4bit x 4bit matrix. For example
 the letter 'A' is 0x41 so the higher nibble is 0x4 (0100)
 and the lower nibble is 0x1 (0001) and thus position (4, 1)
 in the table.
 
***************************************************************/

// Inclusion guard
#ifndef __G2LABEL_H__
#define __G2LABEL_H__

#include "g2Controller.h"

// Number if pixels between characters draw on-screen
static const int g2Label_CharacterSpacing = 2;

class g2Label : public g2Controller
{
public:
    
    // Label constructor
    __g2EXPORT g2Label(g2Controller* Parent, g2Theme* MainTheme);
    
    // Label destructor
    __g2EXPORT ~g2Label();
    
    // Set the text string; new lines WILL be printed on following lines
    __g2EXPORT void SetText(const char* Text = NULL);
    
    // Return a constant buffer to the given string; should never be modified
    // The returned buffer may or may not exist soon after the direct call; you should
    // copy the buffer as soon as possible if it is to not be immediately used
    __g2EXPORT const char* const GetText();
    
    // Set the size of the output (as a ratio)
    __g2EXPORT void SetSize(float Scale);
    
    // Get the width of the text label in pixels
    __g2EXPORT int GetWidth();
    
    // Set a shadow (true to render a shadow with text)
    __g2EXPORT void SetShadow(bool State);
    
    // Get the shadow state (true if shadow is visible)
    __g2EXPORT bool GetShadow();
    
    // Get a color from the internal 4-bit template
    __g2EXPORT static void GetTemplateColor(int Index, float* r, float* g, float* b);
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
private:
    
    // The internal text buffer
    char* TextBuffer;
    
    // Internal size scale
    float Scale;
    
    // Shadow state
    bool Shadow;
};

// End of inclusion guard
#endif
