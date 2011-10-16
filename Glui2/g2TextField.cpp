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
    // Initialize nothing in the input buffer
    strcpy(TextBuffer, "");
    CursorTime = 0.0f;
    CursorState = true;
    CursorOffset = 0.0f;
    CursorIndex = 0;
    
    // Compute the offsets so the text is correctly centered
    int CharHeight = GetTheme()->GetCharacterHeight();
    GetTheme()->GetComponentSize(g2Theme_TextField, &OffsetWidth, &OffsetHeight);
    OffsetWidth *= 0.2f;
    OffsetHeight = OffsetHeight / 2 - CharHeight / 2 + 1;
    
    // Allocate the text label
    Label = new g2Label(this, MainTheme);
    Label->SetPos(OffsetWidth, OffsetHeight);
    Label->SetColor(0.0f, 0.0f, 0.0f);
    
    // Default width
    SetWidth(0);
    
    // Default to no filter mechanism
    FilterBuffer = NULL;
}

void g2TextField::SetText(const char* Text)
{
    // Default to empty buffer
    if(Text == NULL)
    {
        strcpy(TextBuffer, "");
        Label->SetText(TextBuffer);
        CursorIndex = 0;
    }
    // Only set if we can keep it in our internal buffer
    else if(strlen(Text) < TextBufferLength - 1)
    {
        strcpy(TextBuffer, Text);
        Label->SetText(TextBuffer);
        CursorIndex = (int)strlen(TextBuffer);
    }
}

const char* g2TextField::GetText()
{
    return TextBuffer;
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
}

int g2TextField::GetWidth()
{
    return Width;
}

g2Label* g2TextField::GetLabel()
{
    return Label;
}

void g2TextField::SetFilter(const char* Filter)
{
    // Release the previous filter (if it exists)
    if(FilterBuffer != NULL)
        delete[] FilterBuffer;
    
    // Are we no longer having a filter?
    if(Filter == NULL)
        FilterBuffer = NULL;
    
    // Allocate and copy
    else
    {
        FilterBuffer = new char[strlen(Filter) + 1];
        strcpy(FilterBuffer, Filter);
    }
}

void g2TextField::Update(float dT)
{
    // Update the timer and flip the state if needed
    CursorTime += dT;
    if(CursorTime > 0.5f)
    {
        CursorTime -= 0.5f;
        CursorState = !CursorState;
    }
}

void g2TextField::Render(int pX, int pY)
{
    /*** Draw Background (Text field) ***/
    
    // What state is the component currently in?
    g2ThemeElement TextFieldState = g2Theme_TextField;
    if(GetDisabled())
        TextFieldState = g2Theme_TextField_Disabled;
    
    // Render the background
    DrawComponent(TextFieldState, pX, pY, Width);
    
    /*** Draw Cursor (Only if active) ***/
    
    // Is this controller active? (i.e. selected?) and not disabled?
    if(GetActive() && !GetDisabled())
    {
        // What is the pixel offset?
        int CursorPos = 0;
        for(int i = 0; i < CursorIndex; i++)
        {
            int CharWidth;
            GetTheme()->GetCharacterSize(Label->GetText()[i], &CharWidth);
            CursorPos += CharWidth + 2;
        }
        
        float tR, tG, tB, tA;
        Label->GetColor(&tR, &tG, &tB, &tA);
        DrawCharacter(pX + OffsetWidth + CursorPos, pY + OffsetHeight, 1.0f, 1.0f, tR, tG, tB, tA, CursorState ? '|' : ' ');
    }
}

void g2TextField::GetCollisionRect(int* Width, int* Height)
{
    // Current GUI position and size
    GetTheme()->GetComponentSize(g2Theme_TextField, NULL, Height);
    *Width = GetWidth();
}
