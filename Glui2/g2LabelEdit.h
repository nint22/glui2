/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2LabelEdit.cpp/h
 Desc: An interactive text field; based on source originally
 written for the console and g2TextField, but then coalescted
 together. You can enable / disabled text filtering (i.e. only
 allow numerical-input_, copy / pasting to and back from the host
 OS (Win and OSX feature only), and on-screen clipping based on
 a target width and user's cursor position. Shadow is off by
 default but can be turned on. Default width is 0.
 
***************************************************************/

// Inclusion guard
#ifndef __G2LABELEDIT_H__
#define __G2LABELEDIT_H__

#include "g2Controller.h"

// Number if pixels between characters draw on-screen
static const int g2LabelEdit_CharacterSpacing = 2;

// User input's text buffer
static const int g2LabelEdit_TextBufferLength = 1024;

class g2LabelEdit : public g2Controller
{
public:
    
    // Label constructor and destructor
    __g2EXPORT g2LabelEdit(g2Controller* Parent, g2Theme* MainTheme);
    
    // Set the text string; the user's cursor will be given back
    __g2EXPORT void SetText(const char* Text = NULL);
    
    // Return a constant buffer to the given string; should never be modified
    // The returned buffer may or may not exist soon after the direct call; you should
    // copy the buffer as soon as possible if it is to not be immediately used
    __g2EXPORT const char* const GetText();
    
    // Set the cursor's position; it will be placed after the target index
    // and before the following letter
    __g2EXPORT void SetCursorPos(int Index);
    
    // Return the current cursor position
    __g2EXPORT int GetCursorPos();
    
    // Force-set the cursor to visible or not; if set to true, the cursor
    // is visible regardless of the active state
    // Default to false, so the state is based on active selection
    __g2EXPORT void SetCursorAlwaysVisible(bool State);
    
    // Get the current cursor state; regardless of the flashing pattern, this
    // function will return true if the controller is explicitly showing the cursor
    // Default to false, so the state is based on active selection
    __g2EXPORT bool GetCursorAlwaysVisible();
    
    // Set the target width of the text input
    __g2EXPORT void SetWidth(int Width);
    
    // Get the width of the text input
    __g2EXPORT int GetWidth();
    
    // Set a shadow (true to render a shadow with text)
    __g2EXPORT void SetShadow(bool State);
    
    // Get the shadow state (true if shadow is visible)
    __g2EXPORT bool GetShadow();
    
    // Set a filter; an array of characters that are the only allowed input
    // characters. Pass null to remove the filter
    __g2EXPORT void SetFilter(const char* Filter = NULL);
    
    // Copy into the host operating system's copy-buffer
    __g2EXPORT void CopyBuffer();
    
    // Paste (by appending) from the host's operating system's
    // copy-buffer into this text buffer
    __g2EXPORT void PasteBuffer();
    
    // User has pressed enter; once this function returns true, the
    // return state is reset back to false
    __g2EXPORT bool UserReturned();
    
protected:
    
    // Update
    __g2EXPORT void Update(float dT);
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Standard collision body
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
    // Handle all key events the user executes
    __g2EXPORT void KeyEvent(unsigned char key, bool IsSpecial);
    
    // When the user clicks, center the cursor as best as possible
    __g2EXPORT void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
private:
    
    // Set a filter for this text
    bool InFilter(char c);
    
    // Returns the number of characters that can be rendered
    // on-screen to the left given the coordinate
    int RenderableLeftChars(int Index);
    
    // Number of pixels between the cursor and the start of
    // the rendered offset
    int LengthToCursor();
    
    // Internal width
    int Width;
    
    // Shadow state
    bool Shadow;
    
    // Current text buffer
    char TextBuffer[g2LabelEdit_TextBufferLength];
    
    // Filter buffer
    char* FilterBuffer;
    
    /** Cursor States **/
    
    // The total time the cursor has been in the current cursor style
    float CursorTime;
    
    // The current cursor state (on is '|', off is ' ')
    bool CursorState;
    
    // Index position of the cursor
    int CursorIndex;
    
    // View offset
    int ViewIndex;
    
    // Force flashing on regarldess of active state
    bool CursorAlwaysVisible;
    
    // Has the user commited the change (i.e. pressed the 'Enter' key?)
    bool DidUserReturn;
};

// End of inclusion guard
#endif
