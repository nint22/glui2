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
    CursorOffset = 0.0f;
    CursorIndex = 0;
    
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
        strcpy(TextBuffer, "");
        CursorIndex = 0;
    }
    // Only set if we can keep it in our internal buffer
    else if(strlen(Text) < g2LabelEdit_TextBufferLength - 1)
    {
        strcpy(TextBuffer, Text);
        CursorIndex = (int)strlen(TextBuffer);
    }
}

const char* const g2LabelEdit::GetText()
{
    return TextBuffer;
}

void g2LabelEdit::SetWidth(int Width)
{
    // Save to the current buffer
    if(Width > GetWidth())
        this->Width = Width;
    else
        Width = GetWidth();
}

int g2LabelEdit::GetWidth()
{
    // Error check
    if(strlen(TextBuffer) <= 0)
        return 0;
    
    // Else, just sum the character lengths to get the width
    int CharWidth, Sum = 0;
    for(size_t i = 0; i < strlen(TextBuffer); i++)
    {
        GetTheme()->GetCharacterSize(TextBuffer[i], &CharWidth);
        Sum += CharWidth + g2LabelEdit_CharacterSpacing;
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
    if(!OpenClipboard())
        return;
    
    // Allocate a system resource (a memory buffer for the text)
    HGLOBAL TextHandle = GlobalAlloc(GMEM_MOVEABLE, (strlen(TextBuffer) + 1) * sizeof(char));
    if(TextHandle == NULL)
        return;
    
    LPTSTR StringLock = GlobalLock(TextHandle);
    if(StringLock == NULL)
        return;
    strcpy(StringLock, TextBuffer);
    GlobalUnlock(TextHandle);
    
    // Open clipboard to write to
    if(OpenClipboard())
    {
        // Copy to the clipboard
        SetClipboardData(CF_TEXT, StringLock);
        
        // Close clipboard
        CloseClipboard();
    }
    
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
    if(!OpenClipboard())
        return;
    
    // Get the windows clipboard text buffer
    HGLOBAL ClipboardHandle = GetClipboardData(CF_TEXT);
    if(ClipboardHandle != NULL)
    {
        // Actually copy the text
        LPTSTR StringLock = GlobalLock(ClipboardHandle); 
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
                sprintf(TextBuffer, "%s%s", TempTextBuffer, TempClipBuffer);
            
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
                
                for(CFIndex i = 0; (i < DateLength) && (StartIndex + i < g2LabelEdit_TextBufferLength); i++)
                {
                    char byte = *(CFDataGetBytePtr(ItemData) + i);
                    TextBuffer[StartIndex + i] = byte;
                }
                
                // Cap string
                TextBuffer[StartIndex + DateLength] = '\0';
                
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
                DrawCharacter(pX + offset + 1, pY + level * height + 1, 1.0f, 1.0f, Sr, Sg, Sb, 0.2f, c);
            
            // Render text normally
            DrawCharacter(pX + offset, pY + level * height, 1.0f, 1.0f, c);
            
            // Get this character's width and offset
            int width;
            GetTheme()->GetCharacterSize(c, &width, NULL);
            offset += width + g2LabelEdit_CharacterSpacing;
        }
    }
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
        // If left/right, move the cursor
        if(key == GLUT_KEY_LEFT && CursorIndex > 0)
            CursorIndex--;
        else if(key == GLUT_KEY_RIGHT && CursorIndex < (int)strlen(TextBuffer))
            CursorIndex++;
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
                TextBuffer[strlen(TextBuffer) + 1] = '\0';
                int Length = (int)strlen(TextBuffer);
                for(int i = CursorIndex + 1; i <= Length; i++)
                    TextBuffer[i] = TextBuffer[i - 1];
                TextBuffer[CursorIndex] = key;
            }
            
            // Grow cursor position to be after the current char
            CursorIndex++;
        }
    }
    
    // All done for each type of event
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
