### About ###
Glui2 allows you to easily create your own new on-screen controllers. Each controller should derive from the root controller class [g2Controller](g2Controller.md) and can be instantiated as a normal object. Since controllers always need a parent controller, use your main [Glui2](Glui2.md)'s "GetRootController()" function.

Please see [Examples](ExamplesAndUsage.md)'s Example4 to learn more about custom controllers.

### Usage ###
To create your own controller, you will need to create a class that derives from [g2Controller](g2Controller.md) and passes both the parent object and a pointer to a theme object. The best approach, as mentioned above, is to do pass your main Glui2's root controller (using "GetRootController()") and theme "GetMainTheme()".

#### Overloaded Functions ####
Your class should overload the following class members from g2Controller to benefit from the described features: (_note that none of these are pure-virtual functions and thus do not have to be overloaded, but each overloaded function provides access to core features associated with user interface elements_)

```
void Update(float dT)
```

_Description:_ Get's the amount of time, in fractions of seconds, since the last update was called.


```
void Render(int x, int y)
```

_Description:_ Called during the parent's rendering cycle, used for rendering your own custom geometry. Refer to the rendering features of [g2Controller](g2Controller.md) to learn what functions are available to your render routine. Note that the given (x, y) position is the origin (top-left) of where you should draw your object (as a global screen coordinate). This is different from the position returned through "GetPos(...)" which is your local offset.

```
void GetCollisionRect(int* Width, int* Height)
```

_Description:_ Called when the user-input handler needs to know what your controller's geometry is. This is used for determining user-input states and whether or not you should handle input events. If your controller will not handle user events, either set both pointer-values to 0 (zero) or do not implement the function.

```
void WindowResizeEvent(int NewWidth, int NewHeight)
```

_Description:_ When the application's window is resized, the new width and height are given to your controller through this function.

```
void KeyEvent(unsigned char key, bool IsSpecial)
```

_Description:_ If the user has this controller active (meaning it was fully clicked-through), then any future key-board events will be sent. Key is a one-to-one mapping of ASCII characters, while IsSpecial declared wether or not the key pressed is a non-ascii key (e.g. Left Key, Right Key, etc.).

```
void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
```

_Description:_ A localized mouse event, meaning the given coordinates are relative to your controller's origin, but the data is given regardless of wether or not it is colliding within your controller's collision box. Overload "GetCollisionRect(...)" to define your collision geometry and then use "InController(...)" as a quick method of verifying if the given coordinates are within your geometry.

```
void MouseHover(int x, int y)
```

_Description:_ A localized mouse event, meaning the given coordinates are relative to your controller's origin, regardless of whether or not which controller is active.

```
void MouseDrag(int x, int y)
```

_Description:_ A localized mouse event, meaning the given coordinates are relative to your controller's origin, and is only giving if the start of the drag even was within your controller.

#### Rendering Functions ####

g2Controller provides several wrapper functions to allow you to quickly render a sub-image from the source theme image using [configuration-file](Theming.md) keys or predetermined coordinates. You should **only** call these rendering functions during the render cycle of your controller, which is in your overloaded "Render(...)" function derived from [g2Controller](g2Controller.md). Notice that most of these functions take either a key-string used to find the configuration-file definition, or an enumeration value of g2ThemeElement which is used for all pre-defined UI controllers.

```
void DrawComponent(g2ThemeElement ElementType, int DestX, int DestY)
```

_Description:_ Draw a given built-in controller to the given global coordinates (defaults to pre-defined width / height).

```
void DrawComponent(g2ThemeElement ElementType, int DestX, int DestY, int DestW, int DestH)
```

_Description:_ Draw a given built-in controller to the given global coordinates and given height and width.

```
void DrawComponent(const char* ElementName, int DestX, int DestY)
```

_Description:_ Draw a given user-defined controller to the given global coordinates (defaults to pre-defined width / height).

```
void DrawComponent(const char* ElementName, int DestX, int DestY, int DestW, int DestH)
```

_Description:_ Draw a given built-in controller to the given global coordinates and given height and width.

```
void DrawComponent(int DestX, int DestY, int DestW, int DestH, float SrcX, float SrcY, float SrcW, float SrcH, int TextID)
```

_Description:_ Draws a defined sub-image from the given texture ID (defaults to the theme image) to the given output coordinate and size.

```
void DrawComponentStretch(g2ThemeElement ElementType, int DestX, int DestY, int Width)
```

_Description:_ Draw a given built-in controller to the given coordinate and width; notice that unlike other methods, this rendering function will cut the source image into three equal parts, then only stretch the middle (non-repeating; this is a stretch).

```
void DrawComponentStretch(const char* ElementName, int DestX, int DestY, int Width)
```

_Description:_ Draw a given user-defined controller to the given coordinate and width; notice that unlike other methods, this rendering function will cut the source image into three equal parts, then only stretch the middle (non-repeating; this is a stretch).

```
void DrawComponentStretch(g2ThemeElement ElementType, int DestX, int DestY, int Width, int StartHeight, int EndHeight)
```

_Description:_ Draw a given built-in controller to the given coordinate, width, and height; notice that unlike other methods, this rendering function will cut the source image into nine equal parts (3x3), then only stretch the horizontal middle (non-repeating; this is a stretch) to fit, while repeating the vertical middle until filled. Commonly used to render window-like objects that vary in size for both dimensions.

```
void DrawCharacter(int DestX, int DestY, char Character)
```

_Description:_ Draw a given character from the theme file's character bitmap at the given position.

```
void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, char Character)
```

_Description:_ Draw a given character from the theme file's character bitmap at the given position with a given scale.

```
void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, float R, float G, float B, float A, char Character)
```

_Description:_ Draw a given character from the theme file's character bitmap at the given position with a given scale and given color.

#### Helper Functions ####
The following are a few helper functions that are useful for a variety of tasks but not associated with function overloading or rendering:

```
g2ControllerState GetControllerState()
```

_Description:_ Returns the controller state which contains the user's interactive state with this controller alone. It is generally used during the update cycle for dealing with user interaction, but without the need to overload any of the above-mentioned user input functions.

```
bool GetActive()
```

_Description:_ Returns true if this controller is actively selected by the user.

```
bool InController(int x, int y)
```

_Description:_ Returns true if we are currently intersecting this controller given a local coordinate and the collision geometry defined by overloading the "GetCollisionRect(...)" described above.