/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: main.cpp/h for Example3
 Desc: A single OpenGL GLUT window that renders all Glui2
 elements (12) and features ranging from the simple g2Button
 to the more complex open / close file operations.
 
***************************************************************/

/*** Includes Section ***/

// Standard includes
#include <stdio.h>
#include <Glui2/glui2.h>

// Operating system specific glut include
#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

/*** Global Variables ***/

// Window size
const int WindowWidth = 600;
const int WindowHeight = 600;

// Global Glui2 Handle
Glui2* GluiHandle = NULL;

// Global console access
g2Console* Console;

// Global label and value to print the result from the g2Slider
g2Label* SliderValue = NULL;
float GlobalFloat = 0.5f;

// Globel slider to change the progress bar
g2Slider* ProgressBarSlider = NULL;
g2ProgressBar* SampleProgressBar = NULL;

/*** Global Functions ***/

// Main render function
void Render()
{
    // Clear the back buffer (nice light blue color)
    glClearColor(0.92f, 0.94f, 0.97f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // Custom rendering code here...
    // ...
    // Left empty on purpose
    // ...
    
    // Update slider label with it's latest value
    char Buffer[256];
    sprintf(Buffer, "(%.2f)", GlobalFloat);
    SliderValue->SetText(Buffer);
    
    // Update the progress bar with the slider's latest value
    SampleProgressBar->SetProgress(ProgressBarSlider->GetProgress());
    
    // Explicitly call the Glui2 render last
    GluiHandle->Render();
    
    // Flush / force a render, and swap back/front buffers
    glFlush();
    glutSwapBuffers();
    
	// Tell GLUT we want to re-render afterwards
	glutPostRedisplay();
}

// Rescale the viewport as needed
void Reshape(int NewWidth, int NewHeight)
{
	// Apply needed glut viewport updates
	glViewport(0, 0, NewWidth, NewHeight);
}

// Callback to the application
void Quit(g2Controller* Caller)
{
    exit(0);
}

/*** Callback for g2Dialog examples ***/

void DialogShow(g2Controller* Caller)
{
    g2Dialog Dialog(g2DialogType_Notification, "Hello, World!");
    Dialog.Show();
    printf("User's result: %d\n", (int)Dialog.GetInput());
}

void DialogOpen(g2Controller* Caller)
{
	// Open any file
    g2Dialog Dialog(g2DialogType_Open, "Open File...");
    Dialog.Show();
    
    // Get user's results
    char* String;
    int Result = (int)Dialog.GetInput(&String);
    printf("User's open-dialog result: %d (message: \"%s\")\n", Result, String);
    delete[] String;
}

void DialogSave(g2Controller* Caller)
{
	// Save only text files (for the demo)
    g2Dialog Dialog(g2DialogType_Save, "Save File...", "txt");
    Dialog.Show();
    
    // Get user's results
    char* String;
    int Result = (int)Dialog.GetInput(&String);
    printf("User's close-dialog result: %d (message: \"%s\")\n", Result, String);
    delete[] String;
}

/*** Console Toggle ***/

void ToggleConsole(g2Controller* Caller)
{
    // Flip the visability
    Console->SetVisibility(!Console->GetVisibility());
}

/*** Main and Init Functions ***/

// Initialize OpenGL's GLUT
void InitGLUT(int argc, char** argv)
{
    // Initialize glut
	glutInit(&argc, argv);
	
	// Double buffer w/ RGBA colors and z-depth turned on
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	
	// Center the window
	int SystemResWidth = glutGet(GLUT_SCREEN_WIDTH);
	int SystemResHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition(SystemResWidth / 2 - WindowWidth / 2, SystemResHeight / 2 - WindowHeight / 2);
	
	// Set the window size
	glutInitWindowSize(WindowWidth, WindowHeight);
    
    // Create the window
    glutCreateWindow("Glui2 Example 3");
    
    // Turn on alpha blending for textures
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Initialize Glui2 library
void InitGlui2()
{
    // Create a glui instance and register necessary handles
    GluiHandle = new Glui2("g2Blue.cfg", NULL, Reshape);
    glutDisplayFunc(Render);
    
    // Generate all the example GUI elements
    // Note that some of these need supporting buttons
    // to enable / test each individual feature
    g2Label* ComponentTitle = NULL;
    
    /*** g2Label ***/
    ComponentTitle = GluiHandle->AddLabel(20, 10, "g2Label");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    g2Label* SampleLabel = GluiHandle->AddLabel(20, 32, "This is\na sample\nlabel \x01");
    SampleLabel->SetColor(0.9f, 0.0f, 0.0f);
    
    /** g2Button ***/
    ComponentTitle = GluiHandle->AddLabel(150, 10, "g2Button");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    g2Button* SampleButton = NULL;
    
    SampleButton = GluiHandle->AddButton(150, 32, "Button!");
    SampleButton->SetWidth(100);
    SampleButton->SetAlignment(g2Anchor_Center);
    
    SampleButton = GluiHandle->AddButton(150, 52, "Colorized!");
    SampleButton->SetColor(1.0f, 0.6f, 0.2f);
    SampleButton->SetWidth(100);
    SampleButton->SetAlignment(g2Anchor_Center);
    
    SampleButton = GluiHandle->AddButton(150, 72, "Disabled!!");
    SampleButton->SetDisabled(true);
    SampleButton->SetWidth(100);
    SampleButton->SetAlignment(g2Anchor_Center);
    
    SampleButton = GluiHandle->AddButton(135, 92, "Left Anchor");
    SampleButton->SetWidth(130);
    SampleButton->SetAlignment(g2Anchor_Left);
    
    SampleButton = GluiHandle->AddButton(135, 112, "Right Anchor");
    SampleButton->SetWidth(130);
    SampleButton->SetAlignment(g2Anchor_Right);
    
    /*** g2TextBox ***/
    ComponentTitle = GluiHandle->AddLabel(280, 10, "g2Dialog");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddButton(280, 30, "Test Dialog", DialogShow);
    GluiHandle->AddButton(280, 60, "1. Open File... ", DialogOpen);
    GluiHandle->AddButton(280, 80, "2. Save File... ", DialogSave);
    
    /*** g2TextField ***/
    ComponentTitle = GluiHandle->AddLabel(410, 10, "g2TextField");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddTextField(415, 30, "User Name")->SetWidth(150);
    GluiHandle->AddTextField(415, 55, "Password...")->SetWidth(150);
    
    g2TextField* SampleTextField = GluiHandle->AddTextField(415, 80, "Disabled Field");
    SampleTextField->SetWidth(150);
    SampleTextField->SetDisabled(true);
    
    /*** g2Console ***/
    ComponentTitle = GluiHandle->AddLabel(20, 210, "g2Console");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    // Allocate the console and default invisible
    Console = GluiHandle->AddConsole();
    Console->SetVisibility(false);
    
    // Note that we register the callback to toggle the console
    GluiHandle->AddButton(20, 230, "Toggle console", ToggleConsole);
    
    /*** g2Spinner ***/
    ComponentTitle = GluiHandle->AddLabel(150, 210, "g2Spinner");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddSpinner(150, 230, g2SpinnerType_Int)->SetWidth(100);
    
    g2Spinner* SampleSpinner = GluiHandle->AddSpinner(150, 255, g2SpinnerType_Float);
    SampleSpinner->SetBounds(-1.0f, 1.0f);
    SampleSpinner->SetIncrement(0.01f);
    SampleSpinner->SetWidth(100);
    
    /*** g2DropDown ***/
    ComponentTitle = GluiHandle->AddLabel(280, 210, "g2DropDown");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    const char* Options[3];
    Options[0] = "1. Banana";
    Options[1] = "2. Apple";
    Options[2] = "3. Orange";
    
    g2DropDown* SampleDropDown = GluiHandle->AddDropDown(280, 230, Options, 3);
    SampleDropDown->SetWidth(100);
    
    /*** g2ProgressBar ***/
    ComponentTitle = GluiHandle->AddLabel(410, 210, "g2ProgressBar");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    SampleProgressBar = GluiHandle->AddProgressBar(410, 240);
    SampleProgressBar->SetWidth(150);
    SampleProgressBar->SetProgress(0.5f);
    SampleProgressBar->SetText("Progress bar...");
    
    // Bind a global slider, so that the progress bar can be changed in the demo
    ProgressBarSlider = GluiHandle->AddSlider(410, 270);
    ProgressBarSlider->SetWidth(150);
    
    /*** g2RadioGroup ***/
    ComponentTitle = GluiHandle->AddLabel(20, 410, "g2RadioGroup");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    Options[0] = "1. Hello";
    Options[1] = "2. Red";
    Options[2] = "3. Phone";
    GluiHandle->AddRadioGroup(20, 430, Options, 3);
    
    /*** g2CheckBox ***/
    ComponentTitle = GluiHandle->AddLabel(150, 410, "g2CheckBox");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddCheckBox(150, 430, "1. Goodbye");
    GluiHandle->AddCheckBox(150, 445, "2. Green");
    GluiHandle->AddCheckBox(150, 460, "3. Drone");
    GluiHandle->AddCheckBox(150, 475, "4. Alpha");
    GluiHandle->AddCheckBox(150, 490, "5. Example");
    
    /*** g2Slider ***/
    ComponentTitle = GluiHandle->AddLabel(280, 410, "g2Slider:");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    g2Slider* SampleSlider = GluiHandle->AddSlider(280, 430, NULL, &GlobalFloat);
    SampleSlider->SetWidth(100);
    
    SliderValue = GluiHandle->AddLabel(345, 410, "(0.5)");
    SliderValue->SetColor(0, 0, 0);
    
    /*** g2Panel ***/
    ComponentTitle = GluiHandle->AddLabel(410, 410, "g2Panel");
    ComponentTitle->SetColor(0.0f, 0.0f, 0.0f);
    
    g2Panel* SamplePanel = GluiHandle->AddPanel(g2Anchor_None);
    SamplePanel->SetPos(410, 430);
    SamplePanel->SetSize(64, 64);
    
    /*** Quit Button ***/
    g2Button* ExitButton = GluiHandle->AddButton(WindowWidth / 2 - 50, WindowHeight - 40, "   Quit Demo", Quit);
    ExitButton->SetWidth(100);
    ExitButton->SetIcon("icon_quit");
}

/*** Main Application Entry Point ***/

int main(int argc, char** argv)
{
    // Initialize OpenGL / GLUT
    InitGLUT(argc, argv);
    
    // Initialize Glui2
    InitGlui2();
    
    // Start the main rendering loop
    glutMainLoop();
    
    // Suppress warning
    return 0;
}
