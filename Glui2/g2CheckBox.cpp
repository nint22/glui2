/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 ***************************************************************/

#include "g2CheckBox.h"

g2CheckBox::g2CheckBox(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Allocate text and set initial position
    // Note that we are registereting to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(15, 2);
    Label->SetColor(0, 0, 0);
    Label->SetText("Undefined...");
}

const g2Label* g2CheckBox::GetLabel()
{
    // Return the label we are working on
    return Label;
}

void g2CheckBox::Render()
{
    // Draw something simple
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw based on the current state
    if(GetDisabled())
        DrawComponent(pX, pY, g2Theme_CheckBox_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX, pY, g2Theme_CheckBox_Pressed);
    else
        DrawComponent(pX, pY, g2Theme_CheckBox);
}

bool g2CheckBox::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_CheckBox, &width, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
