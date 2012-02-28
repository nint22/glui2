/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Config.cpp/h
 Desc: g2Theme is a way to "skin" or "theme" a GLUI2 on-screen.
 Only one theme may be active at a time; a default theme is loaded
 when not specified with "g2Default.cfg". An example theme
 is "g2Blue.cfg".
 
 All themes require a source image that must of *.png file type.
 
 A theme configuration file follows the below specification, and
 is loaded using the g2Config system; it is roughly equivalent
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
 also two integers. These specify the sub-image's origin and size.
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
#include "g2Images.h"

// Total number of element types
static const unsigned int g2ThemeElement_Count = 31;

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
    
    // Text field
    g2Theme_TextField,
    g2Theme_TextField_Disabled,
    
    // Radiobutton states
    g2Theme_RadioButton,
    g2Theme_RadioButton_Disabled,
    g2Theme_RadioButton_Pressed,
    g2Theme_RadioButton_Pressed_Disabled,
    
    // ProgressBar states
    g2Theme_ProgressBar,
    g2Theme_ProgressBar_Fill,
    g2Theme_ProgressBar_Disabled,
    
    // DropDown states
    g2Theme_DropDown,
    g2Theme_DropDown_Pressed,
    g2Theme_DropDown_Disabled,
    
    // Spinner states (note the graphics are paired, but internally split)
    g2Theme_Spinner,
    g2Theme_Spinner_Pressed,
    g2Theme_Spinner_Disabled,
    
    // Panel background (gets repeated, not stretched)
    g2Theme_Panel,
    
    // Slider
    g2Theme_Slider,
    g2Theme_SliderButton,
    g2Theme_SliderButton_Pressed,
    g2Theme_SliderButton_Disabled,
    
    // Slider (vertical)
    g2Theme_VSlider,
    g2Theme_VSliderButton,
    g2Theme_VSliderButton_Pressed,
    g2Theme_VSliderButton_Disabled,
};

// Look-up table between the theme enumeration and
// the standard theme elements
static const char g2ThemeElement_Names[g2ThemeElement_Count][g2Config_KeySize] =
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
    "ProgressBar",
    "ProgressBar_Fill",
    "ProgressBar_Disabled",
    "DropDown",
    "DropDown_Pressed",
    "DropDown_Disabled",
    "Spinner",
    "Spinner_Pressed",
    "Spinner_Disabled",
    "Panel",
    "Slider",
    "SliderButton",
    "SliderButton_Pressed",
    "SliderButton_Disabled",
    "VSlider",
    "VSliderButton",
    "VSliderButton_Pressed",
    "VSliderButton_Disabled",
};

// Define an anchor style, or how controller are added
// Note that these are uints so we can combine flags together
// It is up to the end-developer to combine them using the bit-wise or operator
typedef unsigned int g2Anchor;
static const g2Anchor g2Anchor_None    =   0;    // Same as a top-left anchor; i.e. never moves
static const g2Anchor g2Anchor_Top     =   1;    // Anchor is from top of screen
static const g2Anchor g2Anchor_Left    =   2;    // Anchor is on left-screen edge
static const g2Anchor g2Anchor_Bottom  =   4;    // Anchor is from bottom of screen
static const g2Anchor g2Anchor_Right   =   8;    // Anchor is on the right-screen edge
static const g2Anchor g2Anchor_Center  =  16;    // Anchor is the horizontal middle

// Theme implementation class
class g2Theme
{
public:
    
    // Standard constructor and destructor
    __g2EXPORT g2Theme();
    __g2EXPORT ~g2Theme();
    
    // Attempts to load a configuration file
    __g2EXPORT void Load(const char* ThemeFile);
    
    // Return the theme name based on the element type; may return null of the index is not
    // in the element-name set
    __g2EXPORT const char* const GetElementName(g2ThemeElement ElementType);
    
    // Access a given UI component's bitmap data based on an enumeration
    // which in turn looks it up in the "g2ThemeElement_Names" string-table
    // Returns true if found, else false
    __g2EXPORT bool GetComponent(g2ThemeElement Element, float* tSrcX = NULL, float* tSrcY = NULL, float* tSrcWidth = NULL, float* tSrcHeight = NULL, int* width = NULL, int* height = NULL, GLuint* textID = NULL);
    
    // Access a given UI component's bitmap data based on the configuration name
    // Returns true if found, else false
    __g2EXPORT bool GetComponent(const char* ElementName, float* tSrcX = NULL, float* tSrcY = NULL, float* tSrcWidth = NULL, float* tSrcHeight = NULL, int* width = NULL, int* height = NULL, GLuint* textID = NULL);
    
    // Access a given UI component's bitwise width and height based on an enumeration
    __g2EXPORT bool GetComponentSize(g2ThemeElement Element, int* width = NULL, int* height = NULL);
    
    // Access a given UI component's bitwise width and height based on a string
    __g2EXPORT bool GetComponentSize(const char* ElementName, int* width = NULL, int* height = NULL);
    
    // Get a bitmap's individual position
    __g2EXPORT void GetCharacter(char character, float* tSrcX = NULL, float* tSrcY = NULL, float* tSrcWidth = NULL, float* tSrcHeight = NULL, int* width = NULL, int* height = NULL, GLuint* textID = NULL);
    
    // Get a character's size
    __g2EXPORT void GetCharacterSize(char character, int* width = NULL, int* height = NULL);
    
    // Get a all character's height
    __g2EXPORT int GetCharacterHeight();
    
    // Get the texture map's size in pixels
    __g2EXPORT void GetTextureSize(int* Width = NULL, int* Height = NULL);
    
    // Get the theme texture ID
    __g2EXPORT GLuint GetTextureID();
    
    // Get the character map's size in pixels
    __g2EXPORT void GetCharacterMapSize(int* Width = NULL, int* Height = NULL);
    
    // Get the character maps texture ID
    __g2EXPORT GLuint GetCharacterMapID();
    
private:
    
    // The theme's configuration file
    g2Config Configuration;
    
    // Texture's ID and width/height
    GLuint TextureID;
    int TextureWidth, TextureHeight;
    
    // Character map ID and width/height
    GLuint CharacterMapID;
    int CharacterMapWidth, CharacterMapHeight;
    
    // 16 x 16 (256) character bitmap width
    int CharacterWidths[16][16];
};

// End of inclusion guard
#endif
