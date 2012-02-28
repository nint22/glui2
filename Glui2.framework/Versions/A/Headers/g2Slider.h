/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Slider.cpp/h
 Desc: Slider bar implementation. Note that the user must
 explicitly drag the button, and thus the "InController(...)"
 function only checks the drag button (which is internally
 rendered here, and not a derivative of g2Button). Can be either
 horizontal or vertical; if vertical
 
***************************************************************/

// Inclusion guard
#ifndef __G2SLIDER_H__
#define __G2SLIDER_H__

#include "g2Controller.h"
#include "g2Label.h"

// The pixel buffer from the left side and right side
static const int g2Slider_SidePixelBuffer = 10;

class g2Slider : public g2Controller
{
public:
    
    // Progress bar constructor
    __g2EXPORT g2Slider(g2Controller* Parent, g2Theme* MainTheme);
    
    // Add a live variable; pass NULL (or leave blank) to disconnect
    __g2EXPORT void SetLiveVariable(float* LiveValue = NULL);
    
    // Set the min / max bounds of the progress bar; defaults to [0.0, 1.0]
    __g2EXPORT void SetBounds(float Lower, float Upper);
    
    // Set the current progress of this progress bar; accepts
    // values from 0 to 1 (floats)
    __g2EXPORT void SetProgress(float Progress);
    
    // Return the current progress
    __g2EXPORT float GetProgress();
    
    // Set the width of the slider in pixels
    __g2EXPORT void SetWidth(int Width);
    
    // Get the current width of the slider in pixels
    __g2EXPORT int GetWidth();
    
    // Set vertical (or false to horizontal)
    __g2EXPORT void SetVertical(bool Vertical);
    
    // get vertical state
    __g2EXPORT bool GetVertical();
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
    // Keep moving the controller based on the user's dragging
    __g2EXPORT void MouseDrag(int x, int y);
    
    // Used when releasing a drag
    __g2EXPORT void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
    // Get the mouse position; used for dragging outside of the controller
    __g2EXPORT void MouseHover(int x, int y);
    
private:
    
    // Min / max bounds
    float MinBound, MaxBound;
    
    // Current progress
    float Progress;
    
    // Actively dragging
    bool IsDragging;
    
    // Width of the controller
    int Width;
    
    // Is vertical
    bool IsVertical;
    
    // Live value
    float* LiveValue;
    
};

// End of inclusion guard
#endif
