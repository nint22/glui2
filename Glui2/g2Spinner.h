/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Spinner.cpp/h
 Desc: An integer or float based spinner that allows the user
 to chose a value between two min/max limits. The user may
 either hit up or down images or directly input the text.
 
***************************************************************/

// Inclusion guard
#ifndef __G2SPINNER_H__
#define __G2SPINNER_H__

#include "g2Controller.h"
#include "g2TextField.h"

// How much time it takes before we update the
// spinner based on the user holding down
static const float g2Spinner_UpdateRate = 0.05f;

// Number of seconds user needs to wait before
// auto-update occurs 
static const float g2Spinner_UpdateMin = 0.4f;

// Define the two spinner types: int or float
enum g2SpinnerType
{
    g2SpinnerType_Int,
    g2SpinnerType_Float,
};

class g2Spinner : public g2Controller
{
public:
    
    // Progress bar constructor
    __g2EXPORT g2Spinner(g2Controller* Parent, g2Theme* MainTheme, g2SpinnerType Type);
    
    // Set this controller's target width
    __g2EXPORT void SetWidth(int Width);
    
    // Get the width of this controller
    __g2EXPORT int GetWidth();
    
    // Set the value (as integer)
    __g2EXPORT void SetInt(int Value);
    
    // Get the int value
    __g2EXPORT int GetInt();
    
    // Set the value (as float)
    __g2EXPORT void SetFloat(float Value);
    
    // Get the float value
    __g2EXPORT float GetFloat();
    
    // Set the lower and upper mounds
    __g2EXPORT void SetBounds(float min, float max);
    __g2EXPORT void SetBounds(int min, int max);
    
    // Set the incrementation
    __g2EXPORT void SetIncrement(float inc);
    __g2EXPORT void SetIncrement(int inc);
    
    // Increment up or down
    __g2EXPORT void IncrementUp();
    __g2EXPORT void IncrementDown();
    
    // Add a live variable; pass NULL (or leave blank) to disconnect
    __g2EXPORT void SetLiveVariable(float* LiveValue = NULL);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
    // Update (grabs the time)
    __g2EXPORT void Update(float dT);
    
    // Get the mouse position; used to go either up or down on spinner
    __g2EXPORT void MouseHover(int x, int y);
    
private:
    
    // Text label
    g2TextField* TextField;
    
    // The spinner type (usually int or float)
    g2SpinnerType Type;
    
    // Current controller state
    g2ControllerState ControllerState;
    
    // Internal float or int values
    float FloatVal;
    int IntVal;
    
    // Internal min / max of each type
    float FloatMin, FloatMax, FloatInc;
    int IntMin, IntMax, IntInc;
    
    // Internal mouse position; needed for constant increase / decrease
    int MouseX, MouseY;
    
    // Time user has spent pressing the button
    float PressedTime;
    
    // Live value
    float* LiveValue;
};

// End of inclusion guard
#endif
