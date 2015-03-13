![http://www.cores2.com/files/Glui2/g2Spinner.png](http://www.cores2.com/files/Glui2/g2Spinner.png)

## About ##

_[g2Spinner Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Spinner.h)_

A floating-point or integer value incriminator or decrement button pair; derives from [g2Controller](g2Controller.md). The on-screen text is rendered by a [g2TextField](g2TextField.md) which also attempts to parse user input if valid. The user may press the adjacent up or down buttons to either increase or decrease the g2TextField on-screen value.

## Factory Method ##

```
g2Spinner* AddSpinner(int x, int y, g2SpinnerType Type, __g2CallBack(callback) = 0, float* LiveValue = NULL)
```

_AddSpinner_ will internally allocate and manage a newly created g2Spinner. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument is the type of the spinner, which will either be an integer-type (g2SpinnerType\_Int) or a floating-point type (g2SpinnerType\_Float). The fourth argument is a button-press callback event handler much like that found in [g2Button](g2Button.md) but is optional. The final argument is a live-variable which will be updated at any time the user makes a change in the radio group, but is optional.

## Function Members ##

```
void SetWidth(int Width)
```
Set this controller's target width

```
int GetWidth()
```
Get the width of this controller

```
void SetInt(int Value)
```
Set the value (as integer)

```
int GetInt()
```
Get the int value

```
void SetFloat(float Value)
```
Set the value (as float)

```
float GetFloat()
```
Get the float value

```
void SetBounds(float min, float max)
```
Set the lower and upper mounds

```
void SetBounds(int min, int max)
```
Set the lower and upper mounds

```
void SetIncrement(float inc)
```
Set the incrementation

```
void SetIncrement(int inc)
```
Set the incrementation

```
void IncrementUp()
```
Increment up or down

```
void IncrementDown()
```
Increment up or down

```
void SetLiveVariable(float* LiveValue = NULL)
```
Add a live variable; pass NULL (or leave blank) to disconnect

## Notes ##

Don't forget that you can set upper and lower bounds, as well as set the rate of change when a user presses either the increment or decrement buttons.