![http://www.cores2.com/files/Glui2/g2RadioGroup.png](http://www.cores2.com/files/Glui2/g2RadioGroup.png)

## About ##

_[g2RadioGroup Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2RadioGroup.h)_

A mutually exclusive group-selection controller; derives from [g2Controller](g2Controller.md). The on-screen text is rendered by individual g2Labels. The user may select any of the individual controllers but will result in the deselection of any other radio controller within the ground.

## Factory Method ##

```
g2RadioGroup* AddRadioGroup(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL)
```

_AddRadioGroup_ will internally allocate and manage a newly created g2RadioGroup. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument "Options" is an array of c-strings (thus an array of character arrays) of OptionCount size that are the individual labels, in order from 0 to (OptionCount - 1). The fifth argument is a button-press callback event handler much like that found in [g2Button](g2Button.md) but is optional. The final argument is a live-variable which will be updated at any time the user makes a change in the radio group, but is optional.

## Function Members ##

```
void SetOptions(const char** OptionLabels, int OptionCount)
```
Set the on-screen label options associated with each individual radio controller. The given OptionLabels is an array of c-strings (thus an array of character arrays) of OptionCount size, in order from index 0 to (OptionCount - 1) which is from top to bottom on-screen.

```
int GetSelectionIndex()
```
Return the currently selected index the user has made, which is from 0 to (OptionCount - 1) (top to bottom on-screen).

```
void SetLiveVariable(int* LiveIndex = NULL)
```
Attach a live index, which is a variable updated at run-time when the user makes any changes to the selected index in the radio group.

## Notes ##

_No notes_