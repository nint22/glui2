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
    Label = new g2Label(this, MainTheme);
    Label->SetColor(0, 0, 0);
    Label->SetText("Undefined g2Button");
    
    // Compute the label's offsets
    int ButtonHeight;
    GetTheme()->GetComponentSize(g2Theme_Button, NULL, &ButtonHeight);
    GetTheme()->GetCharacterSize(' ', &LabelOffsetX, &LabelOffsetY);
    LabelOffsetY = ButtonHeight / 2 - LabelOffsetY / 2;
    Label->SetPos(LabelOffsetX, LabelOffsetY);
    
    // Default width
    SetWidth(0);
    
    // Default the button's icon to none
    SetIcon();
    
    // Default alignment to left
    SetAlignment();
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
    // Note the 2x which is used as the forward and back space-buffering
    int NewLength = Label->GetWidth() + 2 * LabelOffsetX;
    
    // Is this new length bigger than the old width? If so, save
    if(NewLength > Width)
        SetWidth(NewLength);
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

int g2Button::GetWidth()
{
    return Width;
}

void g2Button::SetIcon(const char* IconName)
{
    // If null, make icon empty
    if(IconName == NULL)
        strcpy(UsingIcon, "");
    else
        strcpy(UsingIcon, IconName);
}

void g2Button::Render(int pX, int pY)
{
    // What component should we be rendering?
    g2ThemeElement ButtonState = g2Theme_Button;
    
    // Draw based on the current state
    if(GetDisabled())
        ButtonState = g2Theme_Button_Disabled;
    else if(GetControllerState() == g2ControllerState_Pressed)
        ButtonState = g2Theme_Button_Pressed;
    
    // Compute the label anchor offset
    int LabelAnchorOffset = 0;
    if(LabelAnchor == g2Anchor_Right)
        LabelAnchorOffset = GetWidth() - LabelOffsetX - Label->GetWidth();
    else if(LabelAnchor == g2Anchor_Center)
        LabelAnchorOffset = GetWidth() / 2 - (Label->GetWidth()) / 2;
    else
        LabelAnchorOffset = LabelOffsetX;
    
    // Shift the text bottom right by 1 pixel to make the
    // button look more active when being pressed
    if(ButtonState == g2Theme_Button_Pressed)
        Label->SetPos(LabelAnchorOffset, LabelOffsetY + 1);
    else
        Label->SetPos(LabelAnchorOffset, LabelOffsetY);
    
    // What is the button's minimum size?
    int MinWidth, ButtonHeight;
    GetTheme()->GetComponentSize(g2Theme_Button, &MinWidth, &ButtonHeight);
    
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
    
    // Draw the icon if we have one
    if(strlen(UsingIcon) > 0)
    {
        // Get the size of the component
        int IconWidth, IconHeight;
        GetTheme()->GetComponentSize(UsingIcon, &IconWidth, &IconHeight);
        
        // Computer the offsets
        int IconOffsetX = 5;
        int IconOffsetY = ButtonHeight / 2 - IconHeight / 2;
        
        // Draw icon centered to the left
        DrawComponent(pX + IconOffsetX, pY + IconOffsetY, UsingIcon);
        
        // Offset the text some more
        int LabelX, LabelY;
        Label->GetPos(&LabelX, &LabelY);
        Label->SetPos(LabelX + IconWidth, LabelY);
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

void g2Button::SetAlignment(g2Anchor Alignment)
{
    LabelAnchor = Alignment;
}
