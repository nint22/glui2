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
    SetText();
    CursorTime = 0.0f;
    CursorState = true;
    CursorIndex = 0;
    CursorAlwaysVisible = false;
    
    // User has yet to press enter
    DidUserReturn = false;
    
    // Default width of 100 pixels wide
    SetWidth(100);
    
    // Turn shadow off
    SetShadow(false);
    
    // Default to no filter mechanism
    FilterBuffer = NULL;
}

void g2LabelEdit::SetText(const char* Text)
{
    // Default to empty buffer
    if(Text == NULL)
    {
        // Copy over text and reset cursor and view offset
        strcpy(TextBuffer, "");
        CursorIndex = 0;
        ViewIndex = 0;
    }
    // Only set if we can keep it in our internal buffer
    else if((int)strlen(Text) < g2LabelEdit_TextBufferLength - 1)
    {
        // Copy and move the view over
        strcpy(TextBuffer, Text);
        ViewIndex = 0;
        
        // Clamp down
        if(CursorIndex > (int)strlen(TextBuffer))
            CursorIndex = (int)strlen(TextBuffer);
    }
}

const char* const g2LabelEdit::GetText()
{
    return TextBuffer;
}

void g2LabelEdit::SetCursorPos(int Index)
{
    // Bounds check
    if(Index < 0)
        CursorIndex = 0;
    else if(Index > (int)strlen(TextBuffer))
        CursorIndex = (int)strlen(TextBuffer);
    else
        CursorIndex = Index;
    
    // Update view position so that the cursor is to the right
    while(LengthToCursor() > Width)
        ViewIndex++;
}

int g2LabelEdit::GetCursorPos()
{
    return CursorIndex;
}

void g2LabelEdit::SetCursorAlwaysVisible(bool State)
{
    CursorAlwaysVisible = State;
}

bool g2LabelEdit::GetCursorAlwaysVisible()
{
    return CursorAlwaysVisible;
}

void g2LabelEdit::SetWidth(int Width)
{
    // Save the target width
    this->Width = Width;
}

int g2LabelEdit::GetWidth()
{
    // Return the current target length
    return Width;
}

void g2LabelEdit::SetShadow(bool State)
{
    Shadow = State;
}

bool g2LabelEdit::GetShadow()
{
    return Shadow;
}

void g2LabelEdit::SetFilter(const char* Filter)
{
    // Release the previous filter (if it exists)
    if(FilterBuffer != NULL)
        delete[] FilterBuffer;
    
    // Are we no longer having a filter?
    if(Filter == NULL)
        FilterBuffer = NULL;
    
    // Allocate and copy
    else
    {
        FilterBuffer = new char[strlen(Filter) + 1];
        strcpy(FilterBuffer, Filter);
    }
}

void g2LabelEdit::CopyBuffer()
{
    // Win32 implementation
    #ifdef _WIN32
    
        // Attempt to open clipboard
        if(!OpenClipboard(GetForegroundWindow()))
            return;
        
        // Empty current clipboard
        EmptyClipboard();
        
        // Allocate a system resource (a memory buffer for the text)
        HGLOBAL TextHandle = GlobalAlloc(GMEM_MOVEABLE, (strlen(TextBuffer) + 1) * sizeof(char));
        if(TextHandle == NULL)
            return;
        
        LPTSTR StringLock = (LPTSTR)GlobalLock(TextHandle);
        if(StringLock == NULL)
            return;
        strcpy(StringLock, TextBuffer);
        GlobalUnlock(TextHandle);
        
        // Copy to the clipboard
        SetClipboardData(CF_TEXT, TextHandle);
        
        // Close clipboard
        CloseClipboard();
    
    // OSX implementation
    #elif __APPLE__
    
        // Allocate or get a reference to the application's active clipboard
        PasteboardRef ClipboardHandle;
        if(PasteboardCreate(kPasteboardClipboard, &ClipboardHandle) != noErr)
            return;
        
        // Clear current clipboard
        if(PasteboardClear(ClipboardHandle) != noErr)
            return;
        
        // Explicitly update (after cleaning is important)
        PasteboardSynchronize(ClipboardHandle);
        
        // Create a system-wide buffer to give to the clipboard
        CFDataRef DataBuffer = CFDataCreate(kCFAllocatorDefault, (const UInt8*)TextBuffer, CFIndex((strlen(TextBuffer) + 1) * sizeof(char)));
        if(DataBuffer == NULL)
            return;
        
        // Paste into clipboard
        PasteboardPutItemFlavor(ClipboardHandle, (PasteboardItemID)1, CFSTR("public.utf8-plain-text"), DataBuffer, kPasteboardFlavorNoFlags);
    
    // Not a feature in Linux...
    #endif
}

