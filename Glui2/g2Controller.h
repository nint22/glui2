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

// Necesary STL for the child list; should consider replacing
#include <queue>

// Enumerate all button states
enum g2ControllerState
{
    g2ControllerState_None = 0, // No state
    g2ControllerState_Hover,    // User has the cursor hovering over object
    g2ControllerState_Pressed,  // User has the controller actively pressed on
    g2ControllerState_Clicked,  // User has had a full click through (pressed and released in the same area)
};

class g2Controller
{
public:
    
    // Initialize self and self-register to parent; note that
    // this constructor is private because new controllers should
    // be created using the glui2 main class's factory methods
    g2Controller(g2Controller* Parent, g2Theme* MainTheme);
    
    // Default destructor
    ~g2Controller();
    
    /*** Render Options ***/
    
    // Set visibility (if invisible, it is both deactivated AND invisible)
    void SetVisibility(bool Visible);
    
    // Get visability
    bool GetVisibility();
    
    // Set color (defaults to white)
    void SetColor(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    
    // Get color (Each individual color is optional)
    void GetColor(float* r = NULL, float* g = NULL, float* b = NULL, float* a = NULL);
    
    // Set enabled / disabled modes
    void SetDisabled(bool Disabled);
    
    // Get enabled / disabled modes
    bool GetDisabled();
    
    // Set position
    void SetPos(int x, int y);
    
    // Get x and y position
    void GetPos(int* x = NULL, int* y = NULL);
    
    // Returns true if we are the active controller
    bool GetActive();
    
    /*** Active State Management ***/
    
    // Returns a pointer to an intersecting controller either owned
    // by this controller, the controller itself, or null. An active
    // controller is the controller that can be directly clicked on
    // as determined using "InController(...)" and the the lowesr-rendering
    // order which means the visibility top-most layer
    g2Controller* GetController(int x, int y);
    
    // Set a callback function for a full clickthrough event
    // Note that if there is no argument passed, the callback is set back to none
    void SetCallback(__g2CallBack(PressedCallback) = 0);
    
    // Returns true if the mouse is in the controller's geometry (Required to overload)
    virtual bool InController(int x, int y);
    
protected:
    
    /*** Update, Render, and Input Handlers ***/
    
    // Update object
    virtual void Update(float dT);
    
    // Render object (Required to overload)
    virtual void Render();
    
    // Window resize event
    virtual void WindowResizeEvent(int NewWidth, int NewHeight);
    
    // Glut keyboard event callback (When a full press cycle happens)
    // If the "IsSpecial" flag is true, it means it is a system key (such as up/down/F1/Print) and not
    // an actual keyboard character
    virtual void KeyEvent(unsigned char key, bool IsSpecial = false);
    
    // Glut mouse event callback for a full click
    virtual void MouseClick(g2MouseButton button, g2MouseClick state, int x, int y);
    
    // Glut mouse event callback for a hover
    virtual void MouseHover(int x, int y);
    
    // Glut mouse event callback for a drag
    virtual void MouseDrag(int x, int y);
    
    /*** Internal Rendering Components & Helpers ***/
    
    // Draws a given source location to the on-screen descrition coordinates
    void DrawComponent(int DestX, int DestY, g2ThemeElement ElementType);
    
    // Draws a given source location and size to the on-screen descrition coordinates
    void DrawComponent(int DestX, int DestY, int DestW, int DestH, g2ThemeElement ElementType);
    
    // Draws a given source location to the on-screen descrition coordinates
    void DrawComponent(int DestX, int DestY, const char* ElementName);
    
    // Draws a given source location and size to the on-screen descrition coordinates
    void DrawComponent(int DestX, int DestY, int DestW, int DestH, const char* ElementName);
    
    // Draws a given rectangle and source textures; texture ID defaults to the theme texture
    void DrawComponent(int DestX, int DestY, int DestW, int DestH, float SrcX, float SrcY, float SrcW, float SrcH, int TextID = -1);
    
    // Draw a character with 1-1 scale
    void DrawCharacter(int DestX, int DestY, char Character);
    
    // Draw a character with given scales
    void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, char Character);
    
    // Draw a character with given scales and a 4-channel color (RGBA)
    void DrawCharacter(int DestX, int DestY, float ScaleW, float ScaleH, float R, float G, float B, float A, char Character);
    
    // Accessor to the global theme
    g2Theme* GetTheme();
    
    // Accessor to parent pointer
    g2Controller* GetParent();
    
    // Get the controller state
    g2ControllerState GetControllerState();
    
private:
    
    /*** Rendering Properties ***/
    
    // Position
    int x, y;
    
    // Object color, from 0.0f to 1.0f per chanel
    float R, G, B;
    
    // Alpha value, from 0.0f to 1.0f
    float Alpha;
    
    // Visable/Renderable, propagates down to children objects
    bool IsVisible;
    
    // Disabled/enabled
    bool IsDisabled;
    
    // Active state
    bool IsActive;
    
    // Callback function; called when a full clickthrough event was detected
    __g2CallBack(PressedCallback);
    
    /*** Managed Object Events ***/
    
    // Internal update function
    void __Update(float dT);
    
    // Internal render function
    void __Render();
    
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
    std::queue< g2Controller* > ChildObjects;
    
    // Parent object pointer
    g2Controller* ParentObject;
    
    // Parent theme is from the root controller; otherwise null
    g2Theme* ParentTheme;
    
    // Declare the main GLUI2 class as a friend
    friend class Glui2;
};

// End of inclusion guard
#endif
