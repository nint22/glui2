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

class g2Label : public g2Controller
{
public:
    
    // Label constructor
    g2Label(g2Controller* Parent, g2Theme* MainTheme);
    
    // Label destructor
    ~g2Label();
    
    // Set the text string; new lines WILL be printed on following lines
    void SetText(const char* Text);
    
protected:
    
    // Render
    void Render();
    
private:
    
    // The internal text buffer
    char* TextBuffer;
    
};

// End of inclusion guard
#endif
