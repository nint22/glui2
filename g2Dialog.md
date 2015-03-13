![http://www.cores2.com/files/Glui2/g2Dialog.png](http://www.cores2.com/files/Glui2/g2Dialog.png)

## About ##

_[g2Dialog Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Dialog.h)_

A wrapper for the host operating system's generic dialog / open / save modal windows. For Win32 g2Dialog uses "MessageBox(...)", for OSX it uses "CreateStandardAlert(...)", but for Linux/Unix it uses the command line (simply because there are too many window managers to program against in Linux). Note that we are opening a [modal window](http://en.wikipedia.org/wiki/Modal_window) that will halt the calling thread.

## Factory Method ##

```
g2Dialog* AddDialog(g2DialogType Type, const char* Message = NULL)
```

_AddDialog_ will internally allocate and manage a newly created g2Dialog. The given type can either be g2DialogType\_Open (for an open-file dialog), g2DialogType\_Save (for a safe-file dialog), or g2DialogType\_Notification (for a modal window notification / pop-up). The "Message" argument is a c-string for the modal window's title.

## Function Members ##

```
void Show()
```
Make appear the modal window of the g2DialogType as set in the factory method. This will halt the calling thread until the user makes a decision.

```
g2DialogResult GetInput(char** result = NULL)
```
Returns the user's choice as well as posts a result string of the user's selection. If the result is a save or open event, and the given result reference pointer is not null then the given pointer is allocated a buffer of the user's file selection location and must be deleted explicitly by the caller.

## Notes ##

As mentioned above, these calls are operating-system specific and thus may apear differently on different systems. Creating a glui2 file browser is out of the scope of this project.