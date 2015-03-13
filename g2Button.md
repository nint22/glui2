![http://www.cores2.com/files/Glui2/g2Button.png](http://www.cores2.com/files/Glui2/g2Button.png)

## About ##

_[g2Button Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Button.h)_

An interactive labeled button; derives from [g2Controller](g2Controller.md). The text on top of the button is based on a [g2Label](g2Label.md) child-object and can be directly accessed by the end-developer. g2Button allows for callback event registration.

## Factory Method ##

```
g2Button* AddButton(int x, int y, const char* Label = NULL, __g2CallBack(callback) = 0)
```

_AddButton_ will internally allocate and manage a newly created g2Button. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument "Label" is an optional c-string input; it is rendered on-screen as a [g2Label](g2Label.md). If no argument is provided, the label will initialize with an empty string. The final argument is the button-press event callback. If the button experiences a full click-through by the user, then this c-style function is called by the button object during it's rendering cycle.

## Function Members ##

```
g2Label* GetLabel()
```
Returns the on-screen [g2Label](g2Label.md) that the button is associated with. Allows the user to set color, text size, etc.

```
void SetText(const char* Text)
```

Directly sets the button's text. Using this method is preferred over the "g2Label::SetText(...)" function as the button will automatically resize if the text is too large to fit in the current size.

```
void SetWidth(int Width)
```
Set the button's width in pixel. The width will be at least the length of the associated g2Label's text or the width of the default button size (which is defined the theme image).

```
int GetWidth()
```
Returns the width of the button.

## Notes ##

For a full click-through event, the user must both click on the button and release while the cursor is inside the button. This way it allows users to drag the cursor off the button if they miss-clicked it. Internally the button-handeling code uses [g2Controller](g2Controller.md)'s built-in controller states.