![http://www.cores2.com/files/Glui2/g2DropDown.png](http://www.cores2.com/files/Glui2/g2DropDown.png)

## About ##

_[g2Dropdown Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Dropdown.h)_

A mutually exclusive group-selection controller; derives from [g2Controller](g2Controller.md) and conceptually (but not visually) similar to [g2RadioGroup](g2RadioGroup.md). The on-screen text is rendered by individual [g2Button](g2Button.md)s but the list is only visible when the user explicitly opens and closes the list through clicks and drag events. If a title is set, then the selected option will never render as the title, only the explicitly set title will be set.

## Factory Method ##

```
g2DropDown* AddDropDown(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL)
```

_AddDropDown_ will internally allocate and manage a newly created g2DropDown. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument "Options" is an array of c-strings (thus an array of character arrays) of OptionCount size that are the individual labels, in order from 0 to (OptionCount - 1). The fifth argument is a button-press callback event handler much like that found in [g2Button](g2Button.md) but is optional. The final argument is a live-variable which will be updated at any time the user makes a change in the option group, but is optional.

## Function Members ##

```
void SetWidth(int Width)
```
Explicitly set the width of controller

```
int GetWidth()
```
Return the width of the controller

```
void SetOptions(const char** OptionLabels, int OptionCount)
```
Set the options via an array of strings

```
void SetSelectionIndex(int Index)
```
Set the current selection

```
int GetSelectionIndex()
```
Get the current selection defaults to 0

```
void SetLiveVariable(int* LiveIndex = NULL)
```
Add a live variable pass NULL (or leave blank) to disconect

```
bool InController(int x, int y)
```
Define controller geometry

```
void SetTitle(const char* Title = NULL)
```
Explicitly set the title; no longer will the active selection be rendered as the selected text. Pass an empty or NULL string to reset to the default behavior.

```
const char* const GetTitle()
```
Returns the explicitly set the title; not the active selection's label.

## Notes ##

DropDowns are a great way at packing lots of information but in small visual areas. Make sure to correctly choose your scene ordering as the level that the drop down controller is rendered may be behind or infront of other controllers creating bizarre visual effects.