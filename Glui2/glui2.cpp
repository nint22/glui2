/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
***************************************************************/

#include "glui2.h"

Glui2::Glui2(const char* ThemeFile, void (*GlutIdleFunc)(void), void (*GlutReshapeFunc)(int width, int height), void (*GlutKeyboardFunc)(unsigned char key, int x, int y), void (*GlutSpecialFunc)(int key, int x, int y), void (*GlutMouseFunc)(int button, int state, int x, int y), void (*GlutHoverFunc)(int x, int y))
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
    glutMotionFunc(__HoverFunc); // Paired with above
    glutMouseFunc(__MouseFunc);
    
    // Attempt to load given theme file if not null
    if(ThemeFile == NULL)
        MainTheme.Load(__G2_DEFAULT_THEME__);
    else
        MainTheme.Load(ThemeFile);
    
    // Default root to have no ownership and active controller to none
    RootController = new g2Controller(NULL, &MainTheme);
    ActiveController = NULL;
    ActiveConsole = NULL;
}

Glui2::~Glui2()
{
    // Nothing to release
}

g2Button* Glui2::AddButton(int x, int y, const char* Label, __g2CallBack(callback))
{
    g2Button* NewButton = new g2Button(RootController, &MainTheme);
    NewButton->SetPos(x, y);
    NewButton->SetText(Label);
    NewButton->__WindowResizeEvent(WindowWidth, WindowHeight);
    NewButton->SetCallback(callback);
    return NewButton;
}

g2Label* Glui2::AddLabel(int x, int y, const char* Text)
{
    g2Label* NewLabel = new g2Label(RootController, &MainTheme);
    NewLabel->SetPos(x, y);
    NewLabel->SetText(Text);
    NewLabel->__WindowResizeEvent(WindowWidth, WindowHeight);
    return NewLabel;
}

g2CheckBox* Glui2::AddCheckBox(int x, int y, const char* Text, __g2CallBack(callback), bool* LiveCheckState)
{
    g2CheckBox* NewCheckBox = new g2CheckBox(RootController, &MainTheme);
    NewCheckBox->SetPos(x, y);
    NewCheckBox->GetLabel()->SetText(Text);
    NewCheckBox->__WindowResizeEvent(WindowWidth, WindowHeight);
    NewCheckBox->SetCallback(callback);
    NewCheckBox->SetLiveVariable(LiveCheckState);
    return NewCheckBox;
}

g2Console* Glui2::AddConsole()
{
    ActiveConsole = new g2Console(RootController, &MainTheme);
    ActiveConsole->__WindowResizeEvent(WindowWidth, WindowHeight);
    return ActiveConsole;
}

g2TextField* Glui2::AddTextField(int x, int y, const char* Text)
{
    g2TextField* NewTextField = new g2TextField(RootController, &MainTheme);
    NewTextField->SetPos(x, y);
    NewTextField->SetText(Text);
    NewTextField->__WindowResizeEvent(WindowWidth, WindowHeight);
    return NewTextField;
}

g2RadioGroup* Glui2::AddRadioGroup(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback), int* LiveIndex)
{
    g2RadioGroup* NewRadioGroup = new g2RadioGroup(RootController, &MainTheme);
    NewRadioGroup->SetOptions(Options, OptionCount);
    NewRadioGroup->SetPos(x, y);
    NewRadioGroup->__WindowResizeEvent(WindowWidth, WindowHeight);
    NewRadioGroup->SetCallback(callback);
    NewRadioGroup->SetLiveVariable(LiveIndex);
    return NewRadioGroup;
}

g2DropDown* Glui2::AddDropDown(int x, int y, const char** Options, int OptionCount, __g2CallBack(callback), int* LiveIndex)
{
    g2DropDown* NewDropDown = new g2DropDown(RootController, &MainTheme);
    NewDropDown->SetPos(x, y);
    NewDropDown->__WindowResizeEvent(WindowWidth, WindowHeight);
    NewDropDown->SetOptions(Options, OptionCount);
    NewDropDown->SetCallback(callback);
    NewDropDown->SetLiveVariable(LiveIndex);
    return NewDropDown;
}

g2Dialog* Glui2::AddDialog(g2DialogType Type, const char* Message)
{
    g2Dialog* NewDialog = new g2Dialog(Type, Message);
    return NewDialog;
}

g2Panel* Glui2::AddPanel(g2Anchor AnchorFlags, const char* Title)
{
    g2Panel* NewPanel = new g2Panel(RootController, &MainTheme, AnchorFlags, Title);
    NewPanel->__WindowResizeEvent(WindowWidth, WindowHeight);
    return NewPanel;
}

g2Slider* Glui2::AddSlider(int x, int y, __g2CallBack(callback), float* LiveValue)
{
    g2Slider* NewSlider = new g2Slider(RootController, &MainTheme);
    NewSlider->SetPos(x, y);
    NewSlider->__WindowResizeEvent(WindowWidth, WindowHeight);
    NewSlider->SetCallback(callback);
    NewSlider->SetLiveVariable(LiveValue);
    return NewSlider;
}

