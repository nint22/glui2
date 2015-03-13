### About ###

Glui2, an OpenGL User Interface Library, is a light-weight feature-rich stand-alone Graphical User Interface (GUI) for OpenGL and GLUT applications. Written in C/C++, it is clean to use, easy to extend, well documented, and supports Linux, Windows, and OSX, as well as is very small! (Only 7.5k lines of code!)

Glui2, based on the original GLUI library by [Paul Rademacher](http://www.cs.unc.edu/~rademach/glui/), is a full re-write from scratch based on a similar minimalistic design. This project uses similar methods and programing interfaces, but now includes GUI theming, easier integration with applications, better performance (2D hardware acceleration), easier extending of new controllers, full documentation, and a clean implementation in portable C++. Checkout what the project looks like through our [screenshots](Screenshots.md) page!

Why use Glui2 versus all the other hundreds of GUI libraries? One big advantage is that it has a very small code base and interfacing footprint. Unlike wxWidgest or many other libraries, this code is ready to go and easy to use. Object instantiation is easy, there is no complex overhead, or bulky boilerplate code, etc. It truly is ready to go out of the box and extensible!

The project currently builds and executes without any dependencies, other than OpenGL / GLUT, and requires no advanced OpenGL features. Glui2 runs in immediate-mode and only users OpenGL 1.1 standard features!

This library can easily be integrated with existing or new OpenGL applications designed for interactive media, scientific applications, academic usage, and more!

#### Features ####
  * 2D Rendering using OpenGL
  * Fast and efficient code base
  * Written in portable C/C++
  * Copiles on Windows, OSX, and Linux as dynamic library
  * Uses object-oriented programming patterns
  * Uses factory-method object instantiation
  * Child-parent relationships
  * Copy/paste text within and outside of the application
  * On-screen console (with coloring)
  * 12built-in controllers (buttons, check-boxes, panels, etc)
  * Skinnable themes
  * Works with GLUT
  * Small (7.5k lines of code), 1-2MB compiled
  * Sample code
  * Well documented

### General Design ###

All on-screen renderable controllers derive from [g2Controller](g2Controller.md) which manages memory, theming, user input, and provides several rendering functions. g2Controllers allow any number of child objects to be added, as well as be added to any other controller. New properties set to a parent object propagate to child objects. This includes propagation of visibility, enable-states, positioning, and more.

The coordinate system is the same as OpenGL, meaning that the system's origin for all controller's is (0, 0) in the top left, with the x-dimension growing positive right, and the y-dimension growing positive bottom. Note that coordinates are localized relative to the parent object. This means that any root object (objects directly allocated to the root scene using a Glui2 factory-method) have their origin set to (0, 0), while any object allocated as the child of another controller has their origin set to the current position of the parent object.

Controller creation is much like like the original GLUI library: it takes a [Factory Method](http://en.wikipedia.org/wiki/Factory_method_pattern) approach. This is done so that any new GUI objects were internally managed by the library and easy to manage over time for end-developers.

[Theming](Theming.md) is based on a theme texture file, a theme description file, and a bitmap font file. When initializing the Glui2 library, the first parameter is the location of a theme description file, while will in itself describe the locations of the texture and bitmap image files. Texture description files only need to describe UI elements the end-developer would like to use in their application.

### GUI Controllers ###

Currently the project implements the following GUI controllers (12 in all), but allows for end-developers to quickly make extensions (all controllers, except [g2Dialog](g2Dialog.md) extend from [g2Controller](g2Controller.md)):

  * Labels (bitmap font) as [g2Label](g2Label.md)
  * Buttons as [g2Button](g2Button.md)
  * Text Fields as [g2TextField](g2TextField.md)
  * Radio Button / Group as [g2RadioGroup](g2RadioGroup.md)
  * CheckBox as [g2CheckBox](g2CheckBox.md)
  * Console as [g2Console](g2Console.md)
  * Spinner as [g2Spinner](g2Spinner.md)
  * Dropdown Selection as [g2Dropdown](g2Dropdown.md)
  * Progress Bar as [g2ProgressBar](g2ProgressBar.md)
  * Sliders (Horizontal / vertical) as [g2Slider](g2Slider.md)
  * Panels as [g2Panel](g2Panel.md)
  * Cross platform open/save dialogs as [g2Dialog](g2Dialog.md)

### Coding Style ###

This project uses [WebKit Coding Style Guidelines](http://www.webkit.org/coding/coding-style.html) for the most part. There are few exceptions, notably the CamelCase style is used but first letters are generally capitalized as a style rule. All public members start with g2 while private members are "hidden" using `__` (double underscore).

The code is string const-correct, does C++ style memory allocations (via new / delete operator), but rarely uses C++ STL classes.