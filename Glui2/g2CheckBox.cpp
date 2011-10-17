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
    // Center text as best as possible
    int TextOffsetX, TextOffsetY;
    GetTheme()->GetComponentSize(g2Theme_CheckBox, &TextOffsetX, &TextOffsetY);
    
    TextOffsetX += GetTheme()->GetCharacterHeight(); // Good spacing rule
    TextOffsetY = TextOffsetY / 2 - GetTheme()->GetCharacterHeight() / 2;
    
    // Allocate text and set initial position
    // Note that we are registering to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(TextOffsetX, TextOffsetY);
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

void g2CheckBox::Render(int pX, int pY)
{
    // Draw based on the current check state
    if(GetDisabled())
        DrawComponent(Checked ? g2Theme_CheckBox_Pressed_Disabled : g2Theme_CheckBox_Disabled, pX, pY);
    
    // Normal selection
    else
        DrawComponent(Checked ? g2Theme_CheckBox_Pressed : g2Theme_CheckBox, pX, pY);
}

void g2CheckBox::GetCollisionRect(int* Width, int* Height)
{
    // Post-back the size of this controller
    // Note that there is character height spacing between checkbox and text
    GetTheme()->GetComponentSize(g2Theme_CheckBox, Width, Height);
    *Width += GetTheme()->GetCharacterHeight() + Label->GetWidth();
}

void g2CheckBox::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // Draw based on the current state
    if(GetControllerState() == g2ControllerState_Clicked)
    {
        // Flip state
        Checked = !Checked;
        
        // Post if possible
        if(LiveCheckState != NULL)
            *LiveCheckState = Checked;
    }
}