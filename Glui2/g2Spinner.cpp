/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Spinner.h"

g2Spinner::g2Spinner(g2Controller* Parent, g2Theme* MainTheme, g2SpinnerType Type)
: g2Controller(Parent, MainTheme)
{
    // Allocate textfield and set initial position
    // Note that we are registering to this button, not the root-parent
    TextField = new g2TextField(this, MainTheme);
    
    // Save given type
    this->Type = Type;
    
    // Set all default values
    FloatMin = -10e10;
    FloatMax = 10e10;
    FloatInc = 1.0f;
    IntMin = INT_MIN;
    IntMax = INT_MAX;
    IntInc = 1;
    
    // Time controller is being pressed
    PressedTime = 0.0f;
    
    // Initialize the mouse position off-screen
    MouseX = INT_MIN;
    MouseY = INT_MIN;
    
    // Default to no live value
    LiveValue = NULL;
    
    // Default the float / int values
    if(Type == g2SpinnerType_Float)
    {
        TextField->GetLabelEdit()->SetFilter("1234567890.");
        SetFloat(0.0f);
    }
    else if(Type == g2SpinnerType_Int)
    {
        TextField->GetLabelEdit()->SetFilter("1234567890");
        SetInt(0);
    }
}

void g2Spinner::SetWidth(int Width)
{
    // Directly set the text field's width
    int SpinnerWidth;
    GetTheme()->GetComponentSize(g2Theme_Spinner, &SpinnerWidth);
    TextField->SetWidth(Width - SpinnerWidth);
}

int g2Spinner::GetWidth()
{
    int SpinnerWidth;
    GetTheme()->GetComponentSize(g2Theme_Spinner, &SpinnerWidth);
    return TextField->GetWidth() + SpinnerWidth;
}

void g2Spinner::SetInt(int Value)
{
    IntVal = Value;
    char Buffer[128];
    sprintf(Buffer, "%d", IntVal);
    TextField->SetText(Buffer);
}

int g2Spinner::GetInt()
{
    // Parse current text as an integer
    // If it fails, return the original value
    int Temp = IntVal;
    if(sscanf(TextField->GetText(), "%d", &Temp) == 1)
        IntVal = Temp;
    return IntVal;
}

void g2Spinner::SetFloat(float Value)
{
    FloatVal = Value;
    char Buffer[128];
    sprintf(Buffer, "%.2f", FloatVal);
    TextField->SetText(Buffer);
}

float g2Spinner::GetFloat()
{
    // Parse current text as a float
    // If it fails, return the original value
    float Temp = FloatVal;
    if(sscanf(TextField->GetText(), "%f", &Temp) == 1)
        FloatVal = Temp;
    return FloatVal;
}

void g2Spinner::SetBounds(float min, float max)
{
    FloatMin = min;
    FloatMax = max;
}

void g2Spinner::SetBounds(int min, int max)
{
    IntMin = min;
    IntMax = max;
}

void g2Spinner::SetIncrement(float inc)
{
    FloatInc = inc;
}

void g2Spinner::SetIncrement(int inc)
{
    IntInc = inc;
}

void g2Spinner::IncrementUp()
{
    // Increase and bounds check float & int respectively
    if(Type == g2SpinnerType_Float)
        SetFloat(fmax(fmin(GetFloat() + FloatInc, FloatMax), FloatMin));
    else if(Type == g2SpinnerType_Int)
        SetInt((int)fmax(fmin(GetInt() + IntInc, IntMax), IntMin));
}

void g2Spinner::IncrementDown()
{
    // Decrease and bounds check float & int respectively
    if(Type == g2SpinnerType_Float)
        SetFloat(fmax(fmin(GetFloat() - FloatInc, FloatMax), FloatMin));
    else if(Type == g2SpinnerType_Int)
        SetInt((int)fmax(fmin(GetInt() - IntInc, IntMax), IntMin));
}

void g2Spinner::SetLiveVariable(float* LiveValue)
{
    this->LiveValue = LiveValue;
}

void g2Spinner::Render(int pX, int pY)
{
    // Source texture coordinates for spinner
    float SourceX, SourceY, SourceWidth, SourceHeight;
    int OutWidth, OutHeight;
    GetTheme()->GetComponent(g2Theme_Spinner_Pressed, &SourceX, &SourceY, &SourceWidth, &SourceHeight, &OutWidth, &OutHeight);
    
    // Compute the offsets based on the size of the text field
    int OffsetX = TextField->GetWidth();
    int OffsetY = 0;
    GetTheme()->GetComponentSize(g2Theme_TextField, NULL, &OffsetY);
    OffsetY = OffsetY / 2 - OutHeight / 2; // Centered vertically
    
    // Is the user's mouse on the top or bottom of the button?
    // Note the ternary comparison operator to do the half-height offset
    bool IsAbove = MouseY <= (OffsetY + (OutHeight / 2));
    
    // Disabled
    if(GetDisabled())
        DrawComponent(g2Theme_Spinner_Disabled, pX + OffsetX, pY + OffsetY);
    
    // Actively pressed on the buttons, need to draw only the pressed button
    else if(GetControllerState() == g2ControllerState_Pressed && MouseX > TextField->GetWidth())
    {
        // Draw background normally, then draw the pressed button
        DrawComponent(g2Theme_Spinner, pX + OffsetX, pY + OffsetY);
        DrawComponent(pX + OffsetX, pY + OffsetY + (IsAbove ? 0 : (OutHeight / 2)), OutWidth, OutHeight / 2, SourceX, SourceY + (SourceHeight / 2.0f) * (IsAbove ? 0.0f : 1.0f), SourceWidth, SourceHeight / 2.0f);
    }
    // Normal
    else
        DrawComponent(g2Theme_Spinner, pX + OffsetX, pY + OffsetY);
    
    // Increase or decrease the value based on timing
    if((PressedTime > (g2Spinner_UpdateRate + g2Spinner_UpdateMin)) || (GetControllerState() == g2ControllerState_Clicked && MouseX > TextField->GetWidth()))
    {
        if(IsAbove)
            IncrementUp();
        else
            IncrementDown();
        
        PressedTime -= g2Spinner_UpdateRate;
    }
    
    // Set the live value based on what the field currently has
    if(LiveValue != NULL)
        *LiveValue = (Type == g2SpinnerType_Float) ? GetFloat() : (float)GetInt();
}

void g2Spinner::GetCollisionRect(int* Width, int* Height)
{
    // Get the spinner size then add text length
    GetTheme()->GetComponentSize(g2Theme_Spinner, Width, Height);
    *Width += TextField->GetWidth();
}

void g2Spinner::Update(float dT)
{
    // If we are being pressed, update the timer
    if(GetControllerState() == g2ControllerState_Pressed)
        PressedTime += dT;
    // Else, we aren't pressing, so ignore
    else
        PressedTime = 0.0f;
}

void g2Spinner::MouseHover(int x, int y)
{
    // Save the mouse location
    MouseX = x;
    MouseY = y;
}
