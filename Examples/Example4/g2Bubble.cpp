/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

#include "g2Bubble.h"

g2Bubble::g2Bubble(g2Controller* Parent, g2Theme* MainTheme)
: g2Controller(Parent, MainTheme)
{
    // Allocate text and set initial position
    // Note that we are registereting to this button, not the root-parent
    Label = new g2Label(this, MainTheme);
    Label->SetPos(35, 25);
    Label->SetColor(0, 0, 0);
    Label->SetText("  This is a very\nsimple text-bubble\n     example!");
}

g2Label* g2Bubble::GetLabel()
{
    return Label;
}

void g2Bubble::Render(int x, int y)
{
    // Render at position
    DrawComponent("Bubble", x, y);
}
