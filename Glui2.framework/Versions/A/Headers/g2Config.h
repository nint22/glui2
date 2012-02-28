/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Config.cpp/h
 Desc: Read a configuration file based on the ini-config file
 format (described below). Configuration variables are group
 based on a header tag. Comments begin with the "#" (hash) character
 and all following characters are ignored until a new-line. Files must
 end in *.cfg or *.ini, but it should be noted this is not a strict
 implementation of ini-config file parsing.
 
 Keys and group names must be less than 256 characters, though the
 data can be of any length. Keys are not case sensitive, though
 data is.
 
 General ini-config file format:
 
 All keys must be in a group, and groups are defined as a string
 encased within brackets (i.e. [sample group]). Group names are
 not case sensitive, and neither are key names. Data for each
 key can be anything, ranging from integers to strings, but
 it must be ascii-encoded (i.e. written in plain-text, not in
 native binary).
 
 # This is a comment, started using a hash character
 [group_name]          # Group name of key-value pairs; do not use brackets within the name
 key1: Some data       # Example of key-value pair (or instead of ':' use '=')
 key2: More data
 key3: Any data!
 key: This is an example of multi-line text; the new line MUST either
      be tabbed or include 4 or more space characters.
 
 The internal implementation is based on a linked-list of groups
 with each group having a linked-list of key-data pairs. Though
 this could be implemented as a hash-map, the goal of GLUI2 is
 to keep code simple and maintainable; adding the STL map struct
 is too unruly to work with, ugly, and big...
 
***************************************************************/

// Inclusion guard
#ifndef __G2CONFIG_H__
#define __G2CONFIG_H__

// Includes
#include "g2Utilities.h"
#include <map>
#include <string>

// Define the maximum key size
static const int g2Config_KeySize = 128;

// Key-data node structure; part of a linked list
// Contains the key (lower-case) and data string (allocated in heap)
struct KeyPair
{
    // Group name
    char GroupName[g2Config_KeySize];
    
    // Key name
    char KeyName[g2Config_KeySize];
    
    // Data (allocated on heap)
    char* DataString;
};

class g2Config
{
public:
    
    // Default constructor; does nothing
    __g2EXPORT g2Config();
    
    // Release internal handles
    __g2EXPORT ~g2Config();
    
    // Attempts to load an ini-config file to parse
    __g2EXPORT void LoadFile(const char* FileName);
    
    // Read key-value pairs and places into given buffer; read-only buffers
    // Returns true on valid read, false on failure
    __g2EXPORT bool GetValue(const char* Group, const char* Key, int* OutValue);
    __g2EXPORT bool GetValue(const char* Group, const char* Key, float* OutValue);
    __g2EXPORT bool GetValue(const char* Group, const char* Key, char** OutValue);
    
    // Save as above; but accesses a tuple-pair of either integers or floats
    __g2EXPORT bool GetValue(const char* Group, const char* Key, int* OutValue1, int* OutValue2);
    __g2EXPORT bool GetValue(const char* Group, const char* Key, float* OutValue1, float* OutValue2);
    
private:
    
    // Add a new key (does collision detection, fails if it already exists)
    void AddKey(const char* Group, const char* Key, const char* Data);
    
    // Internal allocations of keys; keys are of the pattern <group name lowercase>_<key name lowercase>
    std::map<std::string, KeyPair> Keys;
    typedef std::map<std::string, KeyPair>::iterator KeysIterator;
};

// End of inclusion guard
#endif
