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
#include <Glui2/Glui2.h>

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

// Global label and value to print the result from the g2Slider
g2Label* SliderValue = NULL;
float GlobalFloat = 0.5f;

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
    
    // Update g2Slider-demo label with new value
    char Buffer[256];
    sprintf(Buffer, "(%.2f)", GlobalFloat);
    SliderValue->SetText(Buffer);
    
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
    g2Dialog Dialog(g2DialogType_Save, "Save File...");
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
    // Allocate only one console
    // Would be better to have this as a global, but this is an example
    static bool Visibility = false;
    static g2Console* Console = GluiHandle->AddConsole();
    
    // Flip visibility
    Visibility = !Visibility;
    Console->SetVisibility(Visibility);
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
    // Create a glui instance and register neccesary handles
    GluiHandle = new Glui2("g2Default.cfg", NULL, Reshape);
    glutDisplayFunc(Render);
    
    // Generate all the example GUI elements
    // Note that some of these need supporting buttons
    // to enable / test each individual feature
    g2Label* TempLabel = NULL;
    
    /*** g2Label ***/
    TempLabel = GluiHandle->AddLabel(20, 10, "g2Label");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    g2Label* SampleLabel = GluiHandle->AddLabel(20, 32, "This is\na sample\nlabel \x01");
    SampleLabel->SetColor(0.9f, 0.0f, 0.0f);
    
    /** g2Button ***/
    TempLabel = GluiHandle->AddLabel(150, 10, "g2Button");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddButton(150, 32, "  Button! ");
    g2Button* SampleButton = GluiHandle->AddButton(150, 52, "Colorized!");
    SampleButton->SetColor(1.0f, 0.6f, 0.2f);
    SampleButton = GluiHandle->AddButton(150, 72, "Disabled!!");
    SampleButton->SetDisabled(true);
    
    /*** g2TextBox ***/
    TempLabel = GluiHandle->AddLabel(280, 10, "g2Dialog");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddButton(280, 30, "Test Dialog", DialogShow);
    GluiHandle->AddButton(280, 60, "1. Open File... ", DialogOpen);
    GluiHandle->AddButton(280, 80, "2. Save File... ", DialogSave);
    
    /*** g2TextField ***/
    TempLabel = GluiHandle->AddLabel(410, 10, "g2TextField");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddTextField(415, 30, "User Name")->SetWidth(150);
    GluiHandle->AddTextField(415, 55, "Password...")->SetWidth(150);
    g2TextField* SampleTextField = GluiHandle->AddTextField(415, 80, "Disabled Field");
    SampleTextField->SetWidth(150);
    SampleTextField->SetDisabled(true);
    
    /*** g2Console ***/
    TempLabel = GluiHandle->AddLabel(20, 210, "g2Console");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    // Note that we register the callback to toggle the console
    GluiHandle->AddButton(20, 230, "Toggle console", ToggleConsole);
    
    /*** g2Spinner ***/
    TempLabel = GluiHandle->AddLabel(150, 210, "g2Spinner");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddSpinner(150, 230, g2SpinnerType_Int)->SetWidth(100);
    
    g2Spinner* ExampleSpinner = GluiHandle->AddSpinner(150, 255, g2SpinnerType_Float);
    ExampleSpinner->SetBounds(-1.0f, 1.0f);
    ExampleSpinner->SetIncrement(0.01f);
    ExampleSpinner->SetWidth(100);
    
    /*** g2DropDown ***/
    TempLabel = GluiHandle->AddLabel(280, 210, "g2DropDown");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    g2DropDown* DropDown = GluiHandle->AddDropDown(280, 230);
    DropDown->SetWidth(80);
    //DropDown->AddOptions(Options);
    
    /*** g2ProgressBar ***/
    TempLabel = GluiHandle->AddLabel(410, 210, "g2ProgressBar");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    g2ProgressBar* ExampleProgress = GluiHandle->AddProgressBar(410, 240);
    ExampleProgress->SetWidth(150);
    ExampleProgress->SetProgress(0.25f);
    ExampleProgress->SetText("Progress bar...");
    
    /*** g2RadioGroup ***/
    TempLabel = GluiHandle->AddLabel(20, 410, "g2RadioGroup");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    const char* Options[3];
    Options[0] = "1. Hello";
    Options[1] = "2. Red";
    Options[2] = "3. Phone";
    GluiHandle->AddRadioGroup(20, 430, Options, 3);
    
    /*** g2CheckBox ***/
    TempLabel = GluiHandle->AddLabel(150, 410, "g2CheckBox");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    GluiHandle->AddCheckBox(150, 430, "1. Goobye");
    GluiHandle->AddCheckBox(150, 445, "2. Green");
    GluiHandle->AddCheckBox(150, 460, "3. Drone");
    GluiHandle->AddCheckBox(150, 475, "4. Alpha");
    GluiHandle->AddCheckBox(150, 490, "5. Example");
    
    /*** g2Slider ***/
    TempLabel = GluiHandle->AddLabel(280, 410, "g2Slider:");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    g2Slider* SampleSlider = GluiHandle->AddSlider(280, 430, NULL, &GlobalFloat);
    SampleSlider->SetWidth(100);
    
    SliderValue = GluiHandle->AddLabel(345, 410, "(0.5)");
    SliderValue->SetColor(0, 0, 0);
    
    /*** g2Panel ***/
    TempLabel = GluiHandle->AddLabel(410, 410, "g2Panel");
    TempLabel->SetColor(0.0f, 0.0f, 0.0f);
    
    g2Panel* Panel = GluiHandle->AddPanel(g2Anchor_None);
    Panel->SetPos(410, 430);
    Panel->SetSize(64, 64);
    
    /*** Quit Button ***/
    GluiHandle->AddButton(WindowWidth / 2 - 50, WindowHeight - 40, "   Quit Demo   ", Quit);
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
    
    // Supress warning
    return 0;
}
