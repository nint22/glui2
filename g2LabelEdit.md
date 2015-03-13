## About ##

_[g2LabelEdit Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2LabelEdit.h)_

An interactive bitmap text input / output; derives from [g2Controller](g2Controller.md). The text is generated and drawn using a bitmap, defined in the active [theme](theme.md)'s [configuration](configuration.md) file. This character-map bitmap must be a 16 x 16 square of individual characters and mapped to a nibble-nibble character ASCII map. This means, as an example, the ASCII letter 'A' is hexadecimal 0x41, so the high-nibble is 0x4 (binary 0100) and the lower nibble is 0x1 (binary 0001) and thus position (4, 1) in the table should be the character 'A' draw.

Input is based on certain rules: new characters will push characters behind it to the right. The user can move the cursor through the left or right arrow (full left or right by holding ctrl) or by clicking with the mouse. Cut, copy, and paste works in Windows and OSX, but not in Linux.

Note that this object cannot be directly instantiated, but must be the child of an object.

## Function Members ##

```
g2LabelEdit(g2Controller* Parent, g2Theme* MainTheme)
```
Label constructor and destructor

```
void SetText(const char* Text = NULL)
```
Set the text string the user's cursor will be given back

```
const char* const GetText()
```
Return a constant buffer to the given string; should never be modified. The returned buffer may or may not exist soon after the direct call; you should copy the buffer as soon as possible if it is to not be immediately used

```
void SetCursorPos(int Index)
```
Set the cursor's position; it will be placed after the target index and before the following letter

```
int GetCursorPos()
```
Return the current cursor position

```
void SetCursorAlwaysVisible(bool State)
```
Force-set the cursor to visible or not; if set to true, the cursor is visible regardless of the active state. Default to false, so the state is based on active selection

```
bool GetCursorAlwaysVisible()
```
Get the current cursor state; regardless of the flashing pattern, this function will return true if the controller is explicitly showing the cursor. Default to false, so the state is based on active selection

```
void SetWidth(int Width)
```
Set the target width of the text input

```
int GetWidth()
```
Get the width of the text input

```
void SetShadow(bool State)
```
Set a shadow (true to render a shadow with text)

```
bool GetShadow()
```
Get the shadow state (true if shadow is visible)

```
void SetFilter(const char* Filter = NULL)
```
Set a filter; an array of characters that are the only allowed input characters. Pass null to remove the filter

```
void CopyBuffer()
```
Copy into the host operating system's copy-buffer

```
void PasteBuffer()
```
Paste (by appending) from the host's operating system's copy-buffer into this text buffer

```
bool UserReturned()
```
User has pressed enter; once this function returns true, the return state is reset back to false

```
void Update(float dT)
```
Update

```
void Render(int pX, int pY)
```
Render

```
void GetCollisionRect(int* Width, int* Height)
```
Standard collision body

```
void KeyEvent(unsigned char key, bool IsSpecial)
```
Handle all key events the user executes

```
void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
```
When the user clicks, center the cursor as best as possible

## Notes ##

The default width of a 2LabelEdit is 0 (zero) and thus non-interactive. Set the width to the desired maximum output width (in pixels) for it to self clip.