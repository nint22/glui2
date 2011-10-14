/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 ***************************************************************/

#include "g2Panel.h"

g2Panel::g2Panel(g2Controller* Parent, g2Theme* MainTheme, g2Anchor Anchors)
: g2Controller(Parent, MainTheme)
{
    // Save the given anchor points
    this->Anchors = Anchors;
    Width = Height = 128;
    
    // Default ratio to 20%
    Ratio = 0.2f;
}

void g2Panel::AddController(g2Controller* Child)
{
    // Todo...
}

void g2Panel::SetAnchors(g2Anchor Anchors)
{
    this->Anchors = Anchors;
}

void g2Panel::SetSize(float Ratio)
{
    // Min/max bounds to [0.0, 1.0]
    Ratio = fmax(fmin(Ratio, 1.0f), 0.0f);
    
    // Set the ratio of the overlap
    this->Ratio = Ratio;
}

void g2Panel::SetSize(int NewWidth, int NewHeight)
{
    // Default to no anchors when explicitly setting the width / height
    Anchors = g2Anchor_None;
    Width = NewWidth;
    Height = NewHeight;
}

void g2Panel::Render(int pX, int pY)
{
    // Get the size of the original tile
    int tWidth, tHeight;
    GetTheme()->GetComponentSize(g2Theme_Panel, &tWidth, &tHeight);
    
    // Draw all major tiles we can in a grid
    for(int y = 0; y < int(float(Height) / float(tHeight)); y++)
    for(int x = 0; x < int(float(Width) / float(tWidth)); x++)
        DrawComponent(pX + x * tWidth, pY + y * tHeight, g2Theme_Panel);
    
    // For all the partial right-components
    if(Width % tWidth != 0)
    {
        float overlap = float(tWidth) / float(Width - tWidth * (Width % tWidth));
        for(int y = 0; y < int(float(Height) / float(tHeight)); y++)
            DrawComponent(pX, pY + y * tHeight, int(float(tWidth) * overlap), tHeight, g2Theme_Panel);
    }
    
    // For all the partial bottom-components
    if(Height % tHeight != 0)
    {
        float overlap = float(tHeight) / float(Height - tHeight * (Height % tHeight));
        for(int x = 0; x < int(float(Width) / float(tWidth)); x++)
            DrawComponent(pX + x * tWidth, pY, tWidth, int(float(tHeight) * overlap), g2Theme_Panel);
    }
    
    // For the bottom right component
    if((Width % tWidth != 0) && (Height % tHeight != 0))
    {
        // Calculate the width and height overlaps
        float wOverlap = float(tWidth) / float(Width - tWidth * (Width % tWidth));
        float hOverlap = float(tHeight) / float(Height - tHeight * (Height % tHeight));
        
        // Draw the bottom right corner
        DrawComponent(pX, pY, int(float(tWidth) * wOverlap), int(float(tHeight) * hOverlap), g2Theme_Panel);
    }
}

void g2Panel::WindowResizeEvent(int NewWidth, int NewHeight)
{
    // If on top, copy width, keep 20% visible
    if((Anchors & g2Anchor_Top) == g2Anchor_Top)
    {
        Width = NewWidth;
        Height = int(Ratio * float(NewHeight));
        SetPos(0, 0);
    }
    // If on bottom, copy width, keep 20% visible from bottom
    else if((Anchors & g2Anchor_Bottom) == g2Anchor_Bottom)
    {
        Width = NewWidth;
        Height = int(Ratio * float(NewHeight));
        SetPos(0, NewHeight - Height);
    }
    // If we are on the left, copy height, keep 20% visible from left
    else if((Anchors & g2Anchor_Left) == g2Anchor_Left)
    {
        Width = int(Ratio * float(NewWidth));
        Height = NewHeight;
        SetPos(0, 0);
    }
    // If we are on the right, copy height, keep 20% visible from right
    else if((Anchors & g2Anchor_Left) == g2Anchor_Left)
    {
        Width = int(Ratio * float(NewWidth));
        Height = NewHeight;
        SetPos(NewWidth - Width, 0);
    }    
}

bool g2Panel::InController(int x, int y)
{
    // Current GUI position and size
    int pX, pY, width, height;
    GetPos(&pX, &pY);
    GetTheme()->GetComponentSize(g2Theme_Button, &width, &height);
    
    // Are we in it?
    if(x >= pX && x <= pX + width && y >= pY && y <= pY + height)
        return true;
    else
        return false;
}
