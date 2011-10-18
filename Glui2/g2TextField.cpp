/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2TextField.h"

g2TextField::g2TextField(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Allocate the editable label and center
    TextEdit = new g2LabelEdit(this, MainTheme);
    
    // Center
    int CharHeight = GetTheme()->GetCharacterHeight();
    int ControllerHeight;
    GetTheme()->GetComponentSize(g2Theme_TextField, NULL, &ControllerHeight);
    TextEdit->SetPos(g2TextField_LabelEditOffset, ControllerHeight / 2 - CharHeight / 2);
    
    // Default to black
    TextEdit->SetColor(0.0f, 0.0f, 0.0f);
    
    // Default width
    SetWidth(0);
}

void g2TextField::SetText(const char* Text)
{
    TextEdit->SetText(Text);
}

const char* const g2TextField::GetText()
{
    return TextEdit->GetText();
}

g2LabelEdit* g2TextField::GetLabelEdit()
{
    return TextEdit;
}

void g2TextField::SetWidth(int Width)
{
    // What is the button's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_TextField, &MinWidth);
    
    if(Width > MinWidth)
        this->Width = Width;
    else
        this->Width = MinWidth;
    
    // Update the text field's width
    TextEdit->SetWidth(this->Width - 2 * g2TextField_LabelEditOffset);
}

int g2TextField::GetWidth()
{
    return Width;
}

void g2TextField::Render(int pX, int pY)
{
    /*** Draw Background (Text field) ***/
    
    // What state is the component currently in?
    g2ThemeElement TextFieldState = g2Theme_TextField;
    if(GetDisabled())
        TextFieldState = g2Theme_TextField_Disabled;
    
    // Render the background
    DrawComponentStretch(TextFieldState, pX, pY, Width);
    
    // The editable text field will draw itself
}

void g2TextField::GetCollisionRect(int* Width, int* Height)
{
    // Current GUI position and size
    GetTheme()->GetComponentSize(g2Theme_TextField, NULL, Height);
    *Width = GetWidth();
}
