/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2ProgressBar.h"

g2ProgressBar::g2ProgressBar(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Allocate text and set initial position
    // Note that we are registereting to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(5, 5);
    Label->SetColor(0, 0, 0);
    Label->SetText("Undefined g2ProgressBar");
    
    // Default progress to none
    Progress = 0.0f;
}

const g2Label* g2ProgressBar::GetLabel()
{
    // Return the label we are working on
    return Label;
}

void g2ProgressBar::SetProgress(float Progress)
{
    // Save the progress
    if(Progress < 0.0f)
        Progress = 0.0f;
    else if(Progress > 1.0f)
        Progress = 1.0f;
    this->Progress = Progress;
}

void g2ProgressBar::Render()
{
    // Get the controller location
    int pX, pY;
    GetPos(&pX, &pY);
    
    // Draw the background
    if(GetDisabled())
        DrawComponent(pX, pY, g2Theme_ProgressBar_Disabled);
    else
        DrawComponent(pX, pY, g2Theme_ProgressBar);
    
    // Get the texture points for the progress bar
    float tx, ty, tw, th;
    int width, height;
    GLuint textID;
    bool IsFound = GetTheme()->GetComponent(g2Theme_ProgressBar_Fill, &tx, &ty, &tw, &th, &width, &height, &textID);
    g2Assert(IsFound, "Unable to retrieve a component's (ID: %d) texture information", g2Theme_ProgressBar_Fill);
    
    // Draw
    DrawComponent(pX, pY, width * Progress, height, tx, ty, tw * Progress, th);
}

bool g2ProgressBar::InController(int x, int y)
{
    // User never interacts with a progress bar
    return false;
}
