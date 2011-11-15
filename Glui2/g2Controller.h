/***************************************************************
 
 Blood Ocean - Platform Shooter Game
 Copyright 2011 Core S2 - See License.txt for info
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Controller.cpp/h
 Desc: The root controller that is sub-classes by all UI components
 to implement a range of required functions (i.e. update, draw, etc)
 as well as allows for a hierarchy of UI components.
 
***************************************************************/

// Inclusion guard
#ifndef __G2CONTROLLER_H__
#define __G2CONTROLLER_H__

#include "g2Utilities.h"
#include "g2Theme.h"

// Necessary STL for the child list; should consider replacing
#include <list>

// Enumerate all button states
typedef unsigned int g2ControllerState;
static const g2ControllerState g2ControllerState_None =    0x01; // No state
static const g2ControllerState g2ControllerState_Hover =   0x02; // User has the cursor hovering over object
static const g2ControllerState g2ControllerState_Pressed = 0x04; // User has the controller actively pressed on
static const g2ControllerState g2ControllerState_Clicked = 0x08; // User has had a full click through (pressed and released in the same area)

class g2Controller
{
public:
    
    // Initialize self and self-register to parent; note that
    // this constructor is private because new controllers should
    // be created using the glui2 main class's factory methods
    __g2EXPORT g2Controller(g2Controller* Parent, g2Theme* MainTheme);
    
    // Default destructor
    __g2EXPORT ~g2Controller();
    
    /*** Render Options ***/
    
    // Set visibility (if invisible, it is both deactivated AND invisible)
    __g2EXPORT void SetVisibility(bool Visible);
    
    // Get visibility
    __g2EXPORT bool GetVisibility();
    
    // Set color (defaults to white)
    __g2EXPORT void SetColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    
    // Get color (Each individual color is optional)
    __g2EXPORT void GetColor(float* r = NULL, float* g = NULL, float* b = NULL, float* a = NULL);
    
    // Set enabled / disabled modes
    __g2EXPORT void SetDisabled(bool Disabled);
    
    // Get enabled / disabled modes
    __g2EXPORT bool GetDisabled();
    
    // Set position (position from parent)
    // This is the offset from the parent's origin
    __g2EXPORT void SetPos(int x, int y);
    
    // Get x and y position (position from parent)
    // This is the offset from the parent's origin
    __g2EXPORT void GetPos(int* x = NULL, int* y = NULL);
    
    // Get the global x and y position of this controller
    // This is the offset from the screen's origin
    __g2EXPORT void GetGlobalPos(int* x = NULL, int* y = NULL);
    
    // Accessor to the global theme
    __g2EXPORT g2Theme* GetTheme();
    
    // Accessor to parent pointer
    __g2EXPORT g2Controller* GetParent();
    
    // Get the controller state (this is a bit-blit'ed multi-state variable)
    __g2EXPORT g2ControllerState GetControllerState();
    
    // Returns true if we are the active controller
    __g2EXPORT bool GetActive();
    
    // Returns true if we are currently intersecting this controller given the global position
    __g2EXPORT bool InController(int x, int y);
    
    /*** Active State Management ***/
    
    // Returns a pointer to an intersecting controller either owned
    // by this controller, the controller itself, or null. An active
    // controller is the controller that can be directly clicked on
    // as determined using "InController(...)" and the the lower-rendering
    // order which means the visibility top-most layer
    __g2EXPORT g2Controller* GetController(int x, int y);
    
    // Set a callback function for a full click-through event
    // Note that if there is no argument passed, the callback is set back to none
    __g2EXPORT void SetCallback(__g2CallBack(PressedCallback) = 0);
    
protected:
    
    /*** Update, Render, and Input Handlers ***/
    
    // Update object
    __g2EXPORT virtual void Update(float dT);
    
    // Render object (Required to overload)
    // The given coordinate is the global position of this object (includes all parent offsets)
    __g2EXPORT virtual void Render(int x, int y);
    
    // Returns the size of the object that inherits from g2Controller
    // It is up the end-developers to explicitly overload this function if they want user input events
    __g2EXPORT virtual void GetCollisionRect(int* Width, int* Height);
    
    // Window resize event
    __g2EXPORT virtual void WindowResizeEvent(int NewWidth, int NewHeight);
    
    // Glut keyboard event callback (When a full press cycle happens)
    // If the "IsSpecial" flag is true, it means it is a system key (such as up/down/F1/Print) and not
    // an actual keyboard character
    __g2EXPORT virtual void KeyEvent(unsigned char key, bool IsSpecial = false);
    
    // Glut mouse event callback for a full click
    __g2EXPORT virtual void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
    // Glut mouse event callback for a hover
    __g2EXPORT virtual void MouseHover(int x, int y);
    
