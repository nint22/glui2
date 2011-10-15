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
    
    // Default the width to the minimum width of the source image
    GetTheme()->GetComponentSize(g2Theme_TextField, &Width);
    
    // Compute the offsets so the text is correctly centered
    int CharHeight;
    GetTheme()->GetCharacterSize('X', NULL, &CharHeight);
    
    GetTheme()->GetComponentSize(g2Theme_TextField, &OffsetWidth, &OffsetHeight);
    OffsetWidth *= 0.2f;
    OffsetHeight = OffsetHeight / 2 - CharHeight / 2 + 1;
    
    // Allocate the text label
    Label = new g2Label(this, MainTheme);
    Label->SetPos(OffsetWidth, OffsetHeight);
    Label->SetColor(0.0f, 0.0f, 0.0f);
    
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

void g2TextField::KeyEvent(unsigned char key, bool IsSpecial)
{
    // Ignore all inputs if disabled
    if(GetDisabled())
        return;
    
    // If system key (i.e. left/right)
    if(IsSpecial)
    {
        // If left/right, move the cursor
        if(key == GLUT_KEY_LEFT && CursorIndex > 0)
            CursorIndex--;
        else if(key == GLUT_KEY_RIGHT && CursorIndex < (int)strlen(TextBuffer))
            CursorIndex++;
    }
    // Else, normal character
    else
    {
        // In OSX the backspace maps to DEL while DEL maps to backspace, need to swap
        #if __APPLE__
            if(key == 127)
                key = 8;
            else if(key == 8)
                key = 127;
        #endif
        
        // Backspace
        if(key == 8)
        {
            // Is there anything to delete?
            if(strlen(TextBuffer) <= 0)
                return;
            // Ignore if we are at the 0 position
            else if(CursorIndex <= 0)
                return;
            else
            {
                // Delete this character by shifting everything from right to left by 1
                // Note that this copies the null terminator
                for(size_t i = CursorIndex; i <= strlen(TextBuffer); i++)
                    TextBuffer[i - 1] = TextBuffer[i];
                
                // Decrease the cursor position
                CursorIndex--;
            }
        }
        // Delete
        else if(key == 127)
        {
            // Is there anything to delete?
            if(CursorIndex >= (int)strlen(TextBuffer))
                return;
            else
            {
                // Delete this character by shifting everything from right to left by 1
                // Note that this copies the null terminator
                for(size_t i = CursorIndex; i < strlen(TextBuffer); i++)
                    TextBuffer[i] = TextBuffer[i + 1];
                
                // Cursor does not move
            }
        }
        // Standard keyboard input; add character
        else if(strlen(TextBuffer) < TextBufferLength - 1 && !IsSpecial)
        {
            // Ignore if it isn't a valid character
            if(!InFilter(key))
                return;
            
            // If we are writing to the end, make sure to string-cap
            if(CursorIndex == (int)strlen(TextBuffer))
            {
                // Write to the old string-end and move the terminator a little further
                TextBuffer[CursorIndex + 0] = key;
                TextBuffer[CursorIndex + 1] = '\0';
            }
            // Offset one char to the right, then set
            else
            {
                // Null-terminate the end of the string
                TextBuffer[strlen(TextBuffer) + 1] = '\0';
                int Length = (int)strlen(TextBuffer);
                for(int i = CursorIndex + 1; i <= Length; i++)
                    TextBuffer[i] = TextBuffer[i - 1];
                TextBuffer[CursorIndex] = key;
            }
            
            // Grow cursor position to be after the current char
            CursorIndex++;
        }
        
        // Update the text buffer
        Label->SetText(TextBuffer);
    }
}

bool g2TextField::InFilter(char c)
{
    // No filter active, accept all characters
    if(FilterBuffer == NULL)
        return true;
    
    // Linear search, just keep comparing
    for(size_t i = 0; i < strlen(FilterBuffer); i++)
        if(FilterBuffer[i] == c)
            return true;
    
    // Never found
    return false;
}
