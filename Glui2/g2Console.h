#ifdef __DO_NOT_COMPILE__

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
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Input and output queues
    // Note that the out console might also retain
    // a copy of the input; since the user should
    // see what they write
    std::queue<char*> ConsoleIn;
    std::queue<char*> ConsoleOut;
    
};

// End of inclusion guard
#endif

#endif