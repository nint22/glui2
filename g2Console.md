## About ##

_[g2Console Header File](http://code.google.com/p/glui2/source/browse/trunk/Glui2/g2Console.h)_

A debugging console, much like a standard I/O console; derives from [g2Controller](g2Controller.md). The on-screen text is rendered by using g2Controller character-rendering function members. The input is very similar to that of a [g2TextField](g2TextField.md).

## Factory Method ##

```
g2Console* AddConsole()
```

_AddConsole_ will internally allocate and manage a newly created g2Console. The console factory method does not take any arguments as none are needed; the console is purely a string input / output manager, similar to a debugging console.

## Function Members ##

```
void printf(const char* format, ...)
```
Print to the buffer

```
char* gets()
```
Read off the latest string command the user as typed in based on FIFO order. May return null if there is nothing in the buffer. Note that the returned buffer MUST be released when you are done with it.

```
bool InController(int x, int y)
```
Define controller geometry

## Notes ##

It may be easier to use the g2Console in an application than command-line as a tool for debugging at run-time. Any input given or output received from the console is redirected to the standard input / output streams.