void g2LabelEdit::PasteBuffer()
{
    // Win32 implementation
    #ifdef _WIN32
    
        // Attempt to open clipboard
        if(!OpenClipboard(GetForegroundWindow()))
            return;
        
        // Get the windows clipboard text buffer
        HGLOBAL ClipboardHandle = GetClipboardData(CF_TEXT);
        if(ClipboardHandle != NULL)
        {
            // Actually copy the text
            LPTSTR StringLock = (LPTSTR)GlobalLock(ClipboardHandle); 
            if (StringLock != NULL) 
            {
                // Copy as much as we can
                char TempClipBuffer[g2LabelEdit_TextBufferLength];
                strncpy(TempClipBuffer, StringLock, g2LabelEdit_TextBufferLength - strlen(TextBuffer) - strlen(StringLock) - 1);
                
                // Copy the current text buffer
                char TempTextBuffer[g2LabelEdit_TextBufferLength];
                strcpy(TempTextBuffer, TextBuffer);
                
                // Copy into the full buffer (only if text is small enough)
                if(strlen(TempTextBuffer) + strlen(TempClipBuffer) + 1 < g2LabelEdit_TextBufferLength)
                {
                    char NewTextBuffer[g2LabelEdit_TextBufferLength];
                    sprintf(NewTextBuffer, "%s%s", TempTextBuffer, TempClipBuffer);
                    SetText(NewTextBuffer);
                }
                
                // Release the lock
                GlobalUnlock(StringLock); 
            }
        }
        
        // Close clipboard
        CloseClipboard();
    
    // OSX implementation
    #elif __APPLE__
    
        // Allocate or get a reference to the application's active clipboard
        PasteboardRef ClipboardHandle;
        if(PasteboardCreate(kPasteboardClipboard, &ClipboardHandle) != noErr)
            return;
        
        // Explicitly update (possibly not needed...)
        PasteboardSynchronize(ClipboardHandle);
        
        // Get the item count
        ItemCount ClipboardItems;
        if(PasteboardGetItemCount(ClipboardHandle, &ClipboardItems) != noErr)
            return;
        
        // Keep searching until we find valid text
        for(ItemCount ItemIndex = 1; ItemIndex <= ClipboardItems; ItemIndex++)
        {
            // Get item's ID
            PasteboardItemID ItemID;
            if(PasteboardGetItemIdentifier(ClipboardHandle, ItemIndex, &ItemID) != noErr)
                continue;
            
            // Get this item's data types
            CFArrayRef ItemTypes;
            if(PasteboardCopyItemFlavors(ClipboardHandle, ItemID, &ItemTypes) != noErr)
                continue;
            
            // For each data type for this clipboard item
            CFIndex ItemCount = CFArrayGetCount(ItemTypes);
            for(CFIndex ItemTypeIndex = 0; ItemTypeIndex < ItemCount; ItemTypeIndex++)
            {
                // Get the data type
                CFStringRef ItemType = (CFStringRef)CFArrayGetValueAtIndex(ItemTypes, ItemTypeIndex);
                
                // If we have any text-type, then paste and stop
                if(UTTypeConformsTo(ItemType, CFSTR("public.utf8-plain-text")))
                {
                    // Copy from clipboard
                    CFDataRef ItemData;
                    if(PasteboardCopyItemFlavorData(ClipboardHandle, ItemID, ItemType, &ItemData) != noErr)
                        continue;
                    
                    // Paste into active buffer
                    CFIndex DateLength = CFDataGetLength(ItemData);
                    size_t StartIndex = strlen(TextBuffer);
                    
                    char NewTempBuffer[g2LabelEdit_TextBufferLength];
                    strcpy(NewTempBuffer, TextBuffer);
                    
                    for(CFIndex i = 0; (i < DateLength) && (StartIndex + i < g2LabelEdit_TextBufferLength); i++)
                    {
                        char byte = *(CFDataGetBytePtr(ItemData) + i);
                        NewTempBuffer[StartIndex + i] = byte;
                    }
                    
                    // Cap string and set to current buffer
                    NewTempBuffer[StartIndex + DateLength] = '\0';
                    SetText(NewTempBuffer);
                    SetCursorPos((int)strlen(NewTempBuffer));
                    
                    // Release
                    CFRelease(ItemData);
                    
                    // Pasted and done!
                    return;
                }
            }
        }
    
    // Not a feature in Linux...
    #endif
}

