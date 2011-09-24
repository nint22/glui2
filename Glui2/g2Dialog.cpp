/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Dialog.h"

#ifdef __APPLE__
    #include "g2AppKit.h"
#endif

g2Dialog::g2Dialog(g2DialogType Type, const char* Message)
{
    // Supress warning
    g2Assert(Message != NULL, "Given message buffer was null.");
    
    // Default user's choice to nothing
    this->Type = Type;
    Selection = g2DialogResult_Cancel;
    
    // Save the message
    strcpy(MessageBuffer, Message);
}

g2Dialog::~g2Dialog()
{
    
}

void g2Dialog::Show()
{
    // Window implementation block
    #ifdef _WIN32
    
        // Todo...
        
        char szFileName[MAX_PATH] = "";
        
        OPENFILENAME ofn;
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hwnd;
        ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
        ofn.lpstrFile = szFileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
        ofn.lpstrDefExt = 0;
        
        if(GetOpenFileName(&ofn)) {
            loadfile(szFileName);
        }
    
    // Linux implementation block
    #elif __linux__
    
    // Todo...
    
    // Apple/OSX includes
    #elif __APPLE__
        
        // Attempt to execute the appropriate notification
        bool result = false;
        if(Type == g2DialogType_Notification)
            result = __g2ShowDialog(MessageBuffer);
        else if(Type == g2DialogType_Open)
            result = __g2ShowOpenDialog(MessageBuffer, ResultBuffer, MaxBufferLength);
        else if(Type == g2DialogType_Save)
            result = __g2ShowSaveDialog(MessageBuffer, ResultBuffer, MaxBufferLength);
        
        // Based on the result (i.e. button index) save
        // the corrent enumeration type
        if(result == true)
            Selection = g2DialogResult_OK;
        else
            Selection = g2DialogResult_Cancel;
        
    #endif
}

g2DialogResult g2Dialog::GetInput(char** result)
{
    // Copy if a buffer was given
    if(result != NULL)
    {
        *result = new char[strlen(ResultBuffer) + 1];
        strcpy(*result, ResultBuffer);
    }
    
    // Return the user's selection
    return Selection;
}
