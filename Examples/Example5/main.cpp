/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: main.cpp/h for Example5
 Desc: A real-world application example. Includes live-variable
 examples and call-back functions.
 
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

// Rendering state
// 0 - Points, 1 - Lines, 2 - Flat surface
g2DropDown* StyleController = NULL;

// Distance (0) and pitch, yaw (1, 2)
g2Spinner* PositionSliders[3];
g2Label* PositionLabels[3];

// Distance, pitch, yaw
float Distance = 0, Pitch = 0, Yaw = 0;

// Sliders and labels for colors (R, G, B)
g2Slider* ColorSliders[3];
g2Label* ColorLabels[3];

/*** Global Functions ***/

// Main render function
void Render()
{
    // Clear the back buffer (nice light blue color)
    glClearColor(0.92f, 0.94f, 0.97f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // Prepare for 3D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, float(WindowWidth) / float(WindowHeight), 1.0f, 1000.0f);		
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH);
    
    // Set line and point size
    glPointSize(3.0f);
    
    // Update the distance / pitch / yaw
    Distance = PositionSliders[0]->GetFloat();
    Pitch = PositionSliders[1]->GetFloat();
    Yaw = PositionSliders[2]->GetFloat();
    
    // Push for local transformations
    glPushMatrix();
        
        // Change position as needed
        gluLookAt(-10.0f * Distance, 4.0f * Distance, -5.0f * Distance, 0, 0, 0, 0, 1, 0);
        glRotatef(Pitch, 1, 0, 0);
        glRotatef(Yaw, 0, 1, 0);
        
        // Set color and draw
        glColor3f(ColorSliders[0]->GetProgress(), ColorSliders[1]->GetProgress(), ColorSliders[2]->GetProgress());
        
        // Change rendering styles as needed...
        if(StyleController->GetSelectionIndex() == 0)
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        else if(StyleController->GetSelectionIndex() == 1)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        // Render torus
        glutSolidTorus(0.2, 1.0, 6, 12);
        
    glPopMatrix();
    
    // Update the color labels
    for(int i = 0; i < 3; i++)
    {
        // Create a text buffer to place the fraction in it
        // Note the embedded ternary-comparison order, pretty awesome
        char Buffer[256];
        sprintf(Buffer, "Color %c: %.2f%%", (i == 0 ? 'R' : (i == 1 ? 'G' : 'B')), ColorSliders[i]->GetProgress() * 100.0f);
        ColorLabels[i]->SetText(Buffer);
    }
    
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
    GluiHandle = new Glui2("g2Default.cfg", NULL, Reshape);
    glutDisplayFunc(Render);
    
    /*** Color Sliders & Labels ***/
    for(int i = 0; i < 3; i++)
    {
        // Allocate, set position, and width
        ColorSliders[i] = GluiHandle->AddSlider(20, 520 + i * 25);
        ColorSliders[i]->SetWidth(170);
        
        ColorLabels[i] = GluiHandle->AddLabel(200, 518 + i * 25, "Color R/G/B");
        ColorLabels[i]->SetColor(0, 0, 0);
    }
    
    /*** Rendering Style ***/
    const char* RenderingOptions[3];
    RenderingOptions[0] = "1. Point-rendering";
    RenderingOptions[1] = "2. Line-rendering";
    RenderingOptions[2] = "3. Surface-rendering";
    
    StyleController = GluiHandle->AddDropDown(WindowWidth / 2 - 75, WindowHeight - 80, RenderingOptions, 3);
    StyleController->SetWidth(175);
    
    /*** Color Sliders & Labels ***/
    for(int i = 0; i < 3; i++)
    {
        // Allocate, set position, and width
        PositionSliders[i] = GluiHandle->AddSpinner(530, 510 + i * 25, g2SpinnerType_Float);
        PositionSliders[i]->SetWidth(80);
        
        // Set the resolution of the movement rotations
        if(i == 0)
        {
            PositionSliders[i]->SetFloat(1.0f);
            PositionSliders[i]->SetIncrement(0.05f);
        }
        else
            PositionSliders[i]->SetIncrement(5.0f);
        
        // Set position / rotation
        if(i == 0)
            PositionLabels[i] = GluiHandle->AddLabel(622, 515 + i * 25, "Distance");
        else if(i ==1)
            PositionLabels[i] = GluiHandle->AddLabel(622, 515 + i * 25, "Pitch");
        else
            PositionLabels[i] = GluiHandle->AddLabel(622, 515 + i * 25, "Yaw");
        PositionLabels[i]->SetColor(0, 0, 0);
    }
    
    /*** Quit Button ***/
    GluiHandle->AddButton(WindowWidth / 2 - 50, WindowHeight - 100, "   Quit Demo   ", Quit);
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
