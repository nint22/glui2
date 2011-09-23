/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Dialog.cpp/h
 Desc: A wrapper for the host operating-system's generic dialog
 boxes. For Windows we use "MessageBox(...)", for OSX we use
 "CreateStandardAlert(...)", but for Linux we just use the
 command line (because who knows which GUI they are on?). Note
 that we are opening a Modal that may or may not halt the
 calling thread (can't get unified behavior for now) and may
 or may not act as a modal vs. standard window.
 
***************************************************************/

// Inclusion guard
#ifndef __G2DIALOG_H__
#define __G2DIALOG_H__

#include "g2Utilities.h"

// The enumeration of dialog types
enum g2DialogType
{
    g2DialogType_Open = 0,
    g2DialogType_Save,
    g2DialogType_Notification,
};

class g2Dialog
{
public:
    
    // Dialog constructor creates either an open or a save dialog
    g2Dialog(g2DialogType Type, const char* Message);
    
    // Destructor explicitly takes down any open modals
    ~g2Dialog();
    
    // Is the user done with the dialog?
    bool IsDone();
    
    // What did the user write? This buffer is to be read
    // and never written to or released (this is done internally)
    char* GetInput();
    
private:
    
    // Nothing here...
    
};

// End of inclusion guard
#endif
