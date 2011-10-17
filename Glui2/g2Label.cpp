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
    Shadow = true;
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

const char* const g2Label::GetText()
{
    return TextBuffer;
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
    
    // Else, just sum the character lengths to get the width
    int CharWidth, Sum = 0;
    for(size_t i = 0; i < strlen(TextBuffer); i++)
    {
        GetTheme()->GetCharacterSize(TextBuffer[i], &CharWidth);
        Sum += CharWidth + g2Label_CharacterSpacing;
    }
    return Sum;
}

void g2Label::SetShadow(bool State)
{
    Shadow = State;
}

bool g2Label::GetShadow()
{
    return Shadow;
}

void g2Label::Render(int pX, int pY)
{
    // Ignore if not null
    if(TextBuffer == NULL)
        return;
    
    // Get character size
    int height;
    GetTheme()->GetCharacterSize(' ', NULL, &height);
    
    // Added a pixel offset; visual improvement
    height += 1;
    
    // Character positioning
    int level = 0;
    int offset = 0;
    
    // Get active color for shadow
    float Sr, Sg, Sb;
    GetColor(&Sr, &Sg, &Sb);
    
    // For each character...
    for(size_t i = 0; i < strlen(TextBuffer); i++)
    {
        // Get char and character information
        char c = TextBuffer[i];
        
        // Reset for the next line
        if(c == '\n')
        {
            level++;
            offset = 0;
        }
        // Draw normally
        else
        {
            // Draw shadow if on
            if(Shadow)
                DrawCharacter(pX + offset + 1, pY + level * height + 1, Scale, Scale, Sr, Sg, Sb, 0.2f, c);
            
            // Render text normally
            DrawCharacter(pX + offset, pY + level * height, Scale, Scale, c);
            
            // Get this character's width and offset
            int width;
            GetTheme()->GetCharacterSize(c, &width, NULL);
            offset += width + g2Label_CharacterSpacing;
        }
    }
}
