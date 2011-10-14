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
    // Note that we are registering to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(5, 5);
    Label->SetColor(0, 0, 0);
    SetText("Undefined");
    
    // Set the initial width to a default width value
    GetTheme()->GetComponentSize(g2Theme_ProgressBar, &Width);
    
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
        Width = NewLength;
    
    // Center text
    Label->SetPos(5 + Width / 2 - Label->GetWidth() / 2, 5);
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
    
    // Center text
    Label->SetPos(5 + Width / 2 - Label->GetWidth() / 2, 5);
}

void g2ProgressBar::Render(int pX, int pY)
{
    // What component should we be rendering?
    g2ThemeElement ProgressState = g2Theme_ProgressBar;
    if(GetDisabled())
        ProgressState = g2Theme_ProgressBar_Disabled;
    
    // What is the progress bar's minimum size?
    int MinWidth = 0;
    GetTheme()->GetComponentSize(ProgressState, &MinWidth);
    
    /*** Background ***/
    
    // If default size, just render normally
    if(Width == MinWidth)
        DrawComponent(pX, pY, ProgressState);
    
    // Else, we have to draw the two sides and stretch the middle
    else
    {
        // Source texture coordinates
        float SourceX, SourceY, SourceWidth, SourceHeight;
        int OutWidth, OutHeight;
        GetTheme()->GetComponent(ProgressState, &SourceX, &SourceY, &SourceWidth, &SourceHeight, &OutWidth, &OutHeight);
        
        // Draw the left-most third
        DrawComponent(pX, pY, OutWidth / 3, OutHeight, SourceX, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the right-most third
        DrawComponent(pX + Width - OutWidth / 3, pY, OutWidth / 3, OutHeight, SourceX + (2.0f * SourceWidth) / 3.0f, SourceY, SourceWidth / 3.0f, SourceHeight);
        
        // Draw the middle two positions
        // Note the overlap between the middle's right side and the right side's left lip
        // This is to make sure there isn't a pixel space
        DrawComponent(pX + OutWidth / 3.0f, pY, Width - (2.0f * OutWidth) / 3.0f + 1, OutHeight, SourceX + SourceWidth / 3.0f, SourceY, SourceWidth - (2.0f * SourceWidth) / 3.0f, SourceHeight);
    }
    
    /*** Foreground ***/
    
    // Draw the fill based on the fill ratio
    float FillRatio = Progress / fabs(MaxBound - MinBound);
    int FillWidth = int(float(Width) * FillRatio);
    
    // Source texture coordinates
    float SourceX, SourceY, SourceWidth, SourceHeight;
    int OutWidth, OutHeight;
    GetTheme()->GetComponent(g2Theme_ProgressBar_Fill, &SourceX, &SourceY, &SourceWidth, &SourceHeight, &OutWidth, &OutHeight);
    
    // Draw the left-most third
    DrawComponent(pX, pY, OutWidth / 3, OutHeight, SourceX, SourceY, SourceWidth / 3.0f, SourceHeight);
    
    // Draw the right-most third
    DrawComponent(pX + FillWidth - OutWidth / 3, pY, OutWidth / 3, OutHeight, SourceX + (2.0f * SourceWidth) / 3.0f, SourceY, SourceWidth / 3.0f, SourceHeight);
    
    // Draw the middle two positions
    // Note the overlap between the middle's right side and the right side's left lip
    // This is to make sure there isn't a pixel space
    DrawComponent(pX + OutWidth / 3.0f, pY, FillWidth - (2.0f * OutWidth) / 3.0f + 1, OutHeight, SourceX + SourceWidth / 3.0f, SourceY, SourceWidth - (2.0f * SourceWidth) / 3.0f, SourceHeight);
}

bool g2ProgressBar::InController(int x, int y)
{
    // User never interacts with a progress bar
    return false;
}
