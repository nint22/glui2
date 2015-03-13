![http://www.cores2.com/files/Glui2/g2TextField.png](http://www.cores2.com/files/Glui2/g2TextField.png)

## About ##

_[g2TextField Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2TextField.h)_

An interactive text-input field; derives from [g2Controller](g2Controller.md). The on-screen text is fully editable based on [g2LabelEdit](g2LabelEdit.md). The user may enter any character or only characters that end-developers allow through a filter.

## Factory Method ##

```
g2TextField* AddTextField(int x, int y, const char* Text = NULL)
```

_AddTextField_ will internally allocate and manage a newly created g2TextField. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument "Text" is an optional c-string input; it is rendered on-screen as a [g2Label](g2Label.md). If no argument is provided, the label will initialize with an empty string.

## Function Members ##

```
const char* GetText()
```
Returns a reference to the internal buffer of the g2Label's text. This buffer may be released upon the object's destruction or at any time that "SetText?(...)" is called. Thus, you should copy this buffer yourself and not rely on it's contents from being continuously allocated throughout the run-time.

```
void SetWidth(int Width)
```
Set the button's width in pixel. The width will be at least the length of the associated text's width or the width of the default g2TextField size (which is defined the theme image).

```
int GetWidth()
```
Returns the current width of this controller.

```
g2Label* GetLabel()
```
Returns the on-screen [g2Label](g2Label.md) that the button is associated with. Allows the user to set color, text size, etc.

```
void SetFilter(const char* Filter)
```
Set an array of characters acting as a filter that are the only allows the input of the given characters into the g2TextField. By default there is no filter, though an argument such as "ABC" would only allow the user to type the characters 'A', 'B', and 'C' inside the text field.

## Notes ##

g2TextFields are powerful but complex controllers. Make sure to set a wide enough width to allow enough user input, and don't forget about the powerful "SetFilter(...)" function-member.