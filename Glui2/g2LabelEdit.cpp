/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2LabelEdit.h"

g2LabelEdit::g2LabelEdit(g2Controller* Parent, g2Theme* MainTheme)
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

g2LabelEdit::~g2LabelEdit()
{
    if(TextBuffer != NULL)
        delete[] TextBuffer;
}

void g2LabelEdit::SetText(const char* Text)
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

const char* g2LabelEdit::GetText()
{
    return TextBuffer;
}

void g2LabelEdit::SetSize(float Scale)
{
    this->Scale = Scale;
}

int g2LabelEdit::GetWidth()
{
    // Error check
    if(TextBuffer == NULL)
        return 0;
    
    // Else, just sum the character lengths to get the width
    int CharWidth, Sum = 0;
    for(size_t i = 0; i < strlen(TextBuffer); i++)
    {
        GetTheme()->GetCharacterSize(TextBuffer[i], &CharWidth);
        Sum += CharWidth + CharacterSpacing;
    }
    return Sum;
}

void g2LabelEdit::SetShadow(bool State)
{
    Shadow = State;
}

bool g2LabelEdit::GetShadow()
{
    return Shadow;
}

void g2LabelEdit::Update(float dT)
{
    // Update the timer and flip the state if needed
    CursorTime += dT;
    if(CursorTime > 0.5f)
    {
        CursorTime -= 0.5f;
        CursorState = !CursorState;
    }
}

void g2LabelEdit::Render(int pX, int pY)
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
            offset += width + CharacterSpacing;
        }
    }
}

bool g2LabelEdit::InFilter(char c)
{
    // No filter active, accept all characters
    if(FilterBuffer == NULL)
        return true;
    
    // Note to self: I could use a map to speed this up from linear
    // time to constant time, but since these are user input events,
    // speed isn't too critical
    // Linear search, just keep comparing
    for(size_t i = 0; i < strlen(FilterBuffer); i++)
        if(FilterBuffer[i] == c)
            return true;
    
    // Never found
    return false;
}

void g2LabelEdit::::KeyEvent(unsigned char key, bool IsSpecial)
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
