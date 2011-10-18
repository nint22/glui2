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

g2Dialog::g2Dialog(g2DialogType Type, const char* Message, const char* Extension)
{
    // Suppress warning
    g2Assert(Message != NULL, "Given message buffer was null.");
    
    // Default user's choice to nothing
    this->Type = Type;
    Selection = g2DialogResult_Cancel;
    
    // Save the message
    strcpy(MessageBuffer, Message);

	// Copy the extension if any; default to blank if none
	strcpy(FileExtension, (Extension == NULL) ? "" : Extension);
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
            
			// Allocate the args list for opening file
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
			char szFileName[MAX_PATH] = "";
            
			// Set default flags
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = NULL;
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            
			// Set a file filter
            char szFileFilter[MAX_PATH];
			if(strlen(FileExtension) > 0)
				sprintf(szFileFilter, "(*.%s)\0*.%s\0", FileExtension, FileExtension);
			else
				strcpy(szFileFilter, "All Files (*.*)\0*.*\0");
            ofn.lpstrFilter = szFileFilter;
			ofn.lpstrDefExt = FileExtension;
			
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
            
			// Allocate the args list for opening file
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
			char szFileName[MAX_PATH] = "";
            
			// Set default flags
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = NULL;
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            
			// Set a file filter
            char szFileFilter[MAX_PATH];
			if(strlen(FileExtension) > 0)
				sprintf(szFileFilter, "(*.%s)\0*.%s\0", FileExtension, FileExtension);
			else
				strcpy(szFileFilter, "All Files (*.*)\0*.*\0");
            ofn.lpstrFilter = szFileFilter;
			ofn.lpstrDefExt = FileExtension;
			
            // Save file
            if(GetSaveFileName(&ofn))
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
    
    
    // Linux implementation block
    #elif __linux__
    
        // Ask by the command line
        // Note that linux users shouldn't run the program
        // that instances this application in the background
        // as we need access to standard I/O
        strcpy(ResultBuffer, "");
        
        if(Type == g2DialogType_Notification)
        {
            printf("Message: \"%s\"\n", MessageBuffer);
            Selection = g2DialogResult_OK;
            strcpy(ResultBuffer, "");
            return;
        }
        else if(Type == g2DialogType_Open)
            printf("\"%s\"> ", MessageBuffer);
        else if(Type == g2DialogType_Save)
            printf("\"%s\"> ", MessageBuffer);
        
        char* TempBuffer = NULL;
        if(scanf("%s", TempBuffer) > 0)
        {
            Selection = g2DialogResult_OK;
            
            // Special rule: if we are saving, make sure to
            // add the extension if it exists
            if(Type == g2DialogType_Save && strlen(FileExtension) > 0)
            {
                // If this file does not end in the extension...
                char* ExtLocation = strrchr(TempBuffer, '.');
                if(strcmp(ExtLocation + 1, FileExtension) != 0)
                    sprintf(ResultBuffer, "%s.%s", TempBuffer, FileExtension);
                // Else, it does, just copy it over
                else
                    strcpy(ResultBuffer, TempBuffer);
            }
            // Else, just do a regular copy
            else
                strcpy(ResultBuffer, TempBuffer);
        }
        else
        {
            Selection = g2DialogResult_Cancel;
            strcpy(ResultBuffer, "");
        }
        
    // Apple/OSX includes
    #elif __APPLE__
        
        // Attempt to execute the appropriate notification
        bool result = false;
        if(Type == g2DialogType_Notification)
            result = __g2ShowDialog(MessageBuffer);
        else if(Type == g2DialogType_Open)
            result = __g2ShowOpenDialog(MessageBuffer, FileExtension, ResultBuffer, g2Dialog_MaxBufferLength);
        else if(Type == g2DialogType_Save)
            result = __g2ShowSaveDialog(MessageBuffer, FileExtension, ResultBuffer, g2Dialog_MaxBufferLength);
        
        // Based on the result (i.e. button index) save
        // the correct enumeration type
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
