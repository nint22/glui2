/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Label.h"

g2Label::g2Label(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    TextBuffer = NULL;
    Scale = 1.0f;
}

g2Label::~g2Label()
{
    if(TextBuffer != NULL)
        delete[] TextBuffer;
}

void g2Label::SetText(const char* Text)
{
    // Release previous buffer
    if(TextBuffer != NULL)
        delete[] TextBuffer;
    
    // Set to null if given null
    if(Text == NULL)
        TextBuffer = NULL;
    else
    {
        // Allocate and copy buffer
        TextBuffer = new char[strlen(Text) + 1];
        strcpy(TextBuffer, Text);
    }
}

void g2Label::SetSize(float Scale)
{
    this->Scale = Scale;
}

int g2Label::GetWidth()
{
    // Error check
    if(TextBuffer == NULL)
        return 0;
    
    // Else, just the number of chars x pixel width
    int CharWidth = 0;
    GetTheme()->GetCharacterSize(&CharWidth);
    return CharWidth * (int)strlen(TextBuffer);
}

void g2Label::Render()
{
    // Ignore if not null
    if(TextBuffer == NULL)
        return;
    
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Get character size
    int width, height;
    GetTheme()->GetCharacterSize(&width, &height);
    
    // Added a pixel offset; visual improvement
    width -= 1;
    height += 1;
    
    // Character positioning
    int level = 0;
    int offset = 0;
    
    // For each character...
    for(size_t i = 0; i < strlen(TextBuffer); i++)
    {
        // Get char and character information
        char c = TextBuffer[i];
        if(c == '\n')
        {
            // Reset for the next line
            level++;
            offset = 0;
        }
        else
        {
            // Render text normally
            DrawCharacter(pX + offset++ * width, pY + level * height, Scale, Scale, c);
        }
    }
}
