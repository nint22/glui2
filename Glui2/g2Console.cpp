/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Console.h"

// The start message of the input buffer
static const char* InputBufferStart = "g2Console:>";

// Only one console should be created at a time
static int g2Console_RefCount = 0;

g2Console::g2Console(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(NULL, MainTheme)
{
    // We should only create one console at a time!
    g2Assert(g2Console_RefCount <= 0, "Only one g2Console can be allocated at a time!");
    g2Console_RefCount++;
    
    // Initialize nothing in the input buffer
    strcpy(InputBuffer, InputBufferStart);
    CursorTime = 0.0f;
    CursorState = true;
    
    // Default initial message (has to be on the heap, can't be on the stack)
    char* FirstMessage = new char[128];
    strcpy(FirstMessage, "Welcome to g2Console; write any commands and press [Enter] to execute");
    ConsoleOut.push(FirstMessage);
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

char* g2Console::gets()
{
    if(ConsoleIn.empty())
        return NULL;
    else
    {
        char* out = ConsoleIn.front();
        ConsoleIn.pop();
        return out;
    }
}

void g2Console::Update(float dT)
{
    // Update the timer and flip the state if needed
    CursorTime += dT;
    if(CursorTime > 0.5f)
    {
        CursorTime -= 0.5f;
        CursorState = !CursorState;
    }
}

void g2Console::Render(int x, int y)
{
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
    int CharHeight;
    GetTheme()->GetCharacterSize('X', &CharHeight);
    CharHeight += 1;
    
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
    
    // Reset cursor to bottom left
    cX = 2;
    cY = WindowHeight / 2 - CharHeight;
    
    // Print the buffer with the flickering cursor
    char InputBuffer_Cursor[MaxInputLength];
    sprintf(InputBuffer_Cursor, "%s%c", InputBuffer, CursorState ? '_' : ' ' );
    
    // Draw the input buffer
    for(size_t i = 0; i < strlen(InputBuffer_Cursor); i++)
    {
        DrawCharacter(cX, cY, InputBuffer_Cursor[i]);
        int CharWidth;
        GetTheme()->GetCharacterSize(InputBuffer_Cursor[i], &CharWidth);
        cX += CharWidth + 2;
    }
}

bool g2Console::InController(int x, int y)
{
    // Suppress x warning
    x = x;
    
    // If in the top half..
    if(y < WindowHeight / 2)
        return true;
    else
        return false;
}

void g2Console::WindowResizeEvent(int NewWidth, int NewHeight)
{
    WindowWidth = NewWidth;
    WindowHeight = NewHeight;
}

void g2Console::KeyEvent(unsigned char key, bool IsSpecial)
{
    // TODO: COALESCE THIS CODE WITH NEW INPUT METHODS
    IsSpecial = IsSpecial;
    
    // Are we executing our command?
    if(key == '\r')
    {
        // Move buffer to heap
        char* buffer = new char[strlen(InputBuffer) - strlen(InputBufferStart) + 1];
        strcpy(buffer, InputBuffer + strlen(InputBufferStart));
        
        // Are we closing the console?
        if(strcmp(buffer, "close") == 0 || strcmp(buffer, "quit") == 0 || strcmp(buffer, "exit") == 0)
        {
            // No need to keep the buffer, just clear
            delete[] buffer;
            SetVisibility(false);
        }
        
        // Save to the input buffer and push to the standard printf
        ConsoleIn.push(buffer);
        this->printf("%s", buffer);
        
        // Reset the input buffer
        strcpy(InputBuffer, InputBufferStart);
        
    }
    // Backspace (8 on windows, 127 on OSX)
    else if(key == 8 || key == 127)
    {
        // Move back the buffer if there is space
        if(strlen(InputBuffer) > strlen(InputBufferStart))
            InputBuffer[strlen(InputBuffer) - 1] = '\0';
    }
    // Standard keyboard input
    else
    {
        // Accepts all characters (ignore if not enough memory)
        int length = (int)strlen(InputBuffer);
        if(length + 1 >= MaxInputLength)
            return;
        
        // Write to the old string-end and move the terminator a little further
        InputBuffer[length + 0] = key;
        InputBuffer[length + 1] = '\0';
    }
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
