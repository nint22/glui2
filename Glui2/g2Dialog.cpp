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
    // Nothing to release ...
}

void g2Dialog::Show()
{
    // Window implementation block
    #ifdef _WIN32
    
        if(Type == g2DialogType_Notification)
        {
            MessageBox(NULL, MessageBuffer, "GLUI2 - Message", MB_ICONINFORMATION);
        }
        else if(Type == g2DialogType_Open)
        {
            // Based on the MSDN article on open/saving dialogs
            // http://msdn.microsoft.com/en-us/library/windows/desktop/ms646829(v=vs.85).aspx
            
            char szFileName[MAX_PATH] = "";
            
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = NULL;
            ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            ofn.lpstrDefExt = 0;
            
            // Open file
            if(GetOpenFileName(&ofn))
            {
                strcpy(ResultBuffer, ofn.lpstrFile);
                Selection = g2DialogResult_OK;
            }
            else
            {
                strcpy(ResultBuffer, "");
                Selection = g2DialogResult_Cancel;
            }
        }
        else if(Type == g2DialogType_Save)
        {
            // Based on:
            // http://msdn.microsoft.com/en-us/library/windows/desktop/dd183519(v=VS.85).aspx
            
            char szFileName[MAX_PATH] = "";
            
			OPENFILENAME Ofn;
            Ofn.lStructSize = sizeof(OPENFILENAME); 
            Ofn.hwndOwner = NULL; 
            Ofn.lpstrFilter = "*.*"; 
            Ofn.lpstrFile= szFileName; 
            Ofn.nMaxFile = sizeof(szFileName)/ sizeof(*szFileName); 
            Ofn.lpstrFileTitle = "FileTitle";
            Ofn.nMaxFileTitle = sizeof("FileTitle"); 
            Ofn.lpstrInitialDir = (LPSTR)NULL; 
            Ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 
            Ofn.lpstrTitle = "Title!"; 
            
            // Display the Filename common dialog box. The  
            // filename specified by the user is passed  
            // to the CreateEnhMetaFile function and used to  
            // store the metafile on disk.  
            
            // Save file
            if(GetSaveFileName(&Ofn))
            {
                strcpy(ResultBuffer, Ofn.lpstrFile);
                Selection = g2DialogResult_OK;
            }
            else
            {
                strcpy(ResultBuffer, "");
                Selection = g2DialogResult_Cancel;
            }
        }
    
    
    // Linux implementation block
    #elif __linux__
    
        // Ask by the command line
        // Note that linux users shouldn't run the program
        // that instances this application in the background
        // as we need access to standard I/O
        strcpy(ResultBuffer, "");
        
        if(Type == g2DialogType_Notification)
            printf("Message: \"%s\"", MessageBuffer);
        else if(Type == g2DialogType_Open)
            printf("Open file directory: \"%s\"\n> ", MessageBuffer);
        else if(Type == g2DialogType_Save)
            printf("Save file directory: \"%s\"\n> ", MessageBuffer);
        
        char* TempBuffer = NULL;
        size_t ReadBuffer = 0;
        getline(&TempBuffer, &ReadBuffer, stdin);
        if(TempBuffer == NULL)
        {
            Selection = g2DialogResult_Cancel;
            strcpy(ResultBuffer, "");
        }
        else
        {
            Selection = g2DialogResult_OK;
            strcpy(ResultBuffer, TempBuffer);
        }
        
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
