### Themes ###
All theme files are a combination of three different files: a theme description file, a theme image, and a character bitmap used as a font. Theme description files (ending in **.cfg, following the**.ini file format) is expected to describe the location and size of each controller, as well as some other global fields associated with theme image and character bitmap locations. Either of these images can be of type Jpeg, PNG, BMP, TGA, or PSD (limited reading).

Included in the project are two complete theme files, as described in [Themes](Themes.md).

### Config Files ###
Configuration files closely resemble [Window's INI file format](http://en.wikipedia.org/wiki/INI_file) for simplicity and clarity, though there are some notable differences. Comments must start with a hash-pound character '#' rather than a semi-colon. Comments may take an entire line or be at the end of any valid line. Section / group titles are still declared using square-braces, and key-value definitions are formated using the key-value construct, using a `key:value` syntax.  Note again that unlike the INI standard, instead of using an equivalence character, we use a single colon ':' when defining a key-value pair. Please note that as of now, only ascii-encoded data is supported (this might change in the future).

Multi-line key-value strings (as an example, a long string of text) have to have all new lines started with a 4-spaces; a tab is not a valid spacing mechanism. See the example below.

As of now there are 32 sections; one that is theme-general and 31 for different GUI skin elements. In total there are 9 skinnable elements, with multiple states and sub-components each (for example, with the horizontal slider, you need to define the slider itself, the slider's button, and a disabled button state geometry).

#### Example ####

```
 # This is a comment, started using a hash character
 [group_name]          # Group name of key-value pairs; do not use brackets within the name
 key1: Some data       # Example of key-value pair (or instead of ':' use '=')
 key2: More data
 key3: Any data!
 key: This is an example of multi-line text; the new line MUST either
      be tabbed or include 4 or more space characters.
```

#### Performance Note ####
The internal implementation is based on the STL hash-map where the key is simply the lower-case section name appended with an underscore then the lower-case key name. Thus, lookup speed is determined by your C++ STL library implementation, but generally is a best-case of O(1) (constant time) and mostly a worst-case of O(log(n)).

On a more personal note, my experience has shown that STL hash-maps tend to have a higher constant than a simple from-scratch implementation. In the future, I might include my own simple hash-map, but to keep the code base simple and clean for now I'll be leaving that out.

### Configuration Variables ###
The following is a list of all the sections and keys, describing what they should map or be defined to.


  * [general](general.md)
    * image: <path to the image file>
    * font: <path to the character bitmap file>
    * background\_color: <three integers from 0-255, describing the background color>

  * [Button](Button.md)
    * point: <two integers, describing the top-left origin of this component>
    * size: <two integers, describing the width and height of this component>
  * [Button\_pressed](Button_pressed.md)
    * All other components implement the above point/size key-value pairs
  * [Button\_Disabled](Button_Disabled.md)

  * [checkbox](checkbox.md)
  * [checkbox\_Disabled](checkbox_Disabled.md)
  * [CheckBox\_Pressed](CheckBox_Pressed.md)
  * [checkbox\_Selected\_Disabled](checkbox_Selected_Disabled.md)

  * [TextField](TextField.md)
  * [TextField\_Disabled](TextField_Disabled.md)

  * [RadioButton](RadioButton.md)
  * [RadioButton\_Disabled](RadioButton_Disabled.md)
  * [RadioButton\_Pressed](RadioButton_Pressed.md)
  * [RadioButton\_Pressed\_Disabled](RadioButton_Pressed_Disabled.md)

  * [ProgressBar](ProgressBar.md)
  * [ProgressBar\_Fill](ProgressBar_Fill.md)
  * [ProgressBar\_Disabled](ProgressBar_Disabled.md)

  * [DropDown](DropDown.md)
  * [DropDown\_Pressed](DropDown_Pressed.md)
  * [DropDown\_Disabled](DropDown_Disabled.md)

  * [Spinner](Spinner.md)
  * [Spinner\_Pressed](Spinner_Pressed.md)
  * [Spinner\_Disabled](Spinner_Disabled.md)

  * [Panel](Panel.md)

  * [Slider](Slider.md)
  * [SliderButton](SliderButton.md)
  * [SliderButton\_Pressed](SliderButton_Pressed.md)
  * [SliderButton\_Disabled](SliderButton_Disabled.md)

  * [VSlider](VSlider.md)
  * [VSliderButton](VSliderButton.md)
  * [VSliderButton\_Pressed](VSliderButton_Pressed.md)
  * [VSliderButton\_Disabled](VSliderButton_Disabled.md)