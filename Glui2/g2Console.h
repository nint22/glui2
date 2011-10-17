/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Console.cpp/h
 Desc: A simple interactive console where end-developers can
 interface with, using either the GetString() for access to a
 queue (FIFO order) and prints out colors using a special
 extension based on Minecraft's own unique coloring system.
 
 For colors, the text must start with character  '/'
 followed by a 4-bit value ranging from 0 to 15. The following
 is the color map: (Full CGA 16-color palette)
 
 0  - black
 1  - blue
 2  - green
 3  - cyan
 4  - red
 5  - magenta
 6  - brown
 7  - light gray
 8  - gray
 9  - light blue
 10 - light green
 11 - light cyan
 12 - light red
 13 - light magenta
 14 - yellow
 15 - white
 
 The color only stays on the same line of text; any new-line
 character will reset the color back to the default. Also note
 that a console does not have shadows.
 
***************************************************************/

// Inclusion guard
#ifndef __G2CONSOLE_H__
#define __G2CONSOLE_H__

#include "g2Controller.h"
#include "g2LabelEdit.h"
#include "g2Label.h"

// Maximum input length
static const int g2Console_MaxInputSize = 64;

class g2Console : public g2Controller
{
public:
    
    // Console constructor
    __g2EXPORT g2Console(g2Controller* Parent, g2Theme* MainTheme);
    
    // Release the i/o buffers
    __g2EXPORT ~g2Console();
    
    // Print to the buffer
    __g2EXPORT void printf(const char* format, ...);
    
    // Read off the latest string command the user as typed in; based on FIFO order
    // May return null if there is nothing in the buffer; will copy over 'length'
    // chars into the given buffer; maximum input is g2Console_MaxInputLength, if
    // there is no imput, length will be 0
    __g2EXPORT void gets(char* OutBuffer, int* Length);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
    // Gets the screen width and heigh
    __g2EXPORT void WindowResizeEvent(int NewWidth, int NewHeight);
    
private:
    
    // Get a color from the internal 4-bit template
    void GetTemplateColor(int Index, float* r, float* g, float* b);
    
    // Active width and height
    int WindowWidth, WindowHeight;
    
    // User input handler
    g2LabelEdit* LabelEdit;
    
    // The label infront of the edit
    g2Label* Label;
    
    // Input and output queues
    // Note that the out console might also retain
    // a copy of the input; since the user should
    // see what they write
    std::queue<char*> ConsoleIn;
    std::queue<char*> ConsoleOut;
};

// End of inclusion guard
#endif
