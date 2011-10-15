/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Panel.cpp/h
 Desc: A tiled background and placement manager for GUI
 controllers. A panel allows end-developers to add new GUI anchored
 controllers so that window movement and resizing will automatically
 move around and manage the UI's positions. The end-developer
 may explicitly set the size and thus turn off the anchoring
 feature so that this panel will act as a window.
 
***************************************************************/

// Inclusion guard
#ifndef __G2PANEL_H__
#define __G2PANEL_H__

#include "g2Controller.h"

class g2Panel : public g2Controller
{
public:
    
    // Panel constructor
    __g2EXPORT g2Panel(g2Controller* Parent, g2Theme* MainTheme, g2Anchor Anchors);
    
    // Add a controller (will remove controller from the current parent and
    // re-assign the parent to this panel)
    __g2EXPORT void AddController(g2Controller* Child);
    
    // Set the anchor style
    __g2EXPORT void SetAnchors(g2Anchor Anchors);
    
    // Explicitly set the size of this panel, thus turning it into a window-based shap
    __g2EXPORT void SetSize(int NewWidth, int NewHeight);

    // Set the overlap ratio
    __g2EXPORT void SetSize(float Ratio);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
    // Window resize event
    __g2EXPORT void WindowResizeEvent(int NewWidth, int NewHeight);
    
private:

    // Anchor flags
    g2Anchor Anchors;
    
    // Entire panel's surface width and height
    int Width, Height;
    
    // The overlap ratio
    float Ratio;
};

// End of inclusion guard
#endif
