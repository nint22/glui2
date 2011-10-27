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
    
    // Default vertical to false
    IsVertical = false;
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
    this->Width = Width;
}

int g2Slider::GetWidth()
{
    return Width;
}

void g2Slider::SetVertical(bool Vertical)
{
    IsVertical = Vertical;
}

bool g2Slider::GetVertical()
{
    return IsVertical;
}

void g2Slider::Render(int pX, int pY)
{
    // Get slider button status
    g2ThemeElement ButtonStyle = IsVertical ? g2Theme_VSliderButton : g2Theme_SliderButton;
    if(GetDisabled())
        ButtonStyle = IsVertical ? g2Theme_VSliderButton_Disabled : g2Theme_SliderButton_Disabled;
    else if(IsDragging || ((GetControllerState() & g2ControllerState_Pressed) == g2ControllerState_Pressed))
        ButtonStyle = IsVertical ? g2Theme_VSliderButton_Pressed : g2Theme_SliderButton_Pressed;
    
    // If horizontal style
    if(!IsVertical)
    {
        // Center on the vertical of the user's slider controller
        int SliderWidth, SliderHeight;
        int ControllerHeight;
        GetTheme()->GetComponentSize(g2Theme_SliderButton, &SliderWidth, &SliderHeight);
        GetTheme()->GetComponentSize(g2Theme_Slider, NULL, &ControllerHeight);
        
        // Which is the total height? We may need to shift the slider's background
        // since some slider buttons are taller than the bg
        int TotalHeight = SliderHeight;
        if(ControllerHeight > TotalHeight)
            TotalHeight = ControllerHeight;
        
        // Render the centered background
        DrawComponentStretch(g2Theme_Slider, pX, pY + TotalHeight / 2 - ControllerHeight / 2, Width);
        
        // Computer offsets
        float ProgressRatio = Progress / fabs(MaxBound - MinBound);
        int OffsetX = g2Slider_SidePixelBuffer + int(float(Width - 2 * g2Slider_SidePixelBuffer) * ProgressRatio) - SliderWidth / 2;
        
        // Draw the slider button itself
        DrawComponent(ButtonStyle, pX + OffsetX, pY + TotalHeight / 2 - SliderHeight / 2);
    }
    else
    {
        // center on the horizontal of the user's slider controller
        int SliderWidth, SliderHeight;
        int ControllerWidth;
        GetTheme()->GetComponentSize(g2Theme_VSliderButton, &SliderWidth, &SliderHeight);
        GetTheme()->GetComponentSize(g2Theme_VSlider, &ControllerWidth);
        
        // Which is the total height? We may need to shift the slider's background
        // since some slider buttons are taller than the bg
        int TotalWidth = SliderWidth;
        if(ControllerWidth > TotalWidth)
            TotalWidth = ControllerWidth;
        
        // Render the background image
        // Note that we are converting our width to height
        DrawComponentRect(g2Theme_VSlider, pX + TotalWidth / 2 - ControllerWidth / 2, pY, ControllerWidth, Width);
        
        // Computer offsets
        float ProgressRatio = Progress / fabs(MaxBound - MinBound);
        int OffsetY = g2Slider_SidePixelBuffer + int(float(Width - 2 * g2Slider_SidePixelBuffer) * ProgressRatio) - SliderHeight / 2;
        
        // Draw the slider button itself
        DrawComponent(ButtonStyle, pX + TotalWidth / 2 - SliderWidth / 2, pY + OffsetY);
    }
}

void g2Slider::GetCollisionRect(int* Width, int* Height)
{
    // If horizontal
    if(!IsVertical)
    {
        GetTheme()->GetComponentSize(g2Theme_SliderButton, NULL, Height);
        *Width = GetWidth();
    }
    // Else, is vertical
    else
    {
        GetTheme()->GetComponentSize(g2Theme_VSliderButton, Width);
        *Height = GetWidth();
    }
}

void g2Slider::MouseDrag(int x, int y)
{
    IsDragging = true;
}

void g2Slider::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // User attempts to focus on a specific position
    if(InController(x, y) && button == g2MouseButton_Left && state == g2MouseClick_Down)
    {
        // Move to target position
        bool WasDragging = IsDragging;
        IsDragging = true;
        MouseHover(x, y);
        IsDragging = WasDragging;
    }
    // User is done dragging
    else if(button == g2MouseButton_Left && state == g2MouseClick_Up)
        IsDragging = false;
}

void g2Slider::MouseHover(int x, int y)
{
    // Are we dragging and it is horizontal
    if(IsDragging)
    {
        // Compute horizontal, or vertical, offsets
        if(!IsVertical)
            Progress = fabs(MaxBound - MinBound) * ((x - g2Slider_SidePixelBuffer) / float(Width - 2 * g2Slider_SidePixelBuffer));
        else
            Progress = fabs(MaxBound - MinBound) * ((y - g2Slider_SidePixelBuffer) / float(Width - 2 * g2Slider_SidePixelBuffer));
        
        // Apply limits
        if(Progress < MinBound)
            Progress = MinBound;
        else if(Progress > MaxBound)
            Progress = MaxBound;
        
        // Update the live value as needed
        if(LiveValue != NULL)
            *LiveValue = Progress;
    }
}
