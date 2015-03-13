## About ##

_[Glui2 Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/glui2.h)_

The core object for the entirety of the Glui2 library. This class handles all user input events and window events, as well as interfaces with GLUT handles and theming. The first parameter is the location of your [theme configuration file](Theming.md).

One very important note is the constructor: **you must pass any custom GLUT function** to this constructor. The reason is that to make sure the UI is rendered and input events are captured, a custom block of Glui2 code must run first before your application's code can execute. This allows users to type data, click through controllers, and manipulate other elements without giving the event to the application. This approach also gives you the benefit so that no functions have to be called to maintain the Glui2 data, with the exception of the "Render()" function.

You must **explicitly** call your Glui2 handle's Render function during your render loop, commonly bound with glutDisplayFunc(...) from the GLUT library.

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
Get the controller state

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