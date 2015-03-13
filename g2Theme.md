## About ##

_[g2Theme Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Theme.h)_

This class provides a set of functions to access both bitmaps (theme texture bitmap and character bitmap) as well as the location and sizes of declare elements. This class also includes the list of pre-defined theme elements, but allows for direct string-based searching for custom-defined theme elements.

## Global Enumerations and Flags ##

```
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
```
Enumeration of all built-in GUI controller element types

```
typedef unsigned int g2Anchor;
static const g2Anchor g2Anchor_None    =   0;    // Same as a top-left anchor; i.e. never moves
static const g2Anchor g2Anchor_Top     =   1;    // Anchor is from top of screen
static const g2Anchor g2Anchor_Left    =   2;    // Anchor is on left-screen edge
static const g2Anchor g2Anchor_Bottom  =   4;    // Anchor is from bottom of screen
static const g2Anchor g2Anchor_Right   =   8;    // Anchor is on the right-screen edge
static const g2Anchor g2Anchor_Center  =  16;    // Anchor is the horizontal middle
```
Define an anchor style, or how controller are added. Note that these are uints so we can combine flags together. It is up to the end-developer to combine them using the bit-wise or operator

## Function Members ##

```
g2Theme();
~g2Theme();
```
Standard constructor and destructor

```
void Load(const char* ThemeFile)
```
Attempts to load a configuration file

```
const char* const GetElementName(g2ThemeElement ElementType);
```
Return the theme name based on the element type; may return null of the index is not in the element-name set

```
bool GetComponent(g2ThemeElement Element, float* tSrcX = NULL, float* tSrcY = NULL, float* tSrcWidth = NULL, float* tSrcHeight = NULL, int* width = NULL, int* height = NULL, GLuint* textID = NULL)
```
Access a given UI component's bitmap data based on an enumeration which in turn looks it up in the "g2ThemeElement\_Names" string-table. Returns true if found, else false

```
bool GetComponent(const char* ElementName, float* tSrcX = NULL, float* tSrcY = NULL, float* tSrcWidth = NULL, float* tSrcHeight = NULL, int* width = NULL, int* height = NULL, GLuint* textID = NULL)
```
Access a given UI component's bitmap data based on the configuration name. Returns true if found, else false

```
bool GetComponentSize(g2ThemeElement Element, int* width = NULL, int* height = NULL)
```
Access a given UI component's bitwise width and height based on an enumeration

```
bool GetComponentSize(const char* ElementName, int* width = NULL, int* height = NULL)
```
Access a given UI component's bitwise width and height based on a string

```
void GetCharacter(char character, float* tSrcX = NULL, float* tSrcY = NULL, float* tSrcWidth = NULL, float* tSrcHeight = NULL, int* width = NULL, int* height = NULL, GLuint* textID = NULL)
```
Get a bitmap's individual position

```
void GetCharacterSize(char character, int* width = NULL, int* height = NULL)
```
Get a character's size

```
int GetCharacterHeight()
```
Get a all character's height

```
void GetTextureSize(int* Width = NULL, int* Height = NULL)
```
Get the texture map's size in pixels

```
GLuint GetTextureID()
```
Get the theme texture ID

```
void GetCharacterMapSize(int* Width = NULL, int* Height = NULL)
```
Get the character map's size in pixels

```
GLuint GetCharacterMapID()
```
Get the character maps texture ID

## Notes ##

As described in [Theming](Theming.md), you can declare your own custom controller theme images within the configuration file by declare a new section and the location & size key-value integer tuple pair.