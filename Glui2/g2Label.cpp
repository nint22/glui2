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
        // Ignore if it is a color code (of form "\<int>")
        if(TextBuffer[i] == '\\')
        {
            // Attempt to read an integer
            int ColorID = -1;
            sscanf(TextBuffer + i + 1, "%2d", &ColorID);
            
            // Ignores up to 2 digits (So when the user gives \1234, we set it to color \12, and leave 34 alone)
            if(ColorID >= 0 && ColorID < 16)
            {
                i++; // Ignores the first slash
                for(int j = 0; j < 2 && TextBuffer[i] >= '0' && TextBuffer[i] <= '9'; j++)
                    i++;
            }
        }
        
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

void g2Label::GetTemplateColor(int Index, float* r, float* g, float* b)
{
    // Simple look-up table
    switch(Index)
    {
        case 0:  *r = 0.0f; *g = 0.0f; *b = 0.0f; break;
        case 1:  *r = 0.0f; *g = 0.0f; *b = 0.5f; break;
        case 2:  *r = 0.0f; *g = 0.5f; *b = 0.0f; break;
        case 3:  *r = 0.0f; *g = 0.5f; *b = 0.5f; break;
        case 4:  *r = 0.5f; *g = 0.0f; *b = 0.0f; break;
        case 5:  *r = 0.5f; *g = 0.0f; *b = 0.5f; break;
        case 6:  *r = 0.5f; *g = 0.3f; *b = 0.0f; break;
        case 7:  *r = 0.5f; *g = 0.5f; *b = 0.5f; break;
        case 8:  *r = 0.3f; *g = 0.3f; *b = 0.3f; break;
        case 9:  *r = 0.3f; *g = 0.3f; *b = 1.0f; break;
        case 10: *r = 3.0f; *g = 1.0f; *b = 0.3f; break;
        case 11: *r = 3.0f; *g = 1.0f; *b = 1.0f; break;
        case 12: *r = 1.0f; *g = 0.3f; *b = 0.3f; break;
        case 13: *r = 1.0f; *g = 0.3f; *b = 1.0f; break;
        case 14: *r = 1.0f; *g = 1.0f; *b = 0.3f; break;
        case 15: *r = 1.0f; *g = 1.0f; *b = 1.0f; break;
    }
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
    
    // Get regular text color
    float Tr, Tg, Tb, Alpha;
    GetColor(&Tr, &Tg, &Tb, &Alpha);
    
    // For each character...
    for(size_t i = 0; i < strlen(TextBuffer); i++)
    {
        // Reset for the next line
        if(TextBuffer[i] == '\n')
        {
            // Move to next line, reset cursor location, and reset color
            level++;
            offset = 0;
            GetColor(&Tr, &Tg, &Tb);
        }
        // Draw normally
        else
        {
            // Is this character a backslash?
            if(TextBuffer[i] == '\\')
            {
                // Attempt to read an integer
                int ColorID = -1;
                sscanf(TextBuffer + i + 1, "%2d", &ColorID);
                
                // Ignores up to 2 digits (So when the user gives \1234, we set it to color \12, and leave 34 alone)
                if(ColorID >= 0 && ColorID < 16)
                {
                    i++; // Ignores the first slash
                    for(int j = 0; j < 2 && TextBuffer[i] >= '0' && TextBuffer[i] <= '9'; j++)
                        i++;
                    g2Label::GetTemplateColor(ColorID, &Tr, &Tg, &Tb);
                }
            }
            
            // Render text normally if not null
            if(TextBuffer[i] != '\0')
            {
                // Draw shadow if on
                if(Shadow)
                    DrawCharacter(pX + offset + 1, pY + level * height + 1, Scale, Scale, Sr, Sg, Sb, 0.2f, TextBuffer[i]);
                
                // Draw regular text
                DrawCharacter(pX + offset, pY + level * height, Scale, Scale, Tr, Tg, Tb, Alpha, TextBuffer[i]);
                
                // Get this character's width and offset
                int width;
                GetTheme()->GetCharacterSize(TextBuffer[i], &width, NULL);
                offset += width + g2Label_CharacterSpacing;
            }
        }
    }
}