    // Glut mouse event callback for a drag
    __g2EXPORT virtual void MouseDrag(int x, int y);
    
    /*** Internal Rendering Components & Helpers ***/
    
    // Draws a given source location to the on-screen description coordinates
    __g2EXPORT void DrawComponent(g2ThemeElement ElementType, int DestX, int DestY);
    
    // Draws a given source location and size to the on-screen description coordinates
    __g2EXPORT void DrawComponent(g2ThemeElement ElementType, int DestX, int DestY, int DestW, int DestH);
    
    // Draws a given source location to the on-screen description coordinates
    __g2EXPORT void DrawComponent(const char* ElementName, int DestX, int DestY);
    
    // Draws a given source location and size to the on-screen description coordinates
    __g2EXPORT void DrawComponent(const char* ElementName, int DestX, int DestY, int DestW, int DestH);
    
    // Draws a given rectangle and source textures; texture ID defaults to the theme texture
    __g2EXPORT void DrawComponent(int DestX, int DestY, int DestW, int DestH, float SrcX, float SrcY, float SrcW, float SrcH, int TextID = -1);
    
    // Draw a given source location into a spcific width, like a three-part button
    __g2EXPORT void DrawComponentStretch(g2ThemeElement ElementType, int DestX, int DestY, int Width);
    
    // Draw a given source location into a spcific width, like a three-part button
    __g2EXPORT void DrawComponentStretch(const char* ElementName, int DestX, int DestY, int Width);
    
    // Draw a given source location into a specific width (stretched), and a limited height (cut)
    // The start and end height are y-pixel values and are defined as 0 at the top and [Element height - 1] bottom
    __g2EXPORT void DrawComponentStretch(g2ThemeElement ElementType, int DestX, int DestY, int Width, int StartHeight, int EndHeight);
    
    // Draw a given source location into a specific width (stretched), and a limited height (cut)
    // The start and end height are y-pixel values and are defined as 0 at the top and [Element height - 1] bottom
    __g2EXPORT void DrawComponentStretch(const char* ElementName, int DestX, int DestY, int Width, int StartHeight, int EndHeight);
    
    // Draw the object into a square-like output
    __g2EXPORT void DrawComponentRect(g2ThemeElement ElementType, int DestX, int DestY, int Width, int Height);
    
    // Draw the object into a square-like output
    __g2EXPORT void DrawComponentRect(const char* ElementName, int DestX, int DestY, int Width, int Height);
    
    // Draw a character with 1-1 scale
    __g2EXPORT void DrawCharacter(int DestX, int DestY, char Character);
    
    // Draw a character with given scales
    __g2EXPORT void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, char Character);
    
    // Draw a character with given scales and a 4-channel color (RGBA)
    __g2EXPORT void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, float R, float G, float B, float A, char Character);
    
private:
    
    /*** Rendering Properties ***/
    
    // Position from parent (how many pixels offset from the parent's origin)
    int pX, pY;
    
    // Object color, from 0.0f to 1.0f per channel
    float R, G, B;
    
    // Alpha value, from 0.0f to 1.0f
    float Alpha;
    
    // Visible/Renderable, propagates down to children objects
    bool IsVisible;
    
    // Disabled/enabled
    bool IsDisabled;
    
    // Active state
    bool IsActive;
    
    // Callback function; called when a full click-through event was detected
    __g2CallBack(PressedCallback);
    
    /*** Managed Object Events ***/
    
    // Internal update function
    void __Update(float dT);
    
    // Internal render function
    void __Render(int x, int y);
    
    // Window resize event
    void __WindowResizeEvent(int NewWidth, int NewHeight);
    
    // Glut keyboard event callback (When a full press cycle happens)
    // If the "IsSpecial" flag is true, it means it is a system key (such as up/down/F1/Print) and not
    // an actual keyboard character
    void __KeyEvent(unsigned char key, bool IsSpecial = false);
    
    // Glut mouse event callback for a full click
    void __MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
    // Glut mouse event callback for a hover
    void __MouseHover(int x, int y);
    
    // Glut mouse event callback for a drag
    void __MouseDrag(int x, int y);
    
    /*** Managed Child Objects ***/
    
    // Current window sizes
    int WindowWidth, WindowHeight;
    
    // Controller state
    g2ControllerState ControllerState;
    
    // Child objects list
    std::list< g2Controller* > ChildObjects;
    typedef std::list< g2Controller* >::iterator ChildObjectsIt;
    typedef std::list< g2Controller* >::reverse_iterator ChildObjectsRevIt;
    
    // Parent object pointer
    g2Controller* ParentObject;
    
    // Parent theme is from the root controller; otherwise null
    g2Theme* ParentTheme;
    
    // Declare the main GLUI2 class as a friend
    friend class Glui2;
};

// End of inclusion guard
#endif