bool g2LabelEdit::UserReturned()
{
    if(DidUserReturn)
    {
        DidUserReturn = false;
        return true;
    }
    else
        return false;
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
    
    // Total offset from the far left
    int OffsetX = 0;
    
    // For each character...
    for(size_t i = ViewIndex; i < strlen(TextBuffer); i++)
    {
        // Get target character and width
        int CharWidth;
        GetTheme()->GetCharacterSize(TextBuffer[i], &CharWidth, NULL);
        
        // Stop drawing if this one or the next character is out of bounds
        if((OffsetX + CharWidth) >= Width)
            break;
        
        // Draw shadow if on
        if(Shadow)
        {
            // Get active color for shadow
            float Sr, Sg, Sb;
            GetColor(&Sr, &Sg, &Sb);
            DrawCharacter(pX + OffsetX + 1, pY + 1, 1.0f, 1.0f, Sr, Sg, Sb, 0.2f, TextBuffer[i]);
        }
        
        // Render text normally
        DrawCharacter(pX + OffsetX, pY, TextBuffer[i]);
        
        // Grow the offset
        OffsetX += CharWidth + g2LabelEdit_CharacterSpacing;
    }
    
    // Draw the blinking cursor
    if(( (GetActive() && !GetDisabled()) || CursorAlwaysVisible ) && CursorState)
    {
        // Reset offset for rendering again
        OffsetX = 0;
        
        // Go through each character attempting to render
        for(size_t i = ViewIndex; i <= strlen(TextBuffer); i++)
        {
            // Draw and stop at the cursor index
            if((int)i == CursorIndex)
            {
                DrawCharacter(pX + OffsetX - 1, pY, '|');
                break;
            }
            
            // Grow offset
            int CharWidth;
            GetTheme()->GetCharacterSize(TextBuffer[i], &CharWidth, NULL);
            OffsetX += CharWidth + g2LabelEdit_CharacterSpacing;
        }
    }
    
    // Done with rendering...
}

void g2LabelEdit::GetCollisionRect(int* Width, int* Height)
{
    *Width = this->Width;
    *Height = GetTheme()->GetCharacterHeight();
}

