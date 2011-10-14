/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2DropDown.h"

g2DropDown::g2DropDown(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Create a text field in which we will drop-down items
    ButtonField = new g2Button(this, MainTheme);
    ButtonField->SetText("Default...");
    //ButtonField->SetDisabled(true);
    
    // Default options
    OptionCount = 0;
	Buttons = NULL;
    ActiveIndex = 0;
    ActiveSelection = -1;
    
    // Default width
    SetWidth(0);
    
    // default to not rolled out
    IsDragging = false;
    
    // Default to no live value
    LiveIndex = NULL;
}

void g2DropDown::SetWidth(int Width)
{
    // What is the button's minimum size?
    int DropdownWidth;
    GetTheme()->GetComponentSize(g2Theme_DropDown, &DropdownWidth);
    
    // Directly set the text field's width and others
    ButtonField->SetWidth(Width - DropdownWidth);
    for(int i = 0; i < OptionCount; i++)
        Buttons[i]->SetWidth(ButtonField->GetWidth());
}

int g2DropDown::GetWidth()
{
    int DropdownWidth;
    GetTheme()->GetComponentSize(g2Theme_DropDown, &DropdownWidth);
    return ButtonField->GetWidth() + DropdownWidth;
}

void g2DropDown::SetOptions(const char** OptionLabels, int OptionCount)
{
    // Save option count
    this->OptionCount = OptionCount;
    
    // Release existing buttons as needed
    if(Buttons != NULL)
        delete[] Buttons;
    Buttons = new g2Button*[OptionCount];
    
    // Get the vertical size of characters
    int CharHeight;
    GetTheme()->GetCharacterSize(NULL, &CharHeight);
    CharHeight += 2;
    
    // Get the button height to offset
    int ButtonHeight;
    GetTheme()->GetComponentSize(g2Theme_Button, NULL, &ButtonHeight);
    
    // Assert the given pointer is valid
    g2Assert(OptionLabels != NULL, "Given OptionLabels is NULL.");
    for(int i = 0; i < OptionCount; i++)
    {
        // Assert the given element is valid
        g2Assert(OptionLabels[i] != NULL, "Given index OptionLabels[%d] is NULL.", i);
        
        // Create a new label with these properties (move down for each option)
        Buttons[i] = new g2Button(this, GetTheme());
        Buttons[i]->SetPos(0, i * ButtonHeight + ButtonHeight);
        Buttons[i]->SetText(OptionLabels[i]);
        Buttons[i]->SetDisabled(true);
        Buttons[i]->SetWidth(ButtonField->GetWidth());
        Buttons[i]->SetColor(1.0f, 1.0f, 1.0f, DeselectedAlpha);
        
        // Default invisible and disabled
        Buttons[i]->SetVisibility(false);
    }
    
    // Default the index to 0
    SetSelectionIndex(0);
    
    // Reset width
    SetWidth(GetWidth());
}

void g2DropDown::SetSelectionIndex(int Index)
{
    // Bounds check
    if(Index < 0)
        ActiveIndex = 0;
    else if(Index >= OptionCount)
        ActiveIndex = OptionCount - 1;
    else
        ActiveIndex = Index;
    
    // Update top-level string / button
    ButtonField->SetText(Buttons[ActiveIndex]->GetLabel()->GetText());
}

int g2DropDown::GetSelectionIndex()
{
    return ActiveIndex;
}

void g2DropDown::SetLiveVariable(int* LiveIndex)
{
    this->LiveIndex = LiveIndex;
}

void g2DropDown::Render(int pX, int pY)
{
    // Get the width and offsets
    int DropdownWidth, DropdownOffset;
    GetTheme()->GetComponentSize(g2Theme_DropDown, &DropdownWidth);
    DropdownOffset = ButtonField->GetWidth();
    
    // Draw based on the current state
    if(GetDisabled())
        DrawComponent(pX + DropdownOffset, pY, g2Theme_DropDown_Disabled);
    else if(GetControllerState() == g2ControllerState_Pressed)
    {
        IsDragging = true;
        DrawComponent(pX + DropdownOffset, pY, g2Theme_DropDown_Pressed);
    }
    else
        DrawComponent(pX + DropdownOffset, pY, g2Theme_DropDown);
    
    // Did we click? If so, cycle visibility
    for(int i = 0; i < OptionCount; i++)
        Buttons[i]->SetVisibility(IsDragging);
    
    // Update the live variable
    if(LiveIndex != NULL)
        *LiveIndex = ActiveIndex;
}

void g2DropDown::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // Release drag and select what we have
    if(button == g2MouseButton_Left && state == g2MouseClick_Up)
    {
        // Reset dragging and save the active index
        IsDragging = false;
        if(ActiveSelection >= 0)
            SetSelectionIndex(ActiveSelection);
        
        // Reset alpha color and hide
        for(int i = 0; i < OptionCount; i++)
            Buttons[i]->SetColor(1.0f, 1.0f, 1.0f, DeselectedAlpha);
    }
}

void g2DropDown::MouseHover(int x, int y)
{
    // Are we dragging?
    if(IsDragging)
    {
        // Reset to make sure we don't default to anything
        ActiveSelection = -1;
        
        // Color hovered objects
        for(int i = 0; i < OptionCount; i++)
        {
            if(Buttons[i]->InController(x, y))
            {
                Buttons[i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
                ActiveSelection = i;
            }
            else
                Buttons[i]->SetColor(1.0f, 1.0f, 1.0f, DeselectedAlpha);
        }
    }
}

bool g2DropDown::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Get the width and offsets
    int DropdownWidth, DropdownHeight;
    GetTheme()->GetComponentSize(g2Theme_DropDown, &DropdownWidth, &DropdownHeight);
    DropdownWidth += ButtonField->GetWidth();
    
    // Are we in it?
    if(x >= pX && x <= pX + DropdownWidth && y >= pY && y <= pY + DropdownHeight)
        return true;
    else
        return false;
}
