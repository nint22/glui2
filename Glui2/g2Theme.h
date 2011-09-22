/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Config.cpp/h
 Desc: g2Theme is a way to "skin" or "theme" a GLUI2 on-screen.
 Only one theme may be active at a time; a default theme is loaded
 when not specificed with "g2Default.cfg". An example theme
 is "g2Blue.cfg".
 
 All themes require a source image that must of *.png file type.
 
 A theme configuration file follows the below specification, and
 is loaded using the g2Config system; it is roughly equivalient
 to *ini grouped key-data value data.
 
 There are in total 10 groups, 1 used to define the source image,
 and 8 to define the below UI images (some UI components
 require multiple images), and 1 optional for the background.
 
 The first group is the general data: a string for the source image
 location and a key for the background color (three integers ranging
 from 0-256 delimited by space)
 
 [general]
 image: g2Default.png
 background_color: 255 255 255
 font: default.png
 
 The 8 UI components (some require two image for "selection state")
 are as follows:
 
 [checkbox], [checkbox_sel]
 [radiobutton], [radiobutton_sel]
 [uparrow], [uparrow_sel]
 [downarrow], [downarrow_sel]
 [leftarrow], [leftarrow_sel]
 [rightarrow], [rightarrow_sel]
 [spinup], [spinup_sel]
 [spindown], [spindown_sel]
 
 Each of these group need a source key which are two integers (x y)
 delimited by a space, and needs a size (width height), which are
 also two integers. These specificy the sub-image's origin and size.
 This data cuts out the UI sub-image for the given source image.
 
 For example:
 
 [checkbox_sel]   # A checked-checkbox (i.e. selected) graphic
 source: 10 10    # Sub-image source at (10,10) from the origin
 size: 13 13      # This sub-image is 13x13 pixels large
 
 A background image is also optional, using the above configuration
 style, but uses the group name "[background]".
 
 Fonts are not yet an implemented feature.
 
***************************************************************/

// Inclusion guard
#ifndef __G2THEME_H__
#define __G2THEME_H__

#include "g2Utilities.h"
#include "g2Config.h"

// External image loading
#include "SOIL.h"

// Total number of element types
static const unsigned int g2ThemeElement_Count = 13;

// Enumerate all theme options
enum g2ThemeElement
{
    // Button states
    g2Theme_Button = 0,
    g2Theme_Button_Pressed,
    g2Theme_Button_Disabled,
    
    // Checkbox states
    g2Theme_CheckBox,
    g2Theme_CheckBox_Disabled,
    g2Theme_CheckBox_Pressed,
    g2Theme_CheckBox_Pressed_Disabled,
    
    // Text field (same as text box)
    g2Theme_TextField,
    g2Theme_TextField_Disabled,
    
    // Radiobutton states
    g2Theme_RadioButton,
    g2Theme_RadioButton_Disabled,
    g2Theme_RadioButton_Pressed,
    g2Theme_RadioButton_Pressed_Disabled,
};

// Look-up table between the theme enumeration and
// the standard theme elements
static const char g2ThemeElement_Names[g2ThemeElement_Count][__G2CONFIG_KEYSIZE__] =
{
    "Button",
    "Button_Pressed",
    "Button_Disabled",
    "CheckBox",
    "CheckBox_Disabled",
    "CheckBox_Pressed",
    "CheckBox_Pressed_Disabled",
    "TextField",
    "TextField_Disabled",
    "RadioButton",
    "RadioButton_Disabled",
    "RadioButton_Pressed",
    "RadioButton_Pressed_Disabled",
};

// Theme implementation class
class g2Theme
{
public:
    
    // Standard constructor and destructor
    g2Theme();
    ~g2Theme();
    
    // Attempts to load a configuration file
    void Load(const char* ThemeFile);
    
    // Access a given UI component's bitmap data based on an enumeration
    // which inturn looks it up in the "g2ThemeElement_Names" string-table
    // Returns true if found, else false
    bool GetComponent(g2ThemeElement Element, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID);
    
    // Access a given UI component's bitmap data based on the configuration name
    // Returns true if found, else false
    bool GetComponent(const char* ElementName, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID);
    
    // Access a given UI component's bitwise width and height based on an enumeration
    bool GetComponentSize(g2ThemeElement Element, int* width, int* height);
    
    // Access a given UI component's bitwise width and height based on a string
    bool GetComponentSize(const char* ElementName, int* width, int* height);
    
    // Get a bitmap's individual position
    void GetCharacter(char character, float* tSrcX, float* tSrcY, float* tSrcWidth, float* tSrcHeight, int* width, int* height, GLuint* textID);
    
    // Get a character's size
    void GetCharacterSize(int* width, int* height);
    
private:
    
    // The theme's configuration file
    g2Config Configuration;
    
    // Texture's ID and width/height
    GLuint TextureID;
    int TextureWidth, TextureHeight;
    
    // Character map ID and width/height
    GLuint CharacterMapID;
    int CharacterMapWidth, CharacterMapHeight;
    
};

// End of inclusion guard
#endif