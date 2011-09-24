/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Console.h"

// The start message of the input buffer
static const char* InputBufferStart = "g2Console:>";

g2Console::g2Console(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
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

void g2Console::Render()
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
    int CharWidth, CharHeight;
    GetTheme()->GetCharacterSize(&CharWidth, &CharHeight);
    CharHeight += 1;
    CharWidth -= 1;
    
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
        
        // Print to screen
        for(size_t j = 0; j < strlen(Text); j++)
        {
            DrawCharacter(cX, cY - (OutLength - i) * CharHeight, Text[j]);
            cX += CharWidth;
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
        cX += CharWidth;
    }
}

bool g2Console::InController(int x, int y)
{
    // Supress x warning
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

void g2Console::KeyEvent(unsigned char key)
{
    // Are we executing our command?
    if(key == '\r')
    {
        // Move buffer to heap
        char* buffer = new char[strlen(InputBuffer) - strlen(InputBufferStart) + 1];
        strcpy(buffer, InputBuffer + strlen(InputBufferStart));
        
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
        size_t length = strlen(InputBuffer);
        if(length + 1 >= MaxInputLength)
            return;
        
        // Write to the old string-end and move the terminator a little further
        InputBuffer[length + 0] = key;
        InputBuffer[length + 1] = '\0';
    }
}
