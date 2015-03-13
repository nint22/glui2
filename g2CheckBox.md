![http://www.cores2.com/files/Glui2/g2CheckBox.png](http://www.cores2.com/files/Glui2/g2CheckBox.png)

## About ##

_[g2CheckBox Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2CheckBox.h)_

An on/off switch, much like a button; derives from [g2Controller](g2Controller.md). The on-screen text is rendered by a [g2Label](g2Label.md). Any number of check boxes may be on (selected) or off (deselected).

## Factory Method ##

```
g2CheckBox* AddCheckBox(int x, int y, const char* Text, __g2CallBack(callback) = 0, bool* LiveCheckState = NULL)
```

_AddCheckBox_ will internally allocate and manage a newly created g2CheckBox. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument "Text" is a c-string rendered to the right of the button using [g2Label](g2Label.md). The fourth argument is a state-change callback event handler much like that found in [g2Button](g2Button.md) but is optional. The final argument is a live-variable which will be updated at any time the user makes a change in the radio group, but is optional.

## Function Members ##

```
bool IsChecked()
```
Return the check state

```
void SetChecked(bool Check)
```
Set the check state

```
void SetLiveVariable(bool* LiveCheckState = NULL)
```
Add a live variable pass NULL (or leave blank) to disconect

```
bool InController(int x, int y)
```
Define controller geometry

## Notes ##

_No notes_