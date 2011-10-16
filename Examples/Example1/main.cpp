/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: main.cpp/h for Example1
 Desc: The most basic GLUI2 example that creates an OpenGL
 context (Window, handles, etc.) and then creates a few sample
 controllers.
 
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
    glutCreateWindow("Glui2 Example 1");
    
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
    
    // Place a single button in the middle (Small offset to center)
    g2Button* MyButton = GluiHandle->AddButton(WindowWidth / 2 - 50, WindowHeight / 2, "Hello, World!");
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
