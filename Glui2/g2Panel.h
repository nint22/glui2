/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Panel.cpp/h
 Desc: A tiled background and placement manager for GUI
 controllers. A panel allows end-developers to add new GUI anchored
 controllers so that window movement and resizing will automatically
 move around and manage the UI's positions.
 
***************************************************************/

// Inclusion guard
#ifndef __G2PANEL_H__
#define __G2PANEL_H__

#include "g2Controller.h"

class g2Panel : public g2Controller
{
public:
    
    // Panel constructor
    g2Panel(g2Controller* Parent, g2Theme* MainTheme);
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
};

// End of inclusion guard
#endif
