/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Spinner.h"

g2Spinner::g2Spinner(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Allocate text and set initial position
    // Note that we are registereting to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(5, 5);
    Label->SetColor(0, 0, 0);
    Label->SetText("Undefined...");
    
    // Default progress is 0
    Progress = 0.0f;
}

void g2Spinner::Render()
{
    // Draw something simple
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw the slider bar
    DrawComponent(pX, pY, g2Theme_Slider);
    
    // Get the width for the slider button
    int width;
    bool IsFound = GetTheme()->GetComponentSize(g2Theme_SliderButton, &width, NULL);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", g2Theme_SliderButton);
    
    // Draw the slider button
    if(GetDisabled())
        DrawComponent(pX + float(width) * Progress, pY, g2Theme_SliderButton_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX + float(width) * Progress, pY, g2Theme_SliderButton_Pressed);
    else
        DrawComponent(pX + float(width) * Progress, pY, g2Theme_SliderButton);
}

bool g2Spinner::InController(int x, int y)
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
