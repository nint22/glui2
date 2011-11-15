/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Panel.cpp/h
 Desc: A tiled background and placement manager for GUI
 controllers. A panel allows end-developers to add new GUI anchored
 controllers so that window movement and resizing will automatically
 move around and manage the UI's positions. The end-developer
 may explicitly set the size and thus turn off the anchoring
 feature so that this panel will act as a window.
 
***************************************************************/

// Inclusion guard
#ifndef __G2PANEL_H__
#define __G2PANEL_H__

#include "g2Controller.h"
#include "g2Button.h"
#include "g2Label.h"
#include "g2CheckBox.h"
#include "g2Console.h"
#include "g2TextField.h"
#include "g2RadioGroup.h"
#include "g2DropDown.h"
#include "g2Dialog.h"
#include "g2Slider.h"
#include "g2ProgressBar.h"
#include "g2Spinner.h"

class g2Panel : public g2Controller
{
public:
    
    // Panel constructor
    __g2EXPORT g2Panel(g2Controller* Parent, g2Theme* MainTheme, g2Anchor Anchors = g2Anchor_None, const char* Title = NULL);
    
    // Set the alignment style; non-oposing combinations can be made, such as anchoring
    // to the top-left (which is done by doing the bit-wise combination of "g2Anchor_Top | g2Anchor_Left")
    __g2EXPORT void SetAlignment(g2Anchor Anchors);
    
    // Return the alignment style
    __g2EXPORT g2Anchor GetAlignment();
    
    // Set a title to the panel
    __g2EXPORT void SetTitle(const char* Title);
    
    // Retrieve the title of the panel
    __g2EXPORT g2Label* GetTitle();
    
    // Explicitly set the size of this panel, thus turning it into a window-based shape
    // Controllers will move based on resizing and the weighting. Unless the anchor / alignment
    // is set in g2Anchor_none, all new widths or heights may be ignored except for the appropriate handler..
    __g2EXPORT void SetSize(int NewWidth, int NewHeight);
    
    // Get the current size of the panel
    __g2EXPORT void GetSize(int* Width = NULL, int* Height = NULL);
    
    /*** Factory Methods ***/
    
    __g2EXPORT g2Button* AddButton(int x, int y, const char* Label = NULL, __g2CallBack(callback) = 0);
    
    __g2EXPORT g2Label* AddLabel(int x, int y, const char* Text = NULL);
    
    __g2EXPORT g2CheckBox* AddCheckBox(int x, int y, const char* Text, __g2CallBack(callback) = 0, bool* LiveCheckState = NULL);
    
    __g2EXPORT g2TextField* AddTextField(int x, int y, const char* Text = NULL);
    
    __g2EXPORT g2RadioGroup* AddRadioGroup(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL);
    
    __g2EXPORT g2DropDown* AddDropDown(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL);
    
    __g2EXPORT g2Dialog* AddDialog(g2DialogType Type, const char* Message = NULL);
    
    __g2EXPORT g2Slider* AddSlider(int x, int y, __g2CallBack(callback) = 0, float* LiveValue = NULL);
    
    __g2EXPORT g2ProgressBar* AddProgressBar(int x, int y);
    
    __g2EXPORT g2Spinner* AddSpinner(int x, int y, g2SpinnerType Type, __g2CallBack(callback) = 0, float* LiveValue = NULL);
    
protected:
    
    // Render
    __g2EXPORT void Render(int pX, int pY);
    
    // Define controller geometry
    __g2EXPORT void GetCollisionRect(int* Width, int* Height);
    
    // Window resize event
    __g2EXPORT void WindowResizeEvent(int NewWidth, int NewHeight);
    
private:
    
	// Center the title
	void CenterTitle();

    // Alognment flag for placement
    g2Anchor Anchors;
    
    // Entire panel's surface width and height
    int Width, Height;
    
    // Full window size, used for alignment over time
    int WindowWidth, WindowHeight;
    
    // Title text
    g2Label* Label;
    
};

// End of inclusion guard
#endif
