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
    // Nothing to do...
}

g2Config::~g2Config()
{
    // For each key pair in the dictionary, release it
    for(KeysIterator Key = Keys.begin(); Key != Keys.end(); Key++)
        delete[] Key->second.DataString;
    
    // Release the entire dictionary
    Keys.clear();
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
            
            // Read off any white-spaces
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
    g2Assert(Group != NULL && (int)strlen(Group) < g2Config_KeySize, "Given group string is either NULL or too long.");
    g2Assert(Key != NULL && (int)strlen(Key) < g2Config_KeySize, "Given key string is either NULL or too long.");
    
    // Lowercase both the given group name and key
    char LowerGroup[g2Config_KeySize];
    char LowerKey[g2Config_KeySize];
    
    strcpy(LowerGroup, Group);
    strcpy(LowerKey, Key);
    
    for(size_t i = 0; i < strlen(LowerGroup); i++)
        LowerGroup[i] = tolower(LowerGroup[i]);
    for(size_t i = 0; i < strlen(LowerKey); i++)
        LowerKey[i] = tolower(LowerKey[i]);
    
    // Create the official key entry
    char MapKey[g2Config_KeySize];
    sprintf(MapKey, "%s_%s", LowerGroup, LowerKey);
    
    // Ket the object
    KeysIterator Handle = Keys.find(std::string(MapKey));
    if(Handle == Keys.end())
        return false;
    else
    {
        // Copy over the parameters
        Group = Handle->second.GroupName;
        Key = Handle->second.KeyName;
        *OutValue = Handle->second.DataString;
        return true;
    }
}

void g2Config::AddKey(const char* Group, const char* Key, const char* Data)
{
    // Validate the input
    g2Assert(Group != NULL && (int)strlen(Group) < g2Config_KeySize, "Given group string is either NULL or too long.");
    g2Assert(Key != NULL && (int)strlen(Key) < g2Config_KeySize, "Given key string is either NULL or too long.");
    
    // Lowercase both the given group name and key
    char LowerGroup[g2Config_KeySize];
    char LowerKey[g2Config_KeySize];
    
    strcpy(LowerGroup, Group);
    strcpy(LowerKey, Key);
    
    for(size_t i = 0; i < strlen(LowerGroup); i++)
        LowerGroup[i] = tolower(LowerGroup[i]);
    for(size_t i = 0; i < strlen(LowerKey); i++)
        LowerKey[i] = tolower(LowerKey[i]);
    
    // Create the official key entry
    char MapKey[g2Config_KeySize];
    sprintf(MapKey, "%s_%s", LowerGroup, LowerKey);
    
    // Allocate key
    KeyPair NewKey;
    
    strcpy(NewKey.GroupName, LowerGroup);
    strcpy(NewKey.KeyName, LowerKey);
    
    NewKey.DataString = new char[strlen(Data) + 1];
    strcpy(NewKey.DataString, Data);
    
    // Place into map
    Keys.insert(std::pair<std::string, KeyPair>(std::string(MapKey), NewKey));
}
