## About ##

_[g2Controller Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Controller.h)_

The root controller for all other GUI controllers. Provides several class member-functions to overload, used to render, handle user events, and define controller geometry. Learn more about creating your own controller through [Extensibility](Extensibility.md).

## Function Members ##

```
g2Controller(g2Controller* Parent, g2Theme* MainTheme)
```
Initialize self and self-register to parent; note that this constructor is private because new controllers should be created using the glui2 main class's factory methods

```
~g2Controller()
```
Default destructor

```
void SetVisibility(bool Visible)
```
Set visibility (if invisible, it is both deactivated AND invisible)

```
bool GetVisibility()
```
Get visibility

```
void SetColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
```
Set color (defaults to white)

```
void GetColor(float* r = NULL, float* g = NULL, float* b = NULL, float* a = NULL)
```
Get color (Each individual color is optional)

```
void SetDisabled(bool Disabled)
```
Set enabled / disabled modes

```
bool GetDisabled()
```
Get enabled / disabled modes

```
void SetPos(int x, int y)
```
Set position (position from parent). This is the offset from the parent's origin

```
void GetPos(int* x = NULL, int* y = NULL)
```
Get x and y position (position from parent). This is the offset from the parent's origin

```
void GetGlobalPos(int* x = NULL, int* y = NULL)
```
Get the global x and y position of this controller. This is the offset from the screen's origin

```
g2Theme* GetTheme()
```
Accessor to the global theme

```
g2Controller* GetParent()
```
Accessor to parent pointer

```
g2ControllerState GetControllerState()
```
Get the controller state encoded as a series of bit-flags. This is a powerful function, but has some **limitations and is not a constant-behavior function**. All user interface states are saved and returned using this function, but full click-through events are posted _**but**_ resets when queried once.

This means that if the user is holding down the left-mouse button on a controller, this function will return a value such that it will have the bit associated with the left-mouse button press is always high (1). The exception is that a full click-through button event will only return that high-bit flag once, and all other subsequent calls (unless the user generates another click-through event) returns a low-bit.

Essentially this function should only be called once per update, or once per mouse event.

```
bool GetActive()
```
Returns true if we are the active controller

```
bool InController(int x, int y)
```
Returns true if we are currently intersecting this controller given the global position

```
g2Controller* GetController(int x, int y)
```
Returns a pointer to an intersecting controller either owned by this controller, the controller itself, or null. An active controller is the controller that can be directly clicked on as determined using "InController(...)" and the the lower-rendering order which means the visibility top-most layer

```
void SetCallback(__g2CallBack(PressedCallback) = 0)
```
Set a callback function for a full click-through event. Note that if there is no argument passed, the callback is set back to none

```
virtual void Update(float dT)
```
Update object

```
virtual void Render(int x, int y)
```
Render object (Required to overload). The given coordinate is the global position of this object (includes all parent offsets)

```
virtual void GetCollisionRect(int* Width, int* Height)
```
Returns the size of the object that inherits from g2Controller. It is up the end-developers to explicitly overload this function if they want user input events

```
virtual void WindowResizeEvent(int NewWidth, int NewHeight)
```
Window resize event

```
virtual void KeyEvent(unsigned char key, bool IsSpecial = false)
```
Glut keyboard event callback (When a full press cycle happens). If the "IsSpecial" flag is true, it means it is a system key (such as up/down/F1/Print) and not an actual keyboard character

```
virtual void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
```
Glut mouse event callback for a full click

```
virtual void MouseHover(int x, int y)
```
Glut mouse event callback for a hover

```
virtual void MouseDrag(int x, int y)
```
Glut mouse event callback for a drag

```
void DrawComponent(g2ThemeElement ElementType, int DestX, int DestY)
```
Draws a given source location to the on-screen description coordinates

```
void DrawComponent(g2ThemeElement ElementType, int DestX, int DestY, int DestW, int DestH)
```
Draws a given source location and size to the on-screen description coordinates

```
void DrawComponent(const char* ElementName, int DestX, int DestY)
```
Draws a given source location to the on-screen description coordinates

```
void DrawComponent(const char* ElementName, int DestX, int DestY, int DestW, int DestH)
```
Draws a given source location and size to the on-screen description coordinates

```
void DrawComponent(int DestX, int DestY, int DestW, int DestH, float SrcX, float SrcY, float SrcW, float SrcH, int TextID = -1)
```
Draws a given rectangle and source textures; texture ID defaults to the theme texture

```
void DrawComponentStretch(g2ThemeElement ElementType, int DestX, int DestY, int Width)
```
Draw a given source location into a spcific width, like a three-part button

```
void DrawComponentStretch(const char* ElementName, int DestX, int DestY, int Width)
```
Draw a given source location into a spcific width, like a three-part button

```
void DrawComponentStretch(g2ThemeElement ElementType, int DestX, int DestY, int Width, int StartHeight, int EndHeight)
```
Draw a given source location into a specific width (stretched), and a limited height (cut). The start and end height are y-pixel values and are defined as 0 at the top and [height - 1](Element.md) bottom

```
void DrawComponentRect(g2ThemeElement ElementType, int DestX, int DestY, int Width, int Height)
```
Draw the object into a square-like output; very similar to "DrawComponentStretch(...)" but grows in all two dimensions

```
void DrawComponentRect(const char* ElementName, int DestX, int DestY, int Width, int Height)
```
Draw the object into a square-like output; very similar to "DrawComponentStretch(...)" but grows in all two dimensions

```
void DrawCharacter(int DestX, int DestY, char Character)
```
Draw a character with 1-1 scale

```
void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, char Character)
```
Draw a character with given scales

```
void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, float R, float G, float B, float A, char Character)
```
Draw a character with given scales and a 4-channel color (RGBA)

## Notes ##

A controller implements a child-parent relationship and thus has to be instantiated with a parent and associated theme file.