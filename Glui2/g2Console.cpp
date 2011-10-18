/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Console.h"

// The start message of the input buffer
static const char* g2Console_InputBufferStart = "g2Console:> ";

// Only one console should be created at a time
static int g2Console_RefCount = 0;

g2Console::g2Console(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(NULL, MainTheme)
{
    // We should only create one console at a time
    g2Assert(g2Console_RefCount <= 0, "Only one g2Console can be allocated at a time!");
    g2Console_RefCount++;
    
    // Initialize the editable label
    LabelEdit = new g2LabelEdit(this, MainTheme);
    LabelEdit->SetCursorAlwaysVisible(true);
    LabelEdit->SetShadow(false);
    
    // Initialize the label itself
    Label = new g2Label(this, MainTheme);
    Label->SetText(g2Console_InputBufferStart);
    Label->SetColor(0.9f, 0.9f, 0.9f);
    Label->SetShadow(false);
    
    // Default initial message (has to be on the heap, can't be on the stack)
    char* Header = new char[128];
    strcpy(Header, "Welcome to g2Console; write any commands and press [Enter] to execute");
    ConsoleOut.push(Header);
}

g2Console::~g2Console()
{
    // For each input
    while(!ConsoleIn.empty())
    {
        delete[] ConsoleIn.front();
        ConsoleIn.pop();
    }
    
    // For each output
    while(!ConsoleOut.empty())
    {
        delete[] ConsoleOut.front();
        ConsoleOut.pop();
    }
    
    // Release console
    g2Console_RefCount--;
}

void g2Console::printf(const char* format, ...)
{
    // Convert into a valid buffer...
    va_list args;
    va_start(args, format);
    
    // Currently this is a naive approach because who knows how big
    // the output buffer will be? Thus, we will need to
    char buffer[1024];
    vsprintf(buffer, format, args);
    
    // Print to stdout; we don't use the classic "printf" since it
    // will call this class' implementation, leading to recursive calls
    fprintf(stdout, "g2Console: \"%s\"\n", buffer);
    
    // Copy and push
    char* newBuffer = new char[strlen(buffer) + 1];
    strcpy(newBuffer, buffer);
    ConsoleOut.push(newBuffer);
    
    // Too many in the console input? Release
    if(ConsoleOut.size() > 64)
    {
        char* temp = ConsoleOut.front();
        ConsoleOut.pop();
        delete[] temp;
    }
    
    // Done with args
    va_end(args);
}

void g2Console::gets(char* OutBuffer, int* Length)
{
    if(ConsoleIn.empty())
    {
        *Length = 0;
        OutBuffer[0] = '\0';
    }
    else
    {
        // Get from stack
        char* out = ConsoleIn.front();
        ConsoleIn.pop();
        
        // Copy to given buffer
        strcpy(OutBuffer, out);
        *Length = (int)strlen(OutBuffer);
        
        // Release internal buffer
        delete[] out;
    }
}

void g2Console::Render(int x, int y)
{
    /*** Check for new input ***/
    
    if(LabelEdit->UserReturned())
    {
        // Copy the buffer
        char* input = new char[strlen(LabelEdit->GetText()) + 1];
        strcpy(input, LabelEdit->GetText());
        
        // Clear out user input
        LabelEdit->SetText();
        
        // Check for quit, close, exit
        if(strcmp(input, "quit") == 0 || strcmp(input, "close") == 0 || strcmp(input, "exit") == 0)
        {
            this->SetVisibility(false);
            delete[] input;
            return;
        }
        
        // Push into our input stack
        ConsoleIn.push(input);
        
        // Create an extra buffer for drawing back to the user
        char* output = new char[strlen(":> ") + strlen(input) + 1];
        sprintf(output, "%s%s", ":>", input);
        
        // Push into our output stack
        ConsoleOut.push(output);
        
        // Check if either of the queues are too big
        while((int)ConsoleIn.size() > g2Console_MaxInputSize)
            ConsoleIn.pop();
        while((int)ConsoleOut.size() > g2Console_MaxInputSize)
            ConsoleOut.pop();
    }
    
    /*** Rendering ***/
    
    // Set the current color and alpha
    glColor4f(0, 0, 0, 0.5f);
    
    // Disable texture
    glDisable(GL_TEXTURE_2D);
    
    // Draw the console background
    float DestX = 0.0f;
    float DestY = 0.0f;
    float width = float(WindowWidth);
    float height = float(WindowHeight) / 2;
    
    glBegin(GL_QUADS);
        glVertex2f(DestX + 0, DestY + 0);
        glVertex2f(DestX + 0, DestY + height);
        glVertex2f(DestX + width, DestY + height);
        glVertex2f(DestX + width, DestY + 0);
    glEnd();
    
    // Reset color for console
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Cursor position (Pixel offsets to look better)
    int CharHeight = GetTheme()->GetCharacterHeight();
    CharHeight += 2;
    
    // 2 Pixel offset from the left, start two rows up so
    // we can have it on the gray console background AND
    // allow space for the input
    int cX = 2;
    int cY = WindowHeight / 2 - CharHeight * 3;
    
    // Render each character in our output buffer
    int OutLength = (int)ConsoleOut.size();
    for(int i = 0; i < OutLength; i++)
    {
        // Get the latest text
        char* Text = ConsoleOut.front();
        ConsoleOut.pop();
        
        // Get the default color
        float TempR, TempG, TempB, TempA;
        GetColor(&TempR, &TempG, &TempB, &TempA);
        
        // Print to screen
        for(size_t j = 0; j < strlen(Text); j++)
        {
            // Is this character a backslash?
            if(Text[j] == '\\')
            {
                // Attempt to read an integer
                int ColorID = -1;
                sscanf(Text + j + 1, "%d", &ColorID);
                if(ColorID >= 0 && ColorID < 16)
                {
                    // Change color and move ahead until non-numeric
                    do {
                        j++;
                    } while(Text[j] >= '0' && Text[j] <= '9');
                    GetTemplateColor(ColorID, &TempR, &TempG, &TempB);
                }
            }
            
            // Draw the shadow first
            DrawCharacter(cX, cY - (OutLength - i) * CharHeight, 1, 1, TempR, TempG, TempB, TempA, Text[j]);
            int CharWidth;
            GetTheme()->GetCharacterSize(Text[j], &CharWidth);
            cX += CharWidth + 2;
        }
        
        // Reset x position
        cX = 2;
        
        // Put back in
        ConsoleOut.push(Text);
    }
}

void g2Console::GetCollisionRect(int* Width, int* Height)
{
    // Post-back the size of this controller
    *Height = WindowHeight / 2;
    *Width = WindowWidth;
}

void g2Console::WindowResizeEvent(int NewWidth, int NewHeight)
{
    // Save
    WindowWidth = NewWidth;
    WindowHeight = NewHeight;
    
    // Update label positon
    // 5 pixel buffer on each side
    int HeightOffset = WindowHeight / 2 - GetTheme()->GetCharacterHeight() - 2;
    LabelEdit->SetPos(5 + Label->GetWidth(), HeightOffset);
    LabelEdit->SetWidth(WindowWidth - 10 - Label->GetWidth());
    Label->SetPos(5, HeightOffset);
}

void g2Console::GetTemplateColor(int Index, float* r, float* g, float* b)
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
