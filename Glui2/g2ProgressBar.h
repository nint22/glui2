/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2ProgressBar.cpp/h
 Desc: Renders progress based on given values, but is not
 interactive in any way with the user.
 
***************************************************************/

// Inclusion guard
#ifndef __G2PROGRESSBAR_H__
#define __G2PROGRESSBAR_H__

#include "g2Controller.h"
#include "g2Label.h"

class g2ProgressBar : public g2Controller
{
public:
    
    // Progress bar constructor
    g2ProgressBar(g2Controller* Parent, g2Theme* MainTheme);
    
    // Get access to the label that is centered on the button
    const g2Label* GetLabel();
    
    // Set the min / max bounds of the progress bar; defaults to [0.0, 1.0]
    void SetBounds(float Lower, float Upper);
    
    // Set the current progress of this progress bar; default bounds are [0.0, 1.0]
    void SetProgress(float Progress);
    
    // Set the button's text; note that the button will grow if needed
    void SetText(const char* Text);
    
    // Set the width of the button in pixels
    void SetWidth(int Width);
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text label
    g2Label* Label;
    
    // Min / max bounds
    float MinBound, MaxBound;
    
    // The current progress factor
    float Progress;
    
    // Target width of the progress bar
    int Width;
};

// End of inclusion guard
#endif
