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
    strcpy(InputBuffer, "Default g2TextField");
    CursorTime = 0.0f;
    CursorState = true;
    
    // Set text color to black
    tR = tG = tB = 0.0f;
    
    // Default the width to the minimum width of the source image
    GetTheme()->GetComponentSize(g2Theme_TextField, &Width);
}

void g2TextField::SetText(const char* Text)
{
    // Copy an empty string if the text is null
    if(Text == NULL)
        strcpy(InputBuffer, "");
    
    // Make sure the text isn't too long
    // +1 is for the terminator
    else if(strlen(Text) + 1 < MaxInputLength)
        strcpy(InputBuffer, Text);
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

void g2TextField::SetTextColor(float r, float g, float b)
{
    // Min/max bounds to [0.0, 1.0]
    tR = fmax(fmin(r, 1.0f), 0.0f);
    tG = fmax(fmin(g, 1.0f), 0.0f);
    tB = fmax(fmin(b, 1.0f), 0.0f);
}

void g2TextField::GetTextColor(float* r, float* g, float* b)
{
    if(r != NULL)
        *r = tR;
    if(g != NULL)
        *g = tG;
    if(b != NULL)
        *b = tB;
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

void g2TextField::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    /*** Draw Background (Text field) ***/
    
    // What state is the component currently in?
    g2ThemeElement TextFieldState = g2Theme_TextField;
    if(GetDisabled())
        TextFieldState = g2Theme_TextField_Disabled;
    
    // What is this controller's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_TextField, &MinWidth);
    
    // If default size, just render normally
    if(Width == MinWidth)
        DrawComponent(pX, pY, TextFieldState);
    
    // Else, we have to draw the two sides and stretch the middle
    else
    {
        // Source texture coordinates
        float SourceX, SourceY, SourceWidth, SourceHeight;
        int OutWidth, OutHeight;
        GetTheme()->GetComponent(TextFieldState, &SourceX, &SourceY, &SourceWidth, &SourceHeight, &OutWidth, &OutHeight);
        
        // Draw the left-most third
        DrawComponent(pX, pY, OutWidth / 3, OutHeight, SourceX, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the right-most third
        DrawComponent(pX + Width - OutWidth / 3, pY, OutWidth / 3, OutHeight, SourceX + (2.0f * SourceWidth) / 3.0f, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the middle two positions
        // Note the overlap between the middle's right side and the right side's left lip
        // This is to make sure there isn't a pixel space
        DrawComponent(pX + OutWidth / 3.0f, pY, Width - (2.0f * OutWidth) / 3.0f + 1, OutHeight, SourceX + SourceWidth / 3.0f, SourceY, SourceWidth - (2.0f * SourceWidth) / 3.0f, SourceHeight);
    }
    
    /*** Draw Foreground (Text itself) ***/
    
    // How large is this text in pixels?
    int CharWidth = 0;
    GetTheme()->GetCharacterSize(&CharWidth);
    int StringWidth = CharWidth * (int)strlen(InputBuffer);
    
    // Swap colors from the component's color to the text color
    float tempR, tempG, tempB;
    GetColor(&tempR, &tempG, &tempB);
    SetColor(tR, tG, tB);
    
    // If the string width is shorter than the current width, render normally
    if(StringWidth < Width)
    {
        for(int i = 0; i < (int)strlen(InputBuffer); i++)
            DrawCharacter(pX + CharWidth * i, pY, InputBuffer[i]);
    }
    
    // Set the color back
    SetColor(tempR, tempG, tempB);
}

bool g2TextField::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_TextField, &width, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}

void g2TextField::KeyEvent(unsigned char key)
{
    printf("input: '%c'\n", key);
    
    // Backspace (8 on windows, 127 on OSX)
    if(key == 8 || key == 127)
    {
        // Move back the buffer if there is space
        if(strlen(InputBuffer) > 0)
            InputBuffer[strlen(InputBuffer) - 1] = '\0';
    }
    // Standard keyboard input
    else
    {
        // Accepts all characters (ignore if not enough memory)
        size_t length = strlen(InputBuffer);
        if(length + 1 >= MaxInputLength)
            return;
        
        // Write to the old string-end and move the terminator a little further
        InputBuffer[length + 0] = key;
        InputBuffer[length + 1] = '\0';
    }
}
