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
    // Note that we are registereting to this button, not the root-parent
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
    
    // Default to no live value
    LiveValue = NULL;
    
    // Default the float / int values
    if(Type == g2SpinnerType_Float)
        SetFloat(0.0f);
    else if(Type == g2SpinnerType_Int)
        SetInt(0);
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
    return FloatVal;
}

void g2Spinner::SetLimit(float min, float max)
{
    FloatMin = min;
    FloatMax = max;
}

void g2Spinner::SetLimit(int min, int max)
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

void g2Spinner::SetLiveVariable(float* LiveValue)
{
    this->LiveValue = LiveValue;
}

void g2Spinner::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Get the height for the slider button based on the current collision
    int height;
    bool IsFound = GetTheme()->GetComponentSize(g2Theme_Spinner, NULL, &height);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", g2Theme_Spinner);
    
    // SET LIVE VALUE!!!!
    // TODO
    
    // Calculate horizontal and vertical offsets for the button
    int OffsetY, OffsetX = TextField->GetWidth();
    GetTheme()->GetComponentSize(g2Theme_TextField, NULL, &OffsetY);
    OffsetY = abs(OffsetY - height);
    OffsetY /= 2;
    
    // Draw the spinner button
    // Note that the 100+ pixel offset is for the text field
    if(GetDisabled())
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_Spinner_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_Spinner_Pressed);
    else
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_Spinner);
    
}

bool g2Spinner::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, Width, Height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_Spinner, &Width);
    GetTheme()->GetComponentSize(g2Theme_Spinner, &Height);
    Width += TextField->GetWidth();
    
    // Are we in it?
    if(x >= pX && x <= pX + Width && y >= pY && y <= pY + Height)
        return true;
    else
        return false;
}
