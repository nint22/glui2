/***************************************************************
 
 GLUI 2 - OpenGL User Interface Library 2
 Copyright 2011 Core S2 - See License.txt for details
 
 This source file is developed and maintained by:
 + Jeremy Bridon jbridon@cores2.com
 
***************************************************************/

// All of this should only compile if we are in OSX
#ifdef __APPLE__

//#import <AppKit/AppKit.h>

void __g2ShowDialog()
{
    /*
    // All based on Jorge Arimany Espanque's example code
    // Link: http://jorgearimany.blogspot.com/2010/05/messagebox-from-windows-to-mac.html
    
    // Create core foundation strings
    CFStringRef header_ref = CFStringCreateWithCString( NULL, "Header message", kCFStringEncodingASCII);
    CFStringRef message_ref = CFStringCreateWithCString( NULL, "Actual message...", kCFStringEncodingASCII);
    
    // Catch the result of the alert
    CFOptionFlags result;
    
    // Present the notification
    // See full doc at http://developer.apple.com/library/mac/#documentation/
    // CoreFoundation/Reference/CFUserNotificationRef/Reference/reference.html
    CFUserNotificationDisplayAlert(0, kCFUserNotificationNoteAlertLevel, NULL, NULL, NULL, header_ref, message_ref, NULL, CFSTR("Cancel"), NULL, &result);
    
    // Release the strings
    CFRelease(header_ref);
    CFRelease(message_ref);
    
    // Save the result..
    //if( result == kCFUserNotificationDefaultResponse )
     */
}

void __g2ShowSaveDialog()
{
    /*
    NSOpenPanel *opanel = [NSOpenPanel openPanel];
    [opanel setAllowsMultipleSelection:NO];
    int returnCode = [opanel runModalForDirectory:nil file:nil types:nil];
    
    if(returnCode == NSOKButton)
    {
        NSArray *filenames = [opanel filenames];
        NSString *file = [filenames objectAtIndex:0];
    }
     */
}

void __g2ShowOpenDialog()
{
    
}

// End of apple guard
#endif
