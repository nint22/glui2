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
    Label->SetPos(TextOffset, 2);
    Label->SetColor(0, 0, 0);
    Label->SetText("Undefined g2CheckBox");
    
    // Default to no live value
    LiveCheckState = NULL;
    
    // Default check to none
    Checked = false;
}

g2Label* g2CheckBox::GetLabel()
{
    // Return the label we are working on
    return Label;
}

bool g2CheckBox::IsChecked()
{
    return Checked;
}

void g2CheckBox::SetChecked(bool Check)
{
    Checked = Check;
}

void g2CheckBox::SetLiveVariable(bool* LiveCheckState)
{
    this->LiveCheckState = LiveCheckState;
}

void g2CheckBox::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw based on the current state
    if(GetControllerState() == g2ControllerState_Clicked)
    {
        // Flip state
        Checked = !Checked;
        
        // Post if possible
        if(LiveCheckState != NULL)
            *LiveCheckState = Checked;
    }
    
    // Draw based on the current check state
    if(GetDisabled())
        DrawComponent(pX, pY, Checked ? g2Theme_CheckBox_Pressed_Disabled : g2Theme_CheckBox_Disabled);
    
    // Normal selection
    else
        DrawComponent(pX, pY, Checked ? g2Theme_CheckBox_Pressed : g2Theme_CheckBox);
}

bool g2CheckBox::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_CheckBox, &width, &height);
    
    // Add the text length and offset
    width += Label->GetWidth();
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
