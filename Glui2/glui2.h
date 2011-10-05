/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: glui2.h
 Desc: The main header file associated with the GLUI2 library.
 All files begin with the "g2" string are associated with this
 library. This file also implements the interface in which
 end-programmers will have to interface with and connect with.
 
 This object instance is where to install glui2 into your OpenGL
 application as well as used to instantiate new GUI components.
 
 The design pattern of GLUI2 is to use a factory system: you
 should always use this class to create new UI components to
 render on-screen; simply use the family of "AddXYZ". All
 factory methods return the object created; either use "RemoveXYZ"
 or delete the object directly to remove it from the GUI.
 
 To use / install Glui2, simply instantiate your own Glui2 object
 of this class, then (optionally) register your own callback
 functions (there are 5).
 
 Note to self: This library currently directly draws onto
 the front buffer which doesn't change visual output, but
 doesn't follow the standard "backbuffer" drawing approach.
 To help with performance, we ONLY draw elements that need
 to be drawn, so we might actually not render / push to the
 front buffer unless we explicitly need to per frame.
 
***************************************************************/

// Inclusion guard
#ifndef __GLUI2__H__
#define __GLUI2__H__

// Include necessary Glui2 headers
#include "g2Utilities.h"
#include "g2Theme.h"
#include "g2Controller.h"

// Include all built-in controllers
#include "g2Button.h"
#include "g2Label.h"
#include "g2CheckBox.h"
#include "g2Console.h"
#include "g2TextField.h"
#include "g2RadioGroup.h"
#include "g2DropDown.h"
#include "g2Dialog.h"
#include "g2Panel.h"
#include "g2Slider.h"
#include "g2ProgressBar.h"
#include "g2Spinner.h"

// GLUI2 main interfacing / factory class
class Glui2
{
public:
    
    // Takes a theme file; defaults to the g2Default theme
    // X and Y Offsets are the distance from the anchor; default to 0
    // Width and height are how big the UI window is; based on the anchor, either the width or hieght will be ignored (i.e. left / right anchor ignores height)
    // windowPlacement is a bitwise structure that can be combined (i.e. using "|" ) to define window anchor
    // ThemFile is the location of the theme file to load
    Glui2(const char* ThemeFile = NULL, void (*GlutIdleFunc)(void) = NULL, void (*GlutReshapeFunc)(int width, int height) = NULL, void (*GlutKeyboardFunc)(unsigned char key, int x, int y) = NULL, void (*GlutSpecialFunc)(int key, int x, int y) = NULL, void (*GlutMouseFunc)(int button, int state, int x, int y) = NULL, void (*GlutHoverFunc)(int x, int y) = NULL);
    
    // Destructor removes all GUI elements
    ~Glui2();
    
    /*** Factory Methods ***/
    
    g2Button* AddButton(int x, int y, const char* Label = NULL, __g2CallBack(callback) = 0);
    
    g2Label* AddLabel(int x, int y, const char* Text = NULL);
    
    g2CheckBox* AddCheckBox(int x, int y, const char* Text, __g2CallBack(callback) = 0, bool* LiveCheckState = NULL);
    
    g2Console* AddConsole();
    
    g2TextField* AddTextField(int x, int y, const char* Text = NULL);
    
    g2RadioGroup* AddRadioGroup(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL);
    
    g2DropDown* AddDropDown(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback) = 0, int* LiveIndex = NULL);
    
    g2Dialog* AddDialog(g2DialogType Type, const char* Message = NULL);
    
    g2Panel* AddPanel(g2Anchor AnchorFlags);
    
    g2Slider* AddSlider(int x, int y, __g2CallBack(callback) = 0, float* LiveValue = NULL);
    
    g2ProgressBar* AddProgressBar(int x, int y);
    
    g2Spinner* AddSpinner(int x, int y, g2SpinnerType Type, __g2CallBack(callback) = 0, float* LiveValue = NULL);
    
    /*** Accessors to Parent and Theme ***/
    
    // Get the root parent controller
    g2Controller* GetRootController();
    
    // Get active theme
    g2Theme* GetMainTheme();
    
    /*** Internal Rendering & Update ***/
    
    // Render glui2 event
    // Draw all glui2 elements on-screen
    void Render();
    
private:
    
    // Update glui2 event
    // Automatically managed by the GLUT callbacks
    void Update();
    
    /*** Window / Theme Structures ***/
    
    // Window size
    int WindowWidth, WindowHeight;
    
    // The theme object; used to retrieve bitmap data
    g2Theme MainTheme;
    
    /*** User-Overloaded Glut Callbacks ***/
    
    void (*GlutIdleFunc)(void);
    void (*GlutReshapeFunc)(int width, int height);
    void (*GlutKeyboardFunc)(unsigned char key, int x, int y);
    void (*GlutSpecialFunc)(int key, int x, int y);
    void (*GlutMouseFunc)(int button, int state, int x, int y);
    void (*GlutHoverFunc)(int x, int y);
    
    /*** Internal Callback Functions ***/
    
    // Called back externally through parent window
    static void __IdleFunc();
    static void __ReshapeFunc(int width, int height);
    static void __KeyboardFunc(unsigned char key, int x, int y);
    static void __SpecialFunc(int key, int x, int y);
    static void __MouseFunc(int button, int state, int x, int y);
    static void __HoverFunc(int x, int y);
    
    /*** Root GUI Tree Node & Active Node ***/
    
    // Root GUI node
    g2Controller* RootController;
    
    // Active controller (last controller clicked)
    g2Controller* ActiveController;
    
};

// End of inclusion guard
#endif
