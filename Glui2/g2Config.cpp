/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

// Headers
#include "g2Config.h"

g2Config::g2Config()
{
    // Default the root group pointer to NULL
    KeyGroups = NULL;
}

g2Config::~g2Config()
{
    // Release all keygroups and their individual keys
    KeyGroup* ActiveGroup = KeyGroups;
    while(ActiveGroup != NULL)
    {
        // For all key-pairs
        KeyPair* ActiveKey = KeyGroups->Keys;
        while(ActiveKey != NULL)
        {
            // Release all internal data
            delete[] ActiveKey->DataString;
            
            // Go to the next key while releasing this node
            KeyPair* ReleaseKey = ActiveKey;
            ActiveKey = ActiveKey->Next;
            delete ReleaseKey;
        }
        
        // Go to the next group while releasing this node
        KeyGroup* ReleaseGroup = ActiveGroup;
        ActiveGroup = ActiveGroup->Next;
        delete ReleaseGroup;
    }
}

void g2Config::LoadFile(const char* FileName)
{
    // Is this a valid file name?
    g2Assert(FileName != NULL && strlen(FileName) > 4, "Filename is either null or too short.");
    
    // Attempt to load file
    FILE* FileHandle = fopen(FileName, "r");
    
    // Is this file open?
    g2Assert(FileHandle != NULL, "Unable to read file: %s", FileName);
    
    // Active group and key name
    char GroupName[256] = "";
    char KeyName[256] = "";
    
    // For each token
    char TokenBuffer[256];
    while(fscanf(FileHandle, "%s", TokenBuffer) == 1)
    {
        // Is this a comment? Ignore
        if(strlen(TokenBuffer) <= 2 || TokenBuffer[0] == '#')
        {
            // Keep reading to newline or end of file
            while(true)
            {
                char temp = fgetc(FileHandle);
                if(temp == EOF || temp == '\n')
                    break;
            }
            
            // Try again at the top...
            continue;
        }
        
        // Is this a group name buffer?
        else if(TokenBuffer[0] == '[' && TokenBuffer[strlen(TokenBuffer)-1] == ']')
        {
            // Remove surrounding tokens
            strcpy(GroupName, TokenBuffer+1);
            GroupName[strlen(GroupName)-1] = '\0';
            
            // Save as new groupd
            AddGroup(GroupName);
        }
        
        // Is this a key?
        else if(TokenBuffer[strlen(TokenBuffer)-1] == ':' || TokenBuffer[strlen(TokenBuffer)-1] == '=')
        {
            // Copy over the active key name
            strncpy(KeyName, TokenBuffer, strlen(TokenBuffer)-1);
            KeyName[strlen(TokenBuffer)-1] = '\0';
            
            // Create data buffer
            char* DataBuffer = new char[8];
            int DataBufferSize = 8;
            int DataLength = 0;
            
            // Read off any whitespaces
            while(true)
            {
                char temp = fgetc(FileHandle);
                if(temp != ' ' && temp != '\t')
                {
                    ungetc((int)temp, FileHandle);
                    break;
                }
                else if(temp == EOF)
                    break;
            }
            
            // Read off all key data, until we hit the end of line, EOF,
            // or that the next line starts with a tab!
            while(true)
            {
                // Get the data character
                char DataChar = fgetc(FileHandle);
                
                // Is the data buffer long enough to handle this new char?
                // Note the -2 buffer needed to handle the new-line and tab combination
                if(DataLength >= DataBufferSize - 2)
                {
                    // Buffer size grows exponentially
                    DataBufferSize *= 2;
                    
                    // Cap buffer
                    DataBuffer[DataLength] = '\0';
                    
                    // Allocate buffer and copy over
                    char* NewBuffer = new char[DataBufferSize];
                    strncpy(NewBuffer, DataBuffer, DataBufferSize);
                    
                    // Release old buffer and save new pointer
                    delete[] DataBuffer;
                    DataBuffer = NewBuffer;
                }
                
                // End of stream 
                if(DataChar == EOF)
                    break;
                // End of key, but check for multi-line...
                else if(DataChar == '\n')
                {
                    // Warning: windows ends with \n\r instead of \n, ugh...
                    char NextChar = fgetc(FileHandle);
                    
                    // Text continues, this is going to be a multi-line comment
                    if(NextChar == '\t')
                    {
                        DataBuffer[DataLength++] = '\n';
                        DataBuffer[DataLength++] = '\t';
                    }
                    else
                    {
                        // Done with this key-data, break and save string
                        ungetc((int)NextChar, FileHandle);
                        break;
                    }
                }
                // Regular read
                else
                    DataBuffer[DataLength++] = DataChar;
            }
            
            // Cap buffer
            DataBuffer[DataLength] = '\0';
            
            // Do we have both a key and a group name?
            if(strlen(GroupName) <= 0 || strlen(KeyName) <= 0)
                g2Assert(false, "Unknown key name or group name.");
            
            // Add key-value pair to group
            AddKey(GroupName, KeyName, DataBuffer);
            
            // Release temporary data buffer
            delete[] DataBuffer;
        }
    }
    
    // Close the file handle, all done
    fclose(FileHandle);
}

bool g2Config::GetValue(const char* Group, const char* Key, int* OutValue)
{
    char* Buffer;
    bool Success = GetValue(Group, Key, &Buffer);
    
    if(Success)
    {
        if(sscanf(Buffer, "%d", OutValue) != 1)
            Success = false;
    }
    
    return Success;
}

