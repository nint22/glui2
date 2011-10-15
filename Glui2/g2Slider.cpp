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
    // Default progress is 50% within [0, 1]
    Progress = 0.5f;
    MinBound = 0.0f;
    MaxBound = 1.0f;
    
    // Default to no dragging
    IsDragging = false;
    
    // Set the width to default value
    SetWidth(0);
    
    // Default to no live value
    LiveValue = NULL;
}

void g2Slider::SetLiveVariable(float* LiveValue)
{
    this->LiveValue = LiveValue;
}

void g2Slider::SetBounds(float Lower, float Upper)
{
    MinBound = Lower;
    MaxBound = Upper;
}

void g2Slider::SetProgress(float Progress)
{
    // Apply limits, save values
    this->Progress = fmax(fmin(Progress, MaxBound), MinBound);
}

float g2Slider::GetProgress()
{
    return Progress;
}

void g2Slider::SetWidth(int Width)
{
    // What is the button's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_Slider, &MinWidth);
    
    if(Width > MinWidth)
        this->Width = Width;
    else
        this->Width = MinWidth;
}

int g2Slider::GetWidth()
{
    return Width;
}

void g2Slider::Render(int pX, int pY)
{
    // Render the background
    DrawComponent(g2Theme_Slider, pX, pY, Width);
    
    // Center on the vertical the user's slider controller
    int SliderWidth, SliderHeight;
    int ControllerHeight;
    GetTheme()->GetComponentSize(g2Theme_SliderButton, &SliderWidth, &SliderHeight);
    GetTheme()->GetComponentSize(g2Theme_Slider, NULL, &ControllerHeight);
    
    // Computer offsets
    float ProgressRatio = Progress / fabs(MaxBound - MinBound);
    int OffsetX = int(float(Width - 2 * SidePixelBuffer) * ProgressRatio) - SliderWidth / 2 + SidePixelBuffer;
    int OffsetY = ControllerHeight / 2 - SliderHeight / 2;
    
    // Draw slider button
    if(GetDisabled())
        DrawComponent(g2Theme_SliderButton_Disabled, pX + OffsetX, pY + OffsetY);
    else if(IsDragging || GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(g2Theme_SliderButton_Pressed, pX + OffsetX, pY + OffsetY);
    else
        DrawComponent(g2Theme_SliderButton, pX + OffsetX, pY + OffsetY);
    
    // Update the live value as needed
    if(LiveValue != NULL)
        *LiveValue = Progress;
}

void g2Slider::GetCollisionRect(int* Width, int* Height)
{
    // Post back slider length
    GetTheme()->GetComponentSize(g2Theme_SliderButton, NULL, Height);
    *Width = GetWidth();
}

void g2Slider::MouseDrag(int x, int y)
{
    IsDragging = true;
}

void g2Slider::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    if(button == g2MouseButton_Left && state == g2MouseClick_Up)
        IsDragging = false;
}

void g2Slider::MouseHover(int x, int y)
{
    // Are we dragging?
    if(IsDragging)
    {
        // Get the GUI position
        int gX, gY;
        GetGlobalPos(&gX, &gY);
        
        // Compute the progress
        Progress = fabs(MaxBound - MinBound) * ((x - gX - SidePixelBuffer) / float(Width - 2 * SidePixelBuffer));
        if(Progress < MinBound)
            Progress = MinBound;
        else if(Progress > MaxBound)
            Progress = MaxBound;
    }
}
