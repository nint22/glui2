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
    
    // Set the current progress of this progress bar; accepts
    // values from 0 to 1 (floats)
    void SetProgress(float Progress);
    
protected:
    
    // Render
    void Render();
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text label
    g2Label* Label;
    
    // The current progress factor
    float Progress;
    
};

// End of inclusion guard
#endif
