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

// Define an anchor style, or how controller are added
// Note that these are uints so we can combine flags together
// It is up to the end-developer to combine them using the bit-wise or operator
typedef unsigned int g2Anchor;
static const g2Anchor g2Anchor_None     = 0x0000;    // Same as a top-left anchor; i.e. never moves
static const g2Anchor g2Anchor_Top      = 0x0001;    // Anchor is from top of screen
static const g2Anchor g2Anchor_Left     = 0x0002;    // Anchor is on left-screen edge
static const g2Anchor g2Anchor_Bottom   = 0x0004;    // Anchor is from bottom fo screen
static const g2Anchor g2Anchor_Right    = 0x0008;    // Anchor is on the right-screen edge

class g2Panel : public g2Controller
{
public:
    
    // Panel constructor
    g2Panel(g2Controller* Parent, g2Theme* MainTheme, g2Anchor Anchors);
    
    // Add a controller (will remove controller from the current parent and
    // re-assign the parent to this panel)
    void AddController(g2Controller* Child);
    
    // Set the anchor style
    void SetAnchors(g2Anchor Anchors);
    
    // Explicitly set the size of this panel, thus turning it into a window-based shap
    void SetSize(int NewWidth, int NewHeight);

    // Set the overlap ratio
    void SetSize(float Ratio);
    
protected:
    
    // Render
    void Render();
    
    // Window resize event
    void WindowResizeEvent(int NewWidth, int NewHeight);
    
    // Define controller geometry
    bool InController(int x, int y);
    
    // Anchor flags
    g2Anchor Anchors;
    
    // Entire panel's surface width and height
    int Width, Height;
    
    // The overlap ratio
    float Ratio;
};

// End of inclusion guard
#endif
