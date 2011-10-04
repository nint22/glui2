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
    
    // Initialize the mouse position off-screen
    MouseX = INT_MIN;
    MouseY = INT_MIN;
    
    // Default to no live value
    LiveValue = NULL;
    
    // Default the float / int values
    if(Type == g2SpinnerType_Float)
    {
        TextField->SetFilter("1234567890.");
        SetFloat(0.0f);
    }
    else if(Type == g2SpinnerType_Int)
    {
        TextField->SetFilter("1234567890");
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

void g2Spinner::IncrementUp()
{
    // Increase and bounds check float & int respectively
    if(Type == g2SpinnerType_Float)
        SetFloat(fmax(fmin(FloatVal + FloatInc, FloatMax), FloatMin));
    else if(Type == g2SpinnerType_Int)
        SetInt((int)fmax(fmin(IntVal + IntInc, IntMax), IntMin));
}

void g2Spinner::IncrementDown()
{
    // Decrease and bounds check float & int respectively
    if(Type == g2SpinnerType_Float)
        SetFloat(fmax(fmin(FloatVal - FloatInc, FloatMax), FloatMin));
    else if(Type == g2SpinnerType_Int)
        SetInt((int)fmax(fmin(IntVal - IntInc, IntMax), IntMin));
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
    
    // Source texture coordinates for spinner
    float SourceX, SourceY, SourceWidth, SourceHeight;
    int OutWidth, OutHeight;
    GetTheme()->GetComponent(g2Theme_Spinner_Pressed, &SourceX, &SourceY, &SourceWidth, &SourceHeight, &OutWidth, &OutHeight);
    
    // Compute the offsets based on the size of the text field
    int OffsetX = TextField->GetWidth();
    int OffsetY = 0;
    GetTheme()->GetComponentSize(g2Theme_TextField, NULL, &OffsetY);
    OffsetY = OffsetY / 2 - OutHeight / 2; // Centered vertically
    
    // Disabled
    if(GetDisabled())
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_Spinner_Disabled);
    // Actively pressed, need to draw only the pressed button
    else if(GetControllerState() == g2ControllerState_Pressed)
    {
        // Draw background normally
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_Spinner);
        
        // Is the user's mouse on the top or bottom of the button?
        // Note the trinay comparison operator to do the half-height offset
        bool IsAbove = MouseY <= (pY + OffsetY + (OutHeight / 2));
        DrawComponent(pX + OffsetX, pY + OffsetY + (IsAbove ? 0 : (OutHeight / 2)), OutWidth, OutHeight / 2, SourceX, SourceY + (SourceHeight / 2.0f) * (IsAbove ? 0.0f : 1.0f), SourceWidth, SourceHeight / 2.0f);
        
        // Increase or decrease the value
        if(IsAbove)
            IncrementUp();
        else
            IncrementDown();
    }
    // Normal
    else
        DrawComponent(pX + OffsetX, pY + OffsetY, g2Theme_Spinner);
    
    // Set the live value based on what the field currently has
    if(LiveValue != NULL)
    {
        // Parse as a float
        float Temp = 0.0f;
        if(sscanf(TextField->GetText(), "%f", &Temp) == 1)
            *LiveValue = Temp;
        
        // Else, it failed and we place a nan
        else
            *LiveValue = NAN;
    }
}

void g2Spinner::MouseHover(int x, int y)
{
    // Save the mouse location
    MouseX = x;
    MouseY = y;
}

bool g2Spinner::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, Width, Height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_Spinner, &Width, &Height);
    
    // Compute the offsets based on the size of the text field
    int OffsetX = TextField->GetWidth();
    int OffsetY = 0;
    GetTheme()->GetComponentSize(g2Theme_TextField, NULL, &OffsetY);
    OffsetY = OffsetY / 2 - Height / 2; // Centered vertically
    
    // Grow to the correct controller offset, ignoring the text fiend
    pX += OffsetX;
    pY += OffsetY;
    
    // Are we in it? We IGNORE the text field
    if(x >= pX && x <= pX + Width && y >= pY && y <= pY + Height)
        return true;
    else
        return false;
}
