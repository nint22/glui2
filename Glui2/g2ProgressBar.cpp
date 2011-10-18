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
    // Allocate text and set initial position vertically centered
    Label = new g2Label(this, MainTheme);
    Label->SetColor(0, 0, 0);
    SetText("");
    
    // Default progress to none
    Progress = 0.0f;
    MinBound = 0.0f;
    MaxBound = 1.0f;
}

const g2Label* g2ProgressBar::GetLabel()
{
    // Return the label we are working on
    return Label;
}

void g2ProgressBar::SetBounds(float Lower, float Upper)
{
    MinBound = Lower;
    MaxBound = Upper;
}

void g2ProgressBar::SetProgress(float Progress)
{
    // Apply limits, save values
    this->Progress = fmax(fmin(Progress, MaxBound), MinBound);
}

void g2ProgressBar::SetText(const char* Text)
{
    // Change the label itself (empty text if null)
    Label->SetText(Text == NULL ? "" : Text);
    
    // What is the new length of this text?
    int NewLength = Label->GetWidth();
    
    // Is this new length bigger than the old width? If so, save
    if(NewLength > Width)
        SetWidth(NewLength);
    else
        SetWidth(Width);
}

void g2ProgressBar::SetWidth(int Width)
{
    // What is the button's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(g2Theme_ProgressBar, &MinWidth);
    
    if(Width > MinWidth)
        this->Width = Width;
    else
        this->Width = MinWidth;
    
    // Set the initial width to a default width value
    int BarHeight;
    GetTheme()->GetComponentSize(g2Theme_ProgressBar, NULL, &BarHeight);
    int Centered = BarHeight / 2 - GetTheme()->GetCharacterHeight() / 2;
    
    // Center text
    Label->SetPos(this->Width / 2 - Label->GetWidth() / 2, Centered);
}

void g2ProgressBar::Render(int pX, int pY)
{
    // What component should we be rendering?
    g2ThemeElement ProgressState = g2Theme_ProgressBar;
    if(GetDisabled())
        ProgressState = g2Theme_ProgressBar_Disabled;
    
    // Render the background using a target width
    DrawComponentStretch(ProgressState, pX, pY, Width);
    
    // Get the height of both the background and foreground (for centering)
    int BackHeight, FrontHeight;
    GetTheme()->GetComponentSize(g2Theme_ProgressBar, NULL, &BackHeight);
    GetTheme()->GetComponentSize(g2Theme_ProgressBar_Fill, NULL, &FrontHeight);
    
    // Draw the fill based on the fill ratio
    float FillRatio = Progress / fabs(MaxBound - MinBound);
    int FillWidth = int(float(Width) * FillRatio);
    
    // Render the filler graphic
    DrawComponentStretch(g2Theme_ProgressBar_Fill, pX, pY + BackHeight / 2 - FrontHeight / 2, FillWidth);
}
