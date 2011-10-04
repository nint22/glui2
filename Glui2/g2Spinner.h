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
    g2Spinner(g2Controller* Parent, g2Theme* MainTheme, g2SpinnerType Type);
    
    // Set this controller's target width
    void SetWidth(int Width);
    
    // Get the width of this controller
    int GetWidth();
    
    // Set the value (as integer)
    void SetInt(int Value);
    
    // Get the int value
    int GetInt();
    
    // Set the value (as float)
    void SetFloat(float Value);
    
    // Get the float value
    float GetFloat();
    
    // Set the lower and upper mounds
    void SetBounds(float min, float max);
    void SetBounds(int min, int max);
    
    // Set the incrementation
    void SetIncrement(float inc);
    void SetIncrement(int inc);
    
    // Increment up or down
    void IncrementUp();
    void IncrementDown();
    
    // Add a live variable; pass NULL (or leave blank) to disconect
    void SetLiveVariable(float* LiveValue = NULL);
    
protected:
    
    // Render
    void Render();
    
    // Update (grabs the time)
    void Update(float dT);
    
    // Get the mouse position; used to go either up or down on spinner
    void MouseHover(int x, int y);
    
    // Define controller geometry
    bool InController(int x, int y);
    
private:
    
    // Text label
    g2TextField* TextField;
    
    // The spinner type (usually int or float)
    g2SpinnerType Type;
    
    // Internal float or int values
    float FloatVal;
    int IntVal;
    
    // Internal min / max of each type
    float FloatMin, FloatMax, FloatInc;
    int IntMin, IntMax, IntInc;
    
    // Internal mouse position; needed for constant increase / decrease
    int MouseX, MouseY;
    
    // How much time it takes before we update the
    // spinner based on the user holding down
    static const float UpdateRate = 0.05f;
    
    // Number of seconds user needs to wait before
    // auto-update occures 
    static const float UpdateMin = 0.4f;
    
    // Time user has spent pressing the button
    float PressedTime;
    
    // Live value
    float* LiveValue;
};

// End of inclusion guard
#endif
