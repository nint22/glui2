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
    ActiveIndex = 0;
    
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
    
    // Assert the given pointer is valid
    g2Assert(OptionLabels != NULL, "Given OptionLabels is NULL.");
    for(int i = 0; i < OptionCount; i++)
    {
        // Assert the given element is valid
        g2Assert(OptionLabels[i] != NULL, "Given index OptionLabels[%d] is NULL.", i);
        
        // Create a new label with these properties (move down for each option)
        Labels[i] = new g2Label(this, GetTheme());
        Labels[i]->SetPos(10, i * 10);
        Labels[i]->SetText(OptionLabels[i]);
    }
}

int g2RadioGroup::GetSelectionIndex()
{
    return ActiveIndex;
}

void g2RadioGroup::SetLiveVariable(int* LiveIndex)
{
    this->LiveIndex = LiveIndex;
}

void g2RadioGroup::Render()
{
    // Get origin
    int pX, pY;
    GetPos(&pX, &pY);
    
    // NEED TO IMPLEMENT WITH LIVE INDEX! LiveIndex
    
    // For each for
    for(int i = 0; i < OptionCount; i++)
    {
        // Draw the radio button
        if(GetDisabled())
            DrawComponent(pX, pY + i * 10, g2Theme_RadioButton_Disabled);
        else if(GetControllerState() == g2ControllerState_Pressed)
            DrawComponent(pX, pY + i * 10, g2Theme_RadioButton_Pressed);
        else
            DrawComponent(pX, pY + i * 10, g2Theme_RadioButton);
    }
    
    // Note that labels self-draw as they are registered as children
}

bool g2RadioGroup::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_CheckBox, &width, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
