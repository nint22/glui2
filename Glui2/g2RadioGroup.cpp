/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 ***************************************************************/

#include "g2RadioGroup.h"

g2RadioGroup::g2RadioGroup(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Set the labels to null
    OptionCount = 0;
    ActiveIndex = 0;
	Labels = NULL;
    
    // Default to no live value
    LiveIndex = NULL;
}

g2RadioGroup::~g2RadioGroup()
{
    // Labels self-release as they are registered to this object
}

void g2RadioGroup::SetOptions(const char** OptionLabels, int OptionCount)
{
    // Save option count
    this->OptionCount = OptionCount;
    
    // Release existing labels as needed
    if(Labels != NULL)
        delete[] Labels;
    Labels = new g2Label*[OptionCount];
    
    // Get the size of a radio button
    int RadioWidth, RadioHeight;
    GetTheme()->GetComponentSize(g2Theme_RadioButton, &RadioWidth, &RadioHeight);
    
    // Computer offsets based on radio width/height sizes
    int OffsetX = int(float(RadioWidth) * 0.4f);
    int OffsetY = int(float(RadioHeight) * 0.25f);
    
    // Assert the given pointer is valid
    g2Assert(OptionLabels != NULL, "Given OptionLabels is NULL.");
    for(int i = 0; i < OptionCount; i++)
    {
        // Assert the given element is valid
        g2Assert(OptionLabels[i] != NULL, "Given index OptionLabels[%d] is NULL.", i);
        
        // Create a new label with these properties (move down for each option)
        Labels[i] = new g2Label(this, GetTheme());
        Labels[i]->SetPos(RadioWidth + OffsetX, i * (RadioHeight + 1) + OffsetY);
        Labels[i]->SetText(OptionLabels[i]);
        Labels[i]->SetColor(0.0f, 0.0f, 0.0f);
    }
}

void g2RadioGroup::SetSelectionIndex(int Index)
{
    if(Index < 0)
        ActiveIndex = 0;
    else if(Index > OptionCount)
        ActiveIndex = OptionCount - 1;
    else
        ActiveIndex = Index;
}

int g2RadioGroup::GetSelectionIndex()
{
    return ActiveIndex;
}

void g2RadioGroup::SetLiveVariable(int* LiveIndex)
{
    this->LiveIndex = LiveIndex;
}

void g2RadioGroup::Render(int pX, int pY)
{
    // Get the size of a radio button
    int RadioHeight;
    GetTheme()->GetComponentSize(g2Theme_RadioButton, NULL, &RadioHeight);
    
    // For each option; draw with a pixel buffer
    for(int i = 0; i < OptionCount; i++)
    {
        // Draw the radio button
        if(GetDisabled())
            DrawComponent((i == ActiveIndex) ? g2Theme_RadioButton_Pressed_Disabled : g2Theme_RadioButton_Disabled, pX, pY + i * (RadioHeight + 1));
        else
            DrawComponent((i == ActiveIndex) ? g2Theme_RadioButton_Pressed : g2Theme_RadioButton, pX, pY + i * (RadioHeight + 1));
    }
    
    // Note that labels self-draw as they are registered as children
}

void g2RadioGroup::GetCollisionRect(int* Width, int* Height)
{
    // Get the size of a radio button
    int RadioWidth;
    GetTheme()->GetComponentSize(g2Theme_RadioButton, &RadioWidth, Height);
    *Height = (*Height + 1) * OptionCount;
    
    // For each option, save the biggest text length
    for(int i = 0; i < OptionCount; i++)
    {
        // Get current labels length
        int LabelWidth = Labels[i]->GetWidth() + RadioWidth + 1;
        if(LabelWidth > *Width)
            *Width = LabelWidth;
    }
}

void g2RadioGroup::MouseClick(g2MouseButton button, g2MouseClick state, int x, int y)
{
    // If we had a full key-press event within our collision box, change the active index as needed
    if(InController(x, y) && GetControllerState() == g2ControllerState_Clicked)
    {
        // Get the size of a radio button
        int RadioHeight;
        GetTheme()->GetComponentSize(g2Theme_RadioButton, NULL, &RadioHeight);
        
        // For each radio button..
        for(int i = 0; i < OptionCount; i++)
        {
            // What is the y pos of this row?
            int BottomRow = i * (RadioHeight + 1) + RadioHeight;
            if(y < BottomRow)
            {
                ActiveIndex = i;
                break;
            }
        }
        
        // Update the live index
        if(LiveIndex !=  NULL)
            *LiveIndex = ActiveIndex;
    }
    
}
