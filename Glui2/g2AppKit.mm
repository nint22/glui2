/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

// All of this should only compile if we are in OSX
#ifdef __APPLE__

#include "g2AppKit.h"
#import <AppKit/AppKit.h>

bool __g2ShowDialog(const char* Message)
{
    // All based on Jorge Arimany Espanque's example code
    // Link: http://jorgearimany.blogspot.com/2010/05/messagebox-from-windows-to-mac.html
    
    // Create core foundation strings
    CFStringRef header_ref = CFStringCreateWithCString( NULL, "Notification", kCFStringEncodingASCII);
    CFStringRef message_ref = CFStringCreateWithCString( NULL, Message, kCFStringEncodingASCII);
    
    // Catch the result of the alert
    CFOptionFlags result;
    
    // Present the notification
    // See full doc at http://developer.apple.com/library/mac/#documentation/
    // CoreFoundation/Reference/CFUserNotificationRef/Reference/reference.html
    CFUserNotificationDisplayAlert(0, kCFUserNotificationNoteAlertLevel, NULL, NULL, NULL, header_ref, message_ref, NULL, NULL, NULL, &result);
    
    // Release the strings
    CFRelease(header_ref);
    CFRelease(message_ref);
    
    // Save the result..
    if(result == kCFUserNotificationDefaultResponse)
        return true;
    else
        return false;
}

bool __g2ShowSaveDialog(const char* Message, const char* FileExtension, char* OutBuffer, int OutLength)
{ 
    // Alloc a temporary ObjC memory manager
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    bool result = false;
    
    // Open panel to open file
    NSSavePanel* spanel = [NSSavePanel savePanel];
    [spanel setTitle:[NSString stringWithCString:Message encoding:NSASCIIStringEncoding]];
    [spanel setAllowedFileTypes:[NSArray arrayWithObjects:[NSString stringWithCString:FileExtension encoding:NSASCIIStringEncoding], nil]];
    NSInteger returnCode = [spanel runModal];
    
    if(returnCode == NSOKButton)
    {
        NSURL* filenames = [spanel URL];
        NSString* file = [filenames absoluteString];
        if([file length] < OutLength)
        {
            strcpy(OutBuffer, [file cStringUsingEncoding:NSASCIIStringEncoding]);
            result = true;
        }
    }
    
    // Else, something failed
    [pool drain];
    return result;
}

bool __g2ShowOpenDialog(const char* Message, const char* FileExtension, char* OutBuffer, int OutLength)
{
    // Alloc a temporary ObjC memory manager
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    bool result = false;
    
    // Open panel to open file
    NSOpenPanel* opanel = [NSOpenPanel openPanel];
    [opanel setTitle:[NSString stringWithCString:Message encoding:NSASCIIStringEncoding]];
    [opanel setAllowsMultipleSelection:NO];
    [opanel setAllowedFileTypes:[NSArray arrayWithObjects:[NSString stringWithCString:FileExtension encoding:NSASCIIStringEncoding], nil]];
    NSInteger returnCode = [opanel runModalForDirectory:nil file:nil types:nil];
    
    if(returnCode == NSOKButton)
    {
        NSArray* filenames = [opanel filenames];
        NSString* file = [filenames objectAtIndex:0];
        if([file length] < OutLength)
        {
            strcpy(OutBuffer, [file cStringUsingEncoding:NSASCIIStringEncoding]);
            result = true;
        }
    }
    
    // Else, something failed
    [pool drain];
    return result;
}

// End of apple guard
#endif
