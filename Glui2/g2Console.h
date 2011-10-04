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
 
***************************************************************/

// Inclusion guard
#ifndef __G2CONSOLE_H__
#define __G2CONSOLE_H__

#include "g2Controller.h"

class g2Console : public g2Controller
{
public:
    
    // Console constructor
    g2Console(g2Controller* Parent, g2Theme* MainTheme);
    
    // Release the i/o buffers
    ~g2Console();
    
    // Print to the buffer
    void printf(const char* format, ...);
    
    // Read off the latest string command the user as typed in; based on FIFO order
    // May return null if there is nothing in the buffer
    // Note that the returned buffer MUST be released when you are done with it
    char* gets();
    
    // Define controller geometry
    bool InController(int x, int y);
    
protected:
    
    // Update
    void Update(float dT);
    
    // Render
    void Render();
    
    // Gets the screen width and heigh
    void WindowResizeEvent(int NewWidth, int NewHeight);
    
    // Handle user inputs
    void KeyEvent(unsigned char key, bool IsSpecial);
    
private:
    
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
