/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Spinner.h"

g2Spinner::g2Spinner(g2Controller* Parent, g2Theme* MainTheme, g2SpinnerType Type)
: g2Controller(Parent, MainTheme)
{
    // Allocate textfield and set initial position
    // Note that we are registereting to this button, not the root-parent
    TextField = new g2TextField(this, MainTheme);
    
    // Save given type
    this->Type = Type;
    
    // Default the float and integer values to 0
    FloatVal = 0.0f;
    IntVal = 0;
}

void g2Spinner::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Get the height for the slider button based on the current collision
    int height;
    bool IsFound = GetTheme()->GetComponentSize(g2Theme_Spinner, NULL, &height);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", g2Theme_Spinner);
    
    // Draw the spinner button
    // Note that the 100+ pixel offset is for the text field
    if(GetDisabled())
        DrawComponent(pX + 100, pY, g2Theme_Spinner_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX + 100, pY, g2Theme_Spinner_Pressed);
    else
        DrawComponent(pX + 100, pY, g2Theme_Spinner);
}

bool g2Spinner::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_Spinner, &width, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