bool g2Config::GetValue(const char* Group, const char* Key, float* OutValue)
{
    char* Buffer;
    bool Success = GetValue(Group, Key, &Buffer);
    
    if(Success)
    {
        if(sscanf(Buffer, "%f", OutValue) != 1)
            Success = false;
    }
    
    return Success;
}

bool g2Config::GetValue(const char* Group, const char* Key, char** OutValue)
{
    // Validate the inputs
    g2Assert(Group != NULL && strlen(Group) < g2Config_KeySize, "Given group string is either NULL or too long.");
    g2Assert(Key != NULL && strlen(Key) < g2Config_KeySize, "Given key string is either NULL or too long.");
    
    // Lowercase both the given groupname and key
    char LowerGroup[g2Config_KeySize];
    char LowerKey[g2Config_KeySize];
    
    strcpy(LowerGroup, Group);
    strcpy(LowerKey, Key);
    
    for(size_t i = 0; i < strlen(LowerGroup); i++)
        LowerGroup[i] = tolower(LowerGroup[i]);
    for(size_t i = 0; i < strlen(LowerKey); i++)
        LowerKey[i] = tolower(LowerKey[i]);
    
    // Search through the groups linked list
    KeyGroup* ActiveGroup = KeyGroups;
    while(ActiveGroup != NULL)
    {
        // Is this the group we want?
        if(strcmp(ActiveGroup->GroupName, LowerGroup) == 0)
        {
            // Search all key-pairs
            KeyPair* ActiveKey = ActiveGroup->Keys;
            while(ActiveKey != NULL)
            {
                // Is this the key we want?
                if(strcmp(ActiveKey->KeyName, LowerKey) == 0)
                {
                    // Set the pointer and return true; found and set
                    *OutValue = ActiveKey->DataString;
                    return true;
                }
                
                // Go to the next key
                ActiveKey = ActiveKey->Next;
            }
        }
        
        // Go to the next group
        ActiveGroup = ActiveGroup->Next;
    }
    
    // Never found
    return false;
}

void g2Config::AddGroup(const char* Group)
{
    // Validate the input
    g2Assert(Group != NULL && strlen(Group) < g2Config_KeySize, "Given group string is either NULL or too long.");
    
    // Create the new group object
    KeyGroup* NewGroup = new KeyGroup;
    strcpy(NewGroup->GroupName, Group);
    NewGroup->Keys = NULL;
    NewGroup->Next = NULL;
    
    // Lowercase the group name
    for(size_t i = 0; i < strlen(NewGroup->GroupName); i++)
        NewGroup->GroupName[i] = tolower(NewGroup->GroupName[i]);
    
    // Is the root empty?
    if(KeyGroups == NULL)
    {
        KeyGroups = NewGroup;
        return;
    }
    
    // Else, appent to list
    KeyGroup* ActiveGroup = KeyGroups;
    while(ActiveGroup != NULL)
    {
        // Does this group already exist?
        g2Assert(strcmp(ActiveGroup->GroupName, NewGroup->GroupName) != 0, "Duplicate group name \"%s\"", ActiveGroup->GroupName);
        
        // Is this next empty?
        if(ActiveGroup->Next == NULL)
        {
            ActiveGroup->Next = NewGroup;
            return;
        }
        
        // Go to the next group
        ActiveGroup = ActiveGroup->Next;
    }
}

void g2Config::AddKey(const char* Group, const char* Key, const char* Data)
{
    // Validate the input
    g2Assert(Group != NULL && strlen(Group) < g2Config_KeySize, "Given group string is either NULL or too long.");
    g2Assert(Key != NULL && strlen(Key) < g2Config_KeySize, "Given key string is either NULL or too long.");
    
    // Lowercase both the given groupname and key
    char LowerGroup[g2Config_KeySize];
    char LowerKey[g2Config_KeySize];
    
    strcpy(LowerGroup, Group);
    strcpy(LowerKey, Key);
    
    for(size_t i = 0; i < strlen(LowerGroup); i++)
        LowerGroup[i] = tolower(LowerGroup[i]);
    for(size_t i = 0; i < strlen(LowerKey); i++)
        LowerKey[i] = tolower(LowerKey[i]);
    
    // For each key group
    KeyGroup* ActiveGroup = KeyGroups;
    while(ActiveGroup != NULL)
    {
        // Is this the group we want?
        if(strcmp(ActiveGroup->GroupName, LowerGroup) == 0)
        {
            // Allocate key
            KeyPair* NewKey = new KeyPair;
            strcpy(NewKey->KeyName, LowerKey);
            NewKey->Next = NULL;
            NewKey->DataString = new char[strlen(Data) + 1];
            strcpy(NewKey->DataString, Data);
            
            // Is the key empty?
            if(ActiveGroup->Keys == NULL)
            {
                ActiveGroup->Keys = NewKey;
                return;
            }
            
            // Search all key-pairs
            KeyPair* ActiveKey = ActiveGroup->Keys;
            while(ActiveKey != NULL)
            {
                // Do we have conflicting keys?
                g2Assert(strcmp(ActiveKey->KeyName, LowerKey) != 0, "Duplicate key \"%s\"", LowerKey);
                
                // Are we at the end?
                if(ActiveKey->Next == NULL)
                {
                    // Save and finish done
                    ActiveKey->Next = NewKey;
                    return;
                }
                
                // Go to the next key
                ActiveKey = ActiveKey->Next;
            }
        }
        
        // Go to the next group
        ActiveGroup = ActiveGroup->Next;
    }
    
    // Else, never found so ignore...
}
