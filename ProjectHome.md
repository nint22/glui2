![http://www.cores2.com/files/Glui2/g2Logo.png](http://www.cores2.com/files/Glui2/g2Logo.png)

### Description ###

Glui2, an OpenGL User Interface Library, is a light-weight feature-rich stand-alone Graphical User Interface (GUI) for OpenGL and GLUT applications. Written in C/C++, it is clean to use, easy to extend, well documented, and supports Linux, Windows, and OSX, as well as is very small! (Only 7.5k lines of code!)

Glui2, based on the original GLUI library by [Paul Rademacher](http://www.cs.unc.edu/~rademach/glui/), is a full re-write from scratch based on a similar minimalistic design. This project uses similar methods and programing interfaces, but now includes GUI theming, easier integration with applications, better performance (2D hardware acceleration), easier extending of new controllers, full documentation, and a clean implementation in portable C++. Checkout what the project looks like through our [screenshots](Screenshots.md) page!

Why use Glui2 versus all the other hundreds of GUI libraries? One big advantage is that it has a very small code base and interfacing footprint. Unlike wxWidgest or many other libraries, this code is ready to go and easy to use. Object instantiation is easy, there is no complex overhead, or bulky boilerplate code, etc. It truly is ready to go out of the box and extensible! The project currently builds and executes without any dependencies, other than OpenGL / GLUT, and requires no advanced OpenGL features. Glui2 runs in immediate-mode and only users OpenGL 1.1 standard features!

This library can easily be integrated with existing or new OpenGL applications designed for interactive media, scientific applications, academic usage, and more!

### Documentation ###

  * [Introduction](Introduction.md)
  * [Screenshots & Video](Screenshots.md)
  * Glui2 Classes
    * Shared
      * [Glui2](Glui2.md)
      * [g2Controller](g2Controller.md)
      * [g2Theme](g2Theme.md)
    * Controllers
      * [g2Label](g2Label.md)
      * [g2Button](g2Button.md)
      * [g2CheckBox](g2CheckBox.md)
      * [g2RadioGroup](g2RadioGroup.md)
      * [g2Spinner](g2Spinner.md)
      * [g2Slider](g2Slider.md)
      * [g2ProgressBar](g2ProgressBar.md)
      * [g2Dropdown](g2Dropdown.md)
      * [g2Console](g2Console.md)
      * [g2Panel](g2Panel.md)
      * [g2LabelEdit](g2LabelEdit.md)
      * [g2TextField](g2TextField.md)
      * [g2Dialog](g2Dialog.md)
  * [Extensibility](Extensibility.md)
  * [Theming](Theming.md)
    * [Themes](Themes.md)
  * [Examples & Usage](ExamplesAndUsage.md)

### Developer's Note ###

The lead developer of this project is [Jeremy Bridon](http://www.cores2.com). If you use this library for a project, feel free to drop him an email sharing what you accomplished. This project was mainly built for academic and game-development purposes during Jeremy's free time.

This software is free & open source (meaning both free to use, modify, and redistribute), but not free for me to make. Glui2 is a small project but it takes time and money to develop code and maintain it over time. [Please consider donating; anything helps!](http://www.cores2.com/blog/?page_id=22)

### Licensing ###

This software is licensed under LGPL.