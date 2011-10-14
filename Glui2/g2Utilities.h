/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
 File: g2Utilities.cpp/h
 Desc: A group of global variables, functions, and structures
 that are commonly used throughout Glui2.
 
***************************************************************/

// Inclusion guard
#ifndef __G2UTILITIES_H__
#define __G2UTILITIES_H__

// Window includes
#ifdef _WIN32
    
    // Suppress std-c lib buffer-overflow warnings
    #pragma warning(disable:4996)
    #include <windows.h>
    #include <gl/glut.h>
    #include <gl/glext.h>
    
    // Windows doesn't implement fmin/fmax, so instead
    // we do a macro-replacement
    #define fmax max
    #define fmin min
    
    // Define shorthand the DLL export macro
    #define __g2EXPORT __declspec(dllexport)
    
// Linux includes
#elif __linux__
    
    #include <GL/glut.h>
    #include <unistd.h>
    #include <execinfo.h>
    #include <sys/time.h>
    #include <stdarg.h>
    #include <limits.h>
    
    // Nothing to define for GCC's library creation
    #define __g2EXPORT

// Apple/OSX includes
#elif __APPLE__

    #include <GLUT/glut.h>
    #include <Carbon/Carbon.h>
    #include <execinfo.h>
    #include <sys/time.h>
    
    // Nothing to define for Apple's library creation
    #define __g2EXPORT

#endif

// Standard includes across all systems
#include <typeinfo>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

// Define the generic call back function type
#define __g2CallBack(function_name) void (*function_name)(g2Controller* Sender)

// Assertion macro to help debug with critical-failure assertions
#define g2Assert(...) __g2Assert(__FILE__, __LINE__, __VA_ARGS__)
__g2EXPORT void __g2Assert(const char* FileName, int LineNumber, bool Assertion, const char* FailText, ...);

/*** Declare helper enumerations of the mouse press states based on GLUT definitions ***/

// Mouse button type (e.g. left or right buttons)
enum g2MouseButton
{
    g2MouseButton_Left = GLUT_LEFT_BUTTON,
    g2MouseButton_Middle = GLUT_MIDDLE_BUTTON,
    g2MouseButton_Right = GLUT_RIGHT_BUTTON,
};

// Mouse click state (e.g. pressed down or released)
enum g2MouseClick
{
    g2MouseClick_Down = GLUT_DOWN,
    g2MouseClick_Up = GLUT_UP,
};

/*** High-resolution clock; used to measure dT between each frame ***/

// Windows version
#if _WIN32

    // High-resolution clock (In fraction of seconds)
    class g2Clock
    {
    public:
        
        __g2EXPORT g2Clock(bool StartTiming = false)
        {
            // Setup the high-resolution timer
            QueryPerformanceFrequency(&TicksPerSec);
            
            // High-resolution timers, initialized timer
            QueryPerformanceCounter(&startTime);
            
            // Start off the timer
            Start(); Stop();
            
            // Star the timer if we want
            if(StartTiming)
                Start();
        }
        
        __g2EXPORT void Stop()
        {
            QueryPerformanceCounter(&endTime);
        }
        
        // In seconds
        __g2EXPORT float GetTime()
        {
            // Measure the cycle time
            cpuTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
            return (float)cpuTime.QuadPart / (float)TicksPerSec.QuadPart;
        }
        
        __g2EXPORT void Start()
        {
            QueryPerformanceCounter(&startTime);
        }
        
    private:
        LARGE_INTEGER TicksPerSec;
        LARGE_INTEGER startTime, endTime, cpuTime;
    };

// UNIX / Linux / OSX interface
#else

    // High-resolution clock (In fraction of seconds)
    class g2Clock
    {
    public:
        
        g2Clock(bool StartTiming = false)
        {
            // High-resolution timers, initialized timer
            gettimeofday(&startTime, NULL);
            
            // Start off the timer
            Start(); Stop();
            
            // Star the timer if we want
            if(StartTiming)
                Start();
        }
        
        void Stop()
        {
            gettimeofday(&endTime, NULL);
        }
        
        float GetTime()
        {
            // Measure the cycle time (Convert from micro to milli to seconds)
            // If the end time is one second more than the start time, modify the
            float secondDif = float(endTime.tv_sec - startTime.tv_sec);
            return float(float(endTime.tv_usec) / 1000.0f - float(startTime.tv_usec) / 1000.0f) / 1000.0f + secondDif;
        }
        
        void Start()
        {
            gettimeofday(&startTime, NULL);
        }
        
    private:
        struct timeval startTime, endTime;
    };

// End of UNIX version
#endif

// End of inclusion guard
#endif
