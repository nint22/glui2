![http://www.cores2.com/files/Glui2/g2Label.png](http://www.cores2.com/files/Glui2/g2Label.png)

## About ##

_[g2Label Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Label.h)_

A non-interactive bitmap text output; derives from [g2Controller](g2Controller.md). The text is generated and drawn using a bitmap, defined in the active [theme](theme.md)'s [configuration](configuration.md) file. This character-map bitmap must be a 16 x 16 square of individual characters and mapped to a nibble-nibble character ASCII map. This means, as an example, the ASCII letter 'A' is hexadecimal 0x41, so the high-nibble is 0x4 (binary 0100) and the lower nibble is 0x1 (binary 0001) and thus position (4, 1) in the table should be the character 'A' draw.

## Factory Method ##

```
g2Label* AddLabel(int x, int y, const char* Text = NULL)
```

_AddLabel_ will internally allocate and manage a newly created g2Label. The given x and y integers are on-screen coordinates, assuming that the origin is the top left of the screen and that Y grows down and X grows right. The third argument "Text" is an optional c-string input. If no argument is provided, the label will initialize with an empty string.

## Function Members ##

```
void SetText(const char* Text = NULL)
```
Sets the current label's text buffer to the given Text input; if no argument is passed or NULL is passed, then the string will be set to an empty-string.

```
const char* GetText()
```
Returns a reference to the internal buffer of the g2Label's text. This buffer may be released upon the object's destruction or at any time that "SetText(...)" is called. Thus, you should copy this buffer yourself and not rely on it's contents from being continuously allocated throughout the run-time.

```
void SetSize(float Scale)
```
Set the text output's rendered size based on any positive value. Note that a value of one (1.0f) will result in the default per-pixel size of the source character bitmap image.

```
int GetWidth()
```
Returns the number of pixels, in width, that this label takes.

## Notes ##

This is one of the simplest controllers in the Glui2 library as it doesn't use any advanced features or theming features.