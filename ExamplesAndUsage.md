### Usage ###

The Glui2 library is easy to use, both for new or existed OpenGL code bases. The installation and usage step is split into three steps: Glui2 instantiation, Glut registration, and scene creation.

#### Installation ####

_Windows:_

  1. You will need Visual Studio C++ 2010 and Glui installed
  1. Build the entire solution
  1. Copy headers and the produced **.dll and**.lib into your System32 folder or what works best for you
  1. Examples are built as part of building the solution

_OSX:_

  1. You will need XCode (tested with XCode4)
  1. Open the XCode project in the root directory
  1. Build and install by simply building the project (installation is automatically done, _only debug-mode is currently supported_)
  1. You will have to individually open example projects and build / run them after Glui2 is build and installed

_Linux:_

  1. You will need to have x11 / Xorg, g++, and make installed
  1. cd into the root directory
  1. Run "make" to build the library (sans examples)
  1. Run "make install" to install the library (WARNING: This is a very simplified make file, the default install path is "/user/local/lib")
  1. You will have to move into any of the example directories and manually build them using make to execute each individual example

#### Glui2 Usage ####

During your code's initialization, but _before_ OpenGL's / Glut's initialization, create an instance of the Glui2 library. Depending on your code and design, you may either create the Glui2 object on the stack or heap, though in general you will more likely need to create it on the heap. Remember, when your [Glui2](Glui2.md) handle gets released, so do all it's child objects!

```
#include <Glui2/glui2.h>

// Your code here...

Glui2* GluiHandle = new Glui2();

// OpenGL / GLUT initialization cod here ...

```

Read more on the [Glui2](Glui2.md) class to understand the constructors and expected arguments. Once your handle has been instantiated, use any of the built-in factory methods to allocate a new on-screen object. _Never_ allocate new GUI controllers using their respective constructor unless you are doing so within a controller as a child.

```
// Create a button at position (50, 100) with width [100] and text 
g2Button* MyButton = GluiHandle->AddButton();
MyButton->SetPos(50, 100)
MyButton->SetText("Hello, World!");
MyButton->SetWidth(100);

// The above could be simplified using the factory-method arguments
Button = GluiHandle->AddButton(50, 100, "Hello, World!");
Button->SetWidth(100);
```

Some controllers allow call-backs when the user interacts when them or there is a value change. You can do this either by calling the object's `SetHandle(...)` method or pass it part of the constructor (note that all callback functions have to conform to the function-type "g2CallBack", which is defined as `void (*function_name)(g2Controller* Sender)`). The same is done with live-variables.

```
// Callback function, conforms to "__g2CallBack"
void ButtonPressed(g2Controller* Caller)
{
    printf("The button has been pressed!\n");
}

// Register callback for our button
Button->SetCallback(ButtonPressed);
```

One final step is you install your Glui2's render handle. This is left up to you so that you can manipulate when and where to draw the final GUI output. For most uses, it is best to put the Glui2's "Render()" member-function call at the end of your GLUT render callback.

```

// Render function
void Render()
{
    // This is REQUIRED to call, at least at some point in your render loop
    GluiHandle->Render();
}

// Initialization function:
void Init()
{
    // Initialize Glui2
    GluiHandle = new Glui2();
    
    // Do scene-generation work... (as seen above)
    
    // Bind your display function for GLUT
    glutDisplayFunc(Render);
}

```

Once your controllers have been registered and the render-function is correctly placed, you may start with your GLUT main-loop and thus launch you application!

### Examples ###
The following are descriptions of six examples included in the source of Glui2. You can fine these directories by navigating the root of the project's directory, then going into the "Example" directory, then go into any of the below examples. Each example compiles in either OSX, Windows, or Linux. Please see above on how to compile Glui / individual examples.

#### Example1 ####
The absolute most basic usage of Glui2 with a single button being installed.

#### Example2 ####
Similar to Example1, it demonstrates basic Glui2 usage as well as how to interface with GLUT event handlers that need to be registered with Glui2 first.

#### Example3 ####
Shows on-screen all built-in controller objects. If you would like, you may change the theme file by changing the Glui2 construct's first argument from "g2Default.cfg" to "g2Blue.cfg" or vice-versa.

#### Example4 ####
Implements a custom new GUI controller (pop-up text box) that derives from [g2Controller](g2Controller.md).

#### Example5 ####
Implements a "real-world" example that does 3D rendering of a torus, updated by several controllers.

#### Example6 ####
Shows how g2Panels can be used and how they can be quickly set to an anchor-style using a [g2RadioGroup](g2RadioGroup.md).