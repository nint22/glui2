/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: main.cpp/h for Example4
 Desc: A simple GLUI2 example that demonstrates how to create
 a custom control, which in this case is a bubble widget.
 
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

// Include our custom controller
#include "g2Bubble.h"

/*** Global Variables ***/

// Window size
const int WindowWidth = 800;
const int WindowHeight = 600;

// Global Glui2 Handle
Glui2* GluiHandle = NULL;

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
    glutCreateWindow("Glui2 Example 4");
    
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
    
    // Put a quit button
    GluiHandle->AddButton(WindowWidth / 2 - 50, WindowHeight - 40, "   Quit Demo   ", Quit);
    
    // Put a bubble on-screen; needs to be allocated and initialized manually
    g2Bubble* MyBubble = new g2Bubble(GluiHandle->GetRootController(), GluiHandle->GetMainTheme());
    MyBubble->SetPos(WindowWidth / 2 - 100, WindowHeight / 2 - 100);
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