g2ProgressBar* Glui2::AddProgressBar(int x, int y)
{
    g2ProgressBar* NewProgress = new g2ProgressBar(RootController, &MainTheme);
    NewProgress->SetPos(x, y);
    NewProgress->__WindowResizeEvent(WindowWidth, WindowHeight);
    return NewProgress;
}

g2Spinner* Glui2::AddSpinner(int x, int y, g2SpinnerType Type, __g2CallBack(callback), float* LiveValue)
{
    g2Spinner* NewSpinner = new g2Spinner(RootController, &MainTheme, Type);
    NewSpinner->SetPos(x, y);
    NewSpinner->__WindowResizeEvent(WindowWidth, WindowHeight);
    NewSpinner->SetCallback(callback);
    NewSpinner->SetLiveVariable(LiveValue);
    return NewSpinner;
}

g2Controller* Glui2::GetRootController()
{
    return RootController;
}

g2Theme* Glui2::GetMainTheme()
{
    return &MainTheme;
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
    
    // Render all children (this controller is the root of all controllers)
    RootController->__Render(0, 0);
    
    // Render the console LAST
    if(ActiveConsole != NULL)
        ActiveConsole->__Render(0, 0);
    
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
    
    // Update the console LAST
    if(ActiveConsole != NULL)
        ActiveConsole->__Update(dT);
    
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
    
    // Update the console LAST
    if(__G2_HANDLE__->ActiveConsole != NULL)
        __G2_HANDLE__->ActiveConsole->__WindowResizeEvent(width, height);
    
    // Reshape host
    if(__G2_HANDLE__->GlutReshapeFunc != NULL)
        __G2_HANDLE__->GlutReshapeFunc(width, height);
}

void Glui2::__KeyboardFunc(unsigned char key, int x, int y)
{
    // Update console if allocated and not disabled
    if(__G2_HANDLE__->ActiveConsole != NULL && __G2_HANDLE__->ActiveConsole->GetVisibility())
        __G2_HANDLE__->ActiveConsole->__KeyEvent(key);
    
    // Else, pass to active controller if active
    else if(__G2_HANDLE__->ActiveController != NULL)
        __G2_HANDLE__->ActiveController->__KeyEvent(key);
    
    // If nothing is focused, pass to glut
    else if(__G2_HANDLE__->GlutKeyboardFunc != NULL)
        __G2_HANDLE__->GlutKeyboardFunc(key, x, y);
}

void Glui2::__SpecialFunc(int key, int x, int y)
{
    // Update console if allocated and not disabled
    if(__G2_HANDLE__->ActiveConsole != NULL && __G2_HANDLE__->ActiveConsole->GetVisibility())
        __G2_HANDLE__->ActiveConsole->__KeyEvent(key, true);
    
    // Else, pass to active controller if active
    else if(__G2_HANDLE__->ActiveController != NULL)
        __G2_HANDLE__->ActiveController->__KeyEvent(key, true);
    
    // If nothing is focused, pass to glut
    else if(__G2_HANDLE__->GlutSpecialFunc != NULL)
        __G2_HANDLE__->GlutSpecialFunc(key, x, y);
}

void Glui2::__MouseFunc(int button, int state, int x, int y)
{
    // Ignore if  console if allocated and not disabled
    if(__G2_HANDLE__->ActiveConsole != NULL && __G2_HANDLE__->ActiveConsole->GetVisibility())
        return;
    
    // Mouse self
    __G2_HANDLE__->RootController->__MouseClick(g2MouseButton(button), g2MouseClick(state), x, y);
    
    // Release previous active controller's state
    if(__G2_HANDLE__->ActiveController != NULL)
        __G2_HANDLE__->ActiveController->IsActive = false;
    
    // Get new active controller or set it to the console if it's within bounds
    __G2_HANDLE__->ActiveController = __G2_HANDLE__->RootController->GetController(x, y);
    if(__G2_HANDLE__->ActiveController != NULL)
        __G2_HANDLE__->ActiveController->IsActive = true;
    
    // If nothing is focused, mouse glut
    else if(__G2_HANDLE__->GlutMouseFunc != NULL)
        __G2_HANDLE__->GlutMouseFunc(button, state, x, y);
}

void Glui2::__HoverFunc(int x, int y)
{
    // Ignore if  console if allocated and not disabled
    if(__G2_HANDLE__->ActiveConsole != NULL && __G2_HANDLE__->ActiveConsole->GetVisibility())
        return;
    
    // Mouse self
    __G2_HANDLE__->RootController->__MouseHover(x, y);
    
    // Always pass to glut; any code should read this
    if(__G2_HANDLE__->GlutHoverFunc != NULL)
        __G2_HANDLE__->GlutHoverFunc(x, y);
}
