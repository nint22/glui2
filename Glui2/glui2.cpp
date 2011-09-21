/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
***************************************************************/

#include "glui2.h"

// Internal instance handle
static Glui2* __G2_HANDLE__ = NULL;

// Define the default theme file name
static const char* __G2_DEFAULT_THEME__ = "g2Default.cfg";

Glui2::Glui2(int ParentID, const char* ThemeFile, void (*GlutIdleFunc)(void), void (*GlutReshapeFunc)(int width, int height), void (*GlutKeyboardFunc)(unsigned char key, int x, int y), void (*GlutSpecialFunc)(int key, int x, int y), void (*GlutMouseFunc)(int button, int state, int x, int y), void (*GlutHoverFunc)(int x, int y), void (*GlutDragFunc)(int x, int y))
{
    // Save self reference
    g2Assert(__G2_HANDLE__ == NULL, "Unable to allocate more than one instance of Glui2");
    __G2_HANDLE__ = this;
    
    // Default all call-backs to null
    this->GlutIdleFunc = GlutIdleFunc;
    this->GlutReshapeFunc = GlutReshapeFunc;
    this->GlutKeyboardFunc = GlutKeyboardFunc;
    this->GlutSpecialFunc = GlutSpecialFunc;
    this->GlutHoverFunc = GlutHoverFunc;
    this->GlutMouseFunc = GlutMouseFunc;
    
    // Register all needed callbacks
    glutIdleFunc(__IdleFunc);
    glutReshapeFunc(__ReshapeFunc);
    glutKeyboardFunc(__KeyboardFunc);
    glutSpecialFunc(__SpecialFunc);
    glutPassiveMotionFunc(__HoverFunc);
    glutMouseFunc(__MouseFunc);
    
    // Attempt to load given theme file if not null
    if(ThemeFile == NULL)
        MainTheme.Load(__G2_DEFAULT_THEME__);
    else
        MainTheme.Load(ThemeFile);
    
    // Default root to have no ownership
    RootController = new g2Controller(NULL, &MainTheme);
}

Glui2::~Glui2()
{
    // Nothing to release
}

g2Button* Glui2::AddButton(int x, int y, const char* Label)
{
    // Allocate a new button and add to parent
    g2Button* NewButton = new g2Button(RootController, &MainTheme);
    NewButton->SetPos(x, y);
    
    return NewButton;
}

g2Label* Glui2::AddLabel(int x, int y, const char* Text)
{
    // Allocate a new label and add to parent
    g2Label* NewLabel = new g2Label(RootController, &MainTheme);
    NewLabel->SetPos(x, y);
    NewLabel->SetText(Text);
    
    return NewLabel;
}

g2CheckBox* Glui2::AddCheckBox(int x, int y, const char* Text)
{
    // Allocate a new checkbox and add to parent
    g2CheckBox* NewCheckBox = new g2CheckBox(RootController, &MainTheme);
    NewCheckBox->SetPos(x, y);
    
    return NewCheckBox;
}

void Glui2::Render()
{
    // Go into temporary 2D mode
    glPushMatrix();
    
    // Turn into 2D projection
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0, WindowWidth, WindowHeight, 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    // Make sure we are in fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Update all children
    RootController->__Render();
    
    // End 2D mode
    glPopMatrix();
}

void Glui2::Update()
{
    // Start highres clock and default initial time
	static g2Clock Clock;
	static float dT = 0.0f;
    
    // Render the root, thus rendering all GUI elements
    RootController->__Update(dT);
    
    // End external time
	Clock.Stop();
    dT = Clock.GetTime();
    Clock.Start();
}

void Glui2::__IdleFunc()
{
    // Idle self
    __G2_HANDLE__->Update();
    
    // Idle host
    if(__G2_HANDLE__->GlutIdleFunc != NULL)
        __G2_HANDLE__->GlutIdleFunc();
}

void Glui2::__ReshapeFunc(int width, int height)
{
    // Save new size
    __G2_HANDLE__->WindowWidth = width;
    __G2_HANDLE__->WindowHeight = height;
    
    // Reshape self
    __G2_HANDLE__->RootController->__WindowResizeEvent(width, height);
    
    // Reshape host
    if(__G2_HANDLE__->GlutReshapeFunc != NULL)
        __G2_HANDLE__->GlutReshapeFunc(width, height);
}

void Glui2::__KeyboardFunc(unsigned char key, int x, int y)
{
    // Keyboard self
    __G2_HANDLE__->RootController->__KeyEvent(key);
    
    // Keyboard host
    if(__G2_HANDLE__->GlutKeyboardFunc != NULL)
        __G2_HANDLE__->GlutKeyboardFunc(key, x, y);
}

void Glui2::__SpecialFunc(int key, int x, int y)
{
    // Special Keyboard self
    __G2_HANDLE__->RootController->__KeyEvent(key);
    
    // Special Keyboard host
    if(__G2_HANDLE__->GlutSpecialFunc != NULL)
        __G2_HANDLE__->GlutSpecialFunc(key, x, y);
}

void Glui2::__MouseFunc(int button, int state, int x, int y)
{
    // Mouse self
    __G2_HANDLE__->RootController->__MouseClick(g2MouseButton(button), g2MouseClick(state), x, y);
    
    // Mouse host
    if(__G2_HANDLE__->GlutMouseFunc != NULL)
        __G2_HANDLE__->GlutMouseFunc(button, state, x, y);
}

void Glui2::__HoverFunc(int x, int y)
{
    // Mouse self
    __G2_HANDLE__->RootController->__MouseHover(x, y);
    
    // Mouse host
    if(__G2_HANDLE__->GlutMouseFunc != NULL)
        __G2_HANDLE__->GlutHoverFunc(x, y);
}

void Glui2::__DragFunc(int x, int y)
{
    // Drag self
    __G2_HANDLE__->RootController->__MouseDrag(x, y);
    
    // Mouse host
    if(__G2_HANDLE__->GlutDragFunc != NULL)
        __G2_HANDLE__->GlutDragFunc(x, y);
}
