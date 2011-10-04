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
    GetTheme()->GetComponentSize(g2Theme_Slider, NULL, &Width);
    
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

void g2Slider::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // What is the slider bar's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_Slider, &MinWidth);
    
    /*** Background ***/
    
    // If default size, just render normally
    if(Width == MinWidth)
        DrawComponent(pX, pY, g2Theme_Slider);
    
    // Else, we have to draw the two sides and stretch the middle
    else
    {
        // Source texture coordinates
        float SourceX, SourceY, SourceWidth, SourceHeight;
        int OutWidth, OutHeight;
        GetTheme()->GetComponent(g2Theme_Slider, &SourceX, &SourceY, &SourceWidth, &SourceHeight, &OutWidth, &OutHeight);
        
        // Draw the left-most third
        DrawComponent(pX, pY, OutWidth / 3, OutHeight, SourceX, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the right-most third
        DrawComponent(pX + Width - OutWidth / 3, pY, OutWidth / 3, OutHeight, SourceX + (2.0f * SourceWidth) / 3.0f, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the middle two positions
        // Note the overlap between the middle's right side and the right side's left lip
        // This is to make sure there isn't a pixel space
        DrawComponent(pX + OutWidth / 3.0f, pY, Width - (2.0f * OutWidth) / 3.0f + 1, OutHeight, SourceX + SourceWidth / 3.0f, SourceY, SourceWidth - (2.0f * SourceWidth) / 3.0f, SourceHeight);
    }
    
    /*** Foreground ***/
    
    // Center on the vertical
    int SliderWidth, SliderHeight;
    int ControllerHeight;
    GetTheme()->GetComponentSize(g2Theme_SliderButton, &SliderWidth, &SliderHeight);
    GetTheme()->GetComponentSize(g2Theme_Slider, NULL, &ControllerHeight);
    
    // Computer offsets
    float ProgressRatio = Progress / fabs(MaxBound - MinBound);
    int OffsetX = int(float(Width) * ProgressRatio) - SliderWidth / 2;
    int OffsetY = ControllerHeight / 2 - SliderHeight / 2;
    
    // Draw slider button
    if(GetDisabled())
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_SliderButton_Disabled);
    else if(IsDragging || GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_SliderButton_Pressed);
    else
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_SliderButton);
    
    // Update the live value as needed
    if(LiveValue != NULL)
        *LiveValue = Progress;
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
    // Are we draggig?
    if(IsDragging)
    {
        // Get the GUI position
        int pX, pY;
        GetPos(&pX, &pY);
        
        // Bounds check
        if(x < pX)
            Progress = MinBound;
        else if(x > pX + Width)
            Progress = MaxBound;
        else
        {
            // Find the ratio and apply the min/max bounds
            Progress = fabs(MaxBound - MinBound) * ((x - pX) / float(Width));
        }
    }
}

bool g2Slider::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_SliderButton, NULL, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + Width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
