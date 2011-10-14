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
    // May return null if there is nothing in the buffer
    // Note that the returned buffer MUST be released when you are done with it
    __g2EXPORT char* gets();
    
    // Define controller geometry
    __g2EXPORT bool InController(int x, int y);
    
protected:
    
    // Update
    __g2EXPORT void Update(float dT);
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Gets the screen width and heigh
    __g2EXPORT void WindowResizeEvent(int NewWidth, int NewHeight);
    
    // Handle user inputs
    __g2EXPORT void KeyEvent(unsigned char key, bool IsSpecial);
    
private:
    
    // Get a color from the internal 4-bit template
    void GetTemplateColor(int Index, float* r, float* g, float* b);
    
    // Active width and height
    int WindowWidth, WindowHeight;
    
    // Current input buffer (on-screen)
    char InputBuffer[1024];
    
    // Input and output queues
    // Note that the out console might also retain
    // a copy of the input; since the user should
    // see what they write
    std::queue<char*> ConsoleIn;
    std::queue<char*> ConsoleOut;
    
    // The total time the cursor has been in the current cursor style
    float CursorTime;
    
    // The current cursor state (on is '_', off is ' ')
    bool CursorState;
    
    // Maximum input length
    static const int MaxInputLength = 1024;
};

// End of inclusion guard
#endif