void g2LabelEdit::KeyEvent(unsigned char key, bool IsSpecial)
{
    // In OSX the backspace maps to DEL while DEL maps to backspace, need to swap
    #if __APPLE__
    if(key == 127)
        key = 8;
    else if(key == 8)
        key = 127;
    #endif
    
    // Ignore all inputs if disabled
    if(GetDisabled())
        return;
    
    /*** User Movement / Editing ***/
    
    // If system key (i.e. left/right)
    else if(IsSpecial)
    {
        // Move far left/right
        if(key == GLUT_KEY_LEFT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
        {
            CursorIndex = 0;
            ViewIndex = 0;
        }
        else if(key == GLUT_KEY_RIGHT && glutGetModifiers() == GLUT_ACTIVE_CTRL)
        {
            // Move the cursor to the far right and calculate
            // what is the best position for the view buffer to be moved to
            CursorIndex = (int)strlen(TextBuffer);
            
            // When something is written on-screen, check to see where our
            // left-view limit should be
            ViewIndex = (int)strlen(TextBuffer) - RenderableLeftChars(CursorIndex);
        }
        
        // If left/right, move the cursor
        if(key == GLUT_KEY_LEFT && CursorIndex > 0)
        {
            // Move cursor to left
            CursorIndex--;
            
            // Move view left if we can
            if(CursorIndex < ViewIndex)
                ViewIndex--;
        }
        else if(key == GLUT_KEY_RIGHT && CursorIndex < (int)strlen(TextBuffer))
        {
            // Move cursor to right
            CursorIndex++;
            
            // If the movement will cause us to be offsreen..
            while(LengthToCursor() > Width)
                ViewIndex++;
        }
    }
    
    // Backspace
    else if(key == 8)
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
            
            // Is the cursor now smaller than the current view index
            // Move view left if we can
            while(CursorIndex < ViewIndex)
            {
                ViewIndex -= 5;
                if(ViewIndex < 0)
                    ViewIndex = 0;
            }
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
    
    // Commit / enter
    else if(key == '\r')
    {
        DidUserReturn = true;
    }
    
    /*** Cut, Copy, or Paste ***/
    
    // Note that when doing a ctrl+key event, the given number
    // is offset from 'a', meaning true ascii = 'a' - key + 1
    
    // Cut text
    else if(key == ('x' - 'a' + 1) && glutGetModifiers() == GLUT_ACTIVE_CTRL)
    {
        // Copy into buffer, then set text to empty
        CopyBuffer();
        SetText("");
    }
    
    // Copy text
    else if(key == ('c' - 'a' + 1) && glutGetModifiers() == GLUT_ACTIVE_CTRL)
    {
        // Direct copy
        CopyBuffer();
    }
    
    // Paste text
    else if(key == ('v' - 'a' + 1) && glutGetModifiers() == GLUT_ACTIVE_CTRL)
    {
        // Direct paste
        PasteBuffer();
    }
    
    /*** Regular User Input ***/
    
    // Standard keyboard input; add character
    else if(isprint(key) != 0)
    {
        // Can we actually add anything?
        if(strlen(TextBuffer) < g2LabelEdit_TextBufferLength - 1 && !IsSpecial)
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
                int Length = (int)strlen(TextBuffer);
                for(int i = Length; i > CursorIndex; i--)
                    TextBuffer[i] = TextBuffer[i - 1];
                TextBuffer[CursorIndex] = key;
                TextBuffer[Length + 1] = '\0';
            }
            
            // Grow cursor position to be after the current char
            CursorIndex++;
        }
        
        // If the movement will cause us to be offsreen..
        while(LengthToCursor() > Width)
            ViewIndex++;
    }
    
    // All done for each type of event
}

void g2LabelEdit::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // If we are pressing and it's a left click, compute the best position
    if(InController(x, y) && button == g2MouseButton_Left && state == g2MouseClick_Down)
    {
        // Current offset of the character testing
        int OffsetX = 0;
        bool NewOffset = false;
        
        // Compute the best possible position
        for(size_t i = ViewIndex; i < strlen(TextBuffer) && !NewOffset; i++)
        {
            // Get this character's width and offset
            int ThisWidth, NextWidth;
            GetTheme()->GetCharacterSize(TextBuffer[i], &ThisWidth, NULL);
            GetTheme()->GetCharacterSize(TextBuffer[i + 1], &NextWidth, NULL);
            
            // Check for collision (little ceil hack with integers)
            if(x <= (OffsetX + (NextWidth + 1) / 2))
            {
                CursorIndex = (int)i;
                NewOffset = true;
            }
            
            // Grow the offset over time
            OffsetX += ThisWidth + g2LabelEdit_CharacterSpacing;
        }
        
        // If no new offset, assume it is to far right
        if(!NewOffset)
            CursorIndex = (int)strlen(TextBuffer);
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

int g2LabelEdit::RenderableLeftChars(int Index)
{
    // Total length
    int TotalLength = 0;
    int TotalCount = 0;
    
    // Starting from the given index, keep going down the text buffer
    for(int i = Index - 1; i >= 0; i--)
    {
        // Get the size of the current character
        int CharacterWidth;
        GetTheme()->GetCharacterSize(TextBuffer[i], &CharacterWidth);
        
        // Add to total length
        TotalLength += CharacterWidth + g2LabelEdit_CharacterSpacing;
        
        // If the buffer ever gets too big, then return the max index
        if(TotalLength > Width)
            return TotalCount;
        else
            TotalCount++;
    }
    
    // We can render everything
    return TotalCount;
}

int g2LabelEdit::LengthToCursor()
{
    // Total length
    int TotalLength = 0;
    
    // Starting from the given index, keep going down the text buffer
    for(int i = ViewIndex; i < CursorIndex; i++)
    {
        // Get the size of the current character
        int CharacterWidth;
        GetTheme()->GetCharacterSize(TextBuffer[i], &CharacterWidth);
        
        // Add to total length
        TotalLength += CharacterWidth + g2LabelEdit_CharacterSpacing;
    }
    
    // Send the entire length
    return TotalLength;
}
