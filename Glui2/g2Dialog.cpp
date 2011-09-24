/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Dialog.h"

g2Dialog::g2Dialog(g2DialogType Type, const char* Message)
{
    // Supress warning
    Type = g2DialogType_Notification;
    g2Assert(Message != NULL, "Given message buffer was null.");
}

g2Dialog::~g2Dialog()
{
    
}

bool IsDone()
{
    return false;
}


char* GetInput()
{
    return NULL;
}
