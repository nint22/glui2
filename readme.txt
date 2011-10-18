
                             G L U I 2

=== Description ===

Glui2, an OpenGL User Interface Library, is a light-weight feature-rich
stand-alone Graphical User Interface (GUI) for OpenGL and GLUT
applications. Written in C/C++, it is clean to use, easy to extend, well
documented, and supports Linux, Windows, and OSX, as well as is very
small! (Only 7.5k lines of code!)

Glui2, based on the original GLUI library by Paul Rademacher, is a full
re-write from scratch based on a similar minimalistic design. This
project uses similar methods and programing interfaces, but now includes
GUI theming, easier integration with applications, better performance
(2D hardware acceleration), easier extending of new controllers, full
documentation, and a clean implementation in portable C++. Checkout what
the project looks like through our screenshots page!

Why use Glui2 versus all the other hundreds of GUI libraries? One big
advantage is that it has a very small code base and interfacing
footprint. Unlike wxWidgest or many other libraries, this code is ready
to go and easy to use. Object instantiation is easy, there is no complex
overhead, or bulky boilerplate code, etc. It truely is ready to go out
of the box and extensible!

This library can easily be integrated with existing or new OpenGL
applications designed for interactive media, scientific applications,
academic usage, and more!

=== Instalation ===

- Windows:

1. You will need Visual Studio C++ 2010 and Glui installed 2. Build the
entire solution 3. Copy headers and the produced *.dll and *.lib into
your System32 folder

- OSX:

1. You will need XCode (tested with XCode4) 2. Open the XCode project in
the root directory 3. Build and install by simply building the project
(installation is automatically done)

- Linux:

1. You will need to have x11 / Xorg, g++, and make installed 2. cd into
the root directory 3. Run "make" to build the library (sans examples) 4.
Run "make install" to install the library (WARNING: This is a very
simplified make file, the default install path is /user/local/lib" 5.
Done!

== Usage / Examples ===

Please read the online documentation for usage description. Included
here are a dozen examples, please look in the "Examples" directory and
the source code for a description.

=== Documentation ===

Please visit http://code.google.com/p/glui2/ for full documentation.

=== Developer's Note ===

The lead developer of this project is Jeremy Bridon
(http:.//www.cores2.com). If you use this library for a project, feel
free to drop him an email sharing what you accomplished. This project
was mainly built for academic and game-development purposes during
Jeremy's free time.

This software is free & open source (meaning both free to use, modify,
and redistribute), but not free for me to make. Glui2 is a small project
but it takes time and money to develop code and maintain it over time.
Please consider donating; anything helps! (http:.//www.cores2.com)

=== Licensing ===

This software is licensed under LGPL. Please read the "LICENSE" file for
more details and a full copy of the LPGL text.
