/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 ***************************************************************/

#include "g2DropDown.h"

g2DropDown::g2DropDown(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Create a text field in which we will drop-down items
    TextField = new g2TextField(this, MainTheme);
    TextField->SetText("Default g2DropDown");
    
    // Set the initial width to a default width value
    GetTheme()->GetComponentSize(g2Theme_TextField, &Width);
}

void g2DropDown::SetWidth(int Width)
{
    // What is the button's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_TextField, &MinWidth);
    
    if(Width > MinWidth)
        this->Width = Width;
    else
        this->Width = MinWidth;
}

void g2DropDown::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw based on the current state
    if(GetDisabled())
        DrawComponent(pX + Width, pY, g2Theme_DropDown_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX + Width, pY, g2Theme_DropDown_Pressed);
    else
        DrawComponent(pX + Width, pY, g2Theme_DropDown);
}

bool g2DropDown::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_DropDown, &width, &height);
    
    // Grow the buttons width to include the text field
    width += Width;
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
