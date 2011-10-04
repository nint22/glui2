/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Button.h"

g2Button::g2Button(g2Controller* Parent, g2Theme* MainTheme)
    : g2Controller(Parent, MainTheme)
{
    // Allocate text and set initial position
    // Note that we are registereting to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(5, 5);
    Label->SetColor(0, 0, 0);
    Label->SetText("Undefined g2Button");
    
    // Set the initial width to a default width value
    GetTheme()->GetComponentSize(g2Theme_Button, &Width);
}

g2Label* g2Button::GetLabel()
{
    return Label;
}

void g2Button::SetText(const char* Text)
{
    // Change the label itself (empty text if null)
    Label->SetText(Text == NULL ? "" : Text);
    
    // What is the new length of this text?
    int NewLength = Label->GetWidth();
    
    // Is this new length bigger than the old width? If so, save
    if(NewLength > Width)
        Width = NewLength;
}

void g2Button::SetWidth(int Width)
{
    // What is the button's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_Button, &MinWidth);
    
    if(Width > MinWidth)
        this->Width = Width;
    else
        this->Width = MinWidth;
}

void g2Button::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // What component should we be rendering?
    g2ThemeElement ButtonState = g2Theme_Button;
    
    // Draw based on the current state
    if(GetDisabled())
        ButtonState = g2Theme_Button_Disabled;
    else if(GetControllerState() == g2ControllerState_Pressed)
        ButtonState = g2Theme_Button_Pressed;
    
    // Shift the text bottom right by 1 pixel to make the
    // text label look more active
    if(ButtonState == g2Theme_Button_Pressed)
        Label->SetPos(pX + 5, pY + 6);
    else
        Label->SetPos(pX + 5, pY + 5);
    
    // What is the button's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_Button, &MinWidth);
    
    // If default size, just render normally
    if(Width == MinWidth)
        DrawComponent(pX, pY, ButtonState);
    
    // Else, we have to draw the two sides and stretch the middle
    else
    {
        // Source texture coordinates
        float SourceX, SourceY, SourceWidth, SourceHeight;
        int OutWidth, OutHeight;
        GetTheme()->GetComponent(ButtonState, &SourceX, &SourceY, &SourceWidth, &SourceHeight, &OutWidth, &OutHeight);
        
        // Draw the left-most third
        DrawComponent(pX, pY, OutWidth / 3, OutHeight, SourceX, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the right-most third
        DrawComponent(pX + Width - OutWidth / 3, pY, OutWidth / 3, OutHeight, SourceX + (2.0f * SourceWidth) / 3.0f, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the middle two positions
        // Note the overlap between the middle's right side and the right side's left lip
        // This is to make sure there isn't a pixel space
        DrawComponent(pX + OutWidth / 3.0f, pY, Width - (2.0f * OutWidth) / 3.0f + 1, OutHeight, SourceX + SourceWidth / 3.0f, SourceY, SourceWidth - (2.0f * SourceWidth) / 3.0f, SourceHeight);
    }
}

bool g2Button::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_Button, NULL, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + Width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
