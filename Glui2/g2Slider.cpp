/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Slider.h"

g2Slider::g2Slider(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Allocate text and set initial position
    // Note that we are registereting to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(5, 5);
    Label->SetColor(0, 0, 0);
    Label->SetText("Undefined g2Slider");
    
    // Default progress is 0
    Progress = 0.0f;
    
    // Default to no live value
    LiveValue = NULL;
}

g2Label* g2Slider::GetLabel()
{
    // Return the label we are working on
    return Label;
}

void g2Slider::SetProgress(float Progress)
{
    // Save the progress
    if(Progress < 0.0f)
        Progress = 0.0f;
    else if(Progress > 1.0f)
        Progress = 1.0f;
    this->Progress = Progress;
}

void g2Slider::SetLiveVariable(float* LiveValue)
{
    this->LiveValue = LiveValue;
}

void g2Slider::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw the slider bar
    DrawComponent(pX, pY, g2Theme_Slider);
    
    // Get the width for the slider button
    int width;
    bool IsFound = GetTheme()->GetComponentSize(g2Theme_SliderButton, &width, NULL);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", g2Theme_SliderButton);
    
    // NEED TO IMPLEMENT WITH LIVE VALUE
    
    // Draw the slider button
    if(GetDisabled())
        DrawComponent(pX + float(width) * Progress, pY, g2Theme_SliderButton_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX + float(width) * Progress, pY, g2Theme_SliderButton_Pressed);
    else
        DrawComponent(pX + float(width) * Progress, pY, g2Theme_SliderButton);
}

bool g2Slider::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_SliderButton, &width, &height);
    
    // Correct for user sliding
    pX = float(width) * Progress;
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
