![http://www.cores2.com/files/Glui2/g2ProgressBar.png](http://www.cores2.com/files/Glui2/g2ProgressBar.png)

## About ##

_[g2ProgressBar Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2ProgressBar.h)_

A bar that gets filled based on a progress variable; derives from [g2Controller](g2Controller.md).

## Factory Method ##

```
g2ProgressBar* AddProgressBar(int x, int y)
```

_AddProgressBar_ will internally allocate and manage a newly created g2ProgressBar. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. By default the progress is set to 0.5 on a scale of [0, 1].

## Function Members ##

```
g2ProgressBar(g2Controller* Parent, g2Theme* MainTheme)
```
Progress bar constructor

```
const g2Label* GetLabel()
```
Get access to the label that is centered on the button

```
void SetBounds(float Lower, float Upper)
```
Set the min / max bounds of the progress bar; defaults to [0.0, 1.0]

```
void SetProgress(float Progress)
```
Set the current progress of this progress bar; default bounds are [0.0, 1.0]

```
void SetText(const char* Text)
```
Set the button's text note that the button will grow if needed

```
void SetWidth(int Width)
```
Set the width of the button in pixels

```
bool InController(int x, int y)
```
Define controller geometry

## Notes ##

Make sure to change your scale to help you when interfacing with a non-normalized value.