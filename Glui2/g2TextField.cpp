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
    strcpy(InputBuffer, "Empty...");
    CursorTime = 0.0f;
    CursorState = true;
}

void g2TextField::SetText(const char* Text)
{
    // Supress warning
    Text = NULL;
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
    // Draw something simple
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw based on the current state
    if(GetDisabled())
        DrawComponent(pX, pY, g2Theme_TextField_Disabled);
    else
        DrawComponent(pX, pY, g2Theme_TextField);
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
