/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: main.cpp/h for Example6
 Desc: Example that implements a g2Panel.
 
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
const int WindowWidth = 800;
const int WindowHeight = 600;

// Global Glui2 Handle
Glui2* GluiHandle = NULL;

// Global g2Panel Handle
g2Panel* MainPanel = NULL;

/*** Global Functions ***/

// Main render function
void Render()
{
    // Clear the back buffer (nice light blue color)
    glClearColor(0.92f, 0.94f, 0.97f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // Nothing special to do...
    // ...
    // ...
    
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

// Callback to any radio-button change
void AnchorTypeChanged(g2Controller* Caller)
{
    // Get the user's choise [bottom, left, top, right]
    // We know the caller will be a radio group
    int Choice = ((g2RadioGroup*)Caller)->GetSelectionIndex();
    if(Choice == 0)
    {
        MainPanel->SetAlignment(g2Anchor_None);
        MainPanel->SetTitle("g2Anchor_None");
        
        MainPanel->SetPos(WindowWidth / 2 - 100, WindowHeight / 2 + 30);
        MainPanel->SetSize(200, 128);
    }
    else if(Choice == 1)
    {
        MainPanel->SetAlignment(g2Anchor_Bottom);
        MainPanel->SetTitle("g2Anchor_Bottom");
    }
    else if(Choice == 2)
    {
        MainPanel->SetAlignment(g2Anchor_Left);
        MainPanel->SetTitle("g2Anchor_Left");
    }
    else if(Choice == 3)
    {
        MainPanel->SetAlignment(g2Anchor_Top);
        MainPanel->SetTitle("g2Anchor_Top");
    }
    else if(Choice == 4)
    {
        MainPanel->SetAlignment(g2Anchor_Right);
        MainPanel->SetTitle("g2Anchor_Right");
    }
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
    glutCreateWindow("Glui2 Example 5");
    
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
    
    /** Build a few sample Panel **/
    
    // Allocate a panel to play with
    MainPanel = GluiHandle->AddPanel(g2Anchor_Bottom, "g2Anchor_Bottom");
    
    // Create a radio group
    const char* Options[5];
    Options[0] = "1. g2Anchor_None";
    Options[1] = "2. g2Anchor_Bottom";
    Options[2] = "3. g2Anchor_Left";
    Options[3] = "4. g2Anchor_Top";
    Options[4] = "5. g2Anchor_Right";
    
    // Add a radio button group (5 radio options) to show panel placement
    g2RadioGroup* SampleRadioGroup = MainPanel->AddRadioGroup(10, 18, Options, 5, AnchorTypeChanged);
    SampleRadioGroup->SetSelectionIndex(1);
    
    /*** Quit Button ***/
    
    g2Button* QuitButton = GluiHandle->AddButton(0, 0, "   Quit Demo   ", Quit);
    QuitButton->SetAlignment(g2Anchor_Center);
    QuitButton->SetPos(WindowWidth / 2 - QuitButton->GetWidth() / 2, WindowHeight / 2);
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
