/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 ***************************************************************/

#include "g2Panel.h"

g2Panel::g2Panel(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Nothing to do yet...
}

void g2Panel::Render()
{
    // Draw something simple
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw based on the current state
    if(GetDisabled())
        DrawComponent(pX, pY, g2Theme_Button_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX, pY, g2Theme_Button_Pressed);
    else
        DrawComponent(pX, pY, g2Theme_Button);
}

bool g2Panel::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_Button, &width, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
