/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Bubble.cpp/h for Example4
 Desc: A custom control written as an example on how to create
 a new Glui2 controller, which in this case is a bubble widget.
 
 A bubble widget is similar to a pop up but is simply a curved
 edge text box with a multi-line label.
 
 Note that the g2Default theme (g2Default.cfg/png) was updated
 to include bitmap and point/size data for the 
 
***************************************************************/

// Inclusion guard
#ifndef __G2BUBBLE_H__
#define __G2BUBBLE_H__

// Includes for creating custom g2 component
#include <Glui2/glui2.h>
#include <Glui2/g2Controller.h>

class g2Bubble : public g2Controller
{
public:
    
    // Button constructor
    g2Bubble(g2Controller* Parent, g2Theme* MainTheme);
    
    // Get access to the label
    g2Label* GetLabel();
    
protected:
    
    // Render
    void Render(int x, int y);
    
private:
    
    // The bubble's text label
    g2Label* Label;
    
};

// End of inclusion guard
#endif
