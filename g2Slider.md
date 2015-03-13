![http://www.cores2.com/files/Glui2/g2Slider.png](http://www.cores2.com/files/Glui2/g2Slider.png)

## About ##

_[g2Slider Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Slider.h)_

A floating-point value selector; derives from [g2Controller](g2Controller.md) and conceptually similar to [g2Spinner](g2Spinner.md). Based on the value of the slider icon over the slider rail, a floating point value can be read. This controller can be rendered both horizontally (default) and vertically.

## Factory Method ##

```
g2Slider* AddSlider(int x, int y, __g2CallBack(callback) = 0, float* LiveValue = NULL)
```

_AddSlider_ will internally allocate and manage a newly created g2Slider. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument is a button-press callback event handler much like that found in [g2Button](g2Button.md) but is optional. The final argument is a live-variable which will be updated at any time the user makes a change in the radio group, but is optional.

## Function Members ##

```
void SetLiveVariable(float* LiveValue = NULL)
```
Add a live variable pass NULL (or leave blank) to disconect

```
void SetBounds(float Lower, float Upper)
```
Set the min / max bounds of the progress bar; defaults to [0.0, 1.0]

```
void SetProgress(float Progress)
```
Set the current progress of this progress bar accepts values from 0 to 1 (floats)

```
float GetProgress()
```
Return the current progress

```
void SetWidth(int Width)
```
Set the width of the button in pixels

```
bool InController(int x, int y)
```
Define controller geometry

```
void SetVertical(bool Vertical)
```
Sets the controller to be in vertical mode

```
bool GetVertical()
```
Returns true if the controller is vertical; false otherwise

## Notes ##

Much like the [g2Spinner](g2Spinner.md), don't forget that you can set upper and lower bounds, as well as set the rate of change when a user drags the slider-icon across the rail.