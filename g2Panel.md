![http://www.cores2.com/files/Glui2/g2Panel.png](http://www.cores2.com/files/Glui2/g2Panel.png)

## About ##

_[g2Panel Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Panel.h)_

A tiled background and placement manager for GUI controllers. A panel allows end-developers to add new GUI anchored controllers so that window movement and resizing will automatically move around and manage the UI's positions. The end-developer may explicitly set the size and thus turn off the anchoring feature so that this panel will act as a window.

## Factory Method ##

```
g2Panel* AddPanel(g2Anchor AnchorFlags, const char* Title = NULL)
```

_AddPanel_ will internally allocate and manage a newly created g2Panel. The given anchor defines the placement and size of the panel. A title argument, being optional, will set the current title of the window-like panel.

## Function Members ##

```
g2Panel(g2Controller* Parent, g2Theme* MainTheme, g2Anchor Anchors = g2Anchor_None, const char* Title = NULL)
```
Panel constructor

```
void SetAlignment(g2Anchor Anchors)
```
Set the alignment style; non-opposing combinations can be made, such as anchoring to the top-left (which is done by doing the bit-wise combination of "g2Anchor\_Top | g2Anchor\_Left")

```
g2Anchor GetAlignment()
```
Return the alignment style

```
void SetTitle(const char* Title)
```
Set a title to the panel

```
g2Label* GetTitle()
```
Retrieve the title of the panel

```
void SetSize(int NewWidth, int NewHeight)
```
Explicitly set the size of this panel, thus turning it into a window-based shape. Controllers will move based on resizing and the weighting. Unless the anchor / alignment is set in g2Anchor\_none, all new widths or heights may be ignored except for the appropriate handler..

_The following are factory methods for creating objects and assignment them by default into this panel_

```
g2Button* AddButton(int x, int y, const char* Label = NULL, __g2CallBack(callback) = 0)
```

```
g2Label* AddLabel(int x, int y, const char* Text = NULL)
```

```
g2CheckBox* AddCheckBox(int x, int y, const char* Text, __g2CallBack(callback) = 0, bool* LiveCheckState = NULL)
```

```
g2TextField* AddTextField(int x, int y, const char* Text = NULL)
```

```
g2RadioGroup* AddRadioGroup(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL)
```

```
g2DropDown* AddDropDown(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL)
```

```
g2Dialog* AddDialog(g2DialogType Type, const char* Message = NULL)
```

```
g2Slider* AddSlider(int x, int y, __g2CallBack(callback) = 0, float* LiveValue = NULL)
```

```
g2ProgressBar* AddProgressBar(int x, int y)
```

```
g2Spinner* AddSpinner(int x, int y, g2SpinnerType Type, __g2CallBack(callback) = 0, float* LiveValue = NULL)
```

```
void Render(int pX, int pY)
```
Render

```
void GetCollisionRect(int* Width, int* Height)
```
Define controller geometry

```
void WindowResizeEvent(int NewWidth, int NewHeight)
```
Window resize event

## Notes ##

As of release version 1.0, the behavior of multi-flag anchors is not yet implemented and currently undefined.