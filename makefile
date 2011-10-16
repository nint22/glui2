################################################################
# 
# GLUI 2 - OpenGL User Interface Library 2
# Copyright 2011 Core S2 - See License.txt for details
# 
# This source file is developed and maintained by:
# + Jeremy Bridon jbridon@cores2.com
# 
# File: makefile
# Desc: The linux makefile for most linux and unix-like systems.
# 
################################################################

# Supress verbose output
.SILENT:

# Define the source code / implementation files
sources := \
Glui2/g2Button.cpp \
Glui2/g2CheckBox.cpp \
Glui2/g2Config.cpp \
Glui2/g2Console.cpp \
Glui2/g2Controller.cpp \
Glui2/g2Dialog.cpp \
Glui2/g2DropDown.cpp \
Glui2/g2Label.cpp \
Glui2/g2LabelEdit.cpp \
Glui2/g2Panel.cpp \
Glui2/g2ProgressBar.cpp \
Glui2/g2RadioGroup.cpp \
Glui2/g2Slider.cpp \
Glui2/g2Spinner.cpp \
Glui2/g2TextField.cpp \
Glui2/g2Theme.cpp \
Glui2/g2Utilities.cpp \
Glui2/g2Images.cpp \
Glui2/glui2.cpp \
Glui2/stb_image.c \

# Define the output product
product := libglui2.so

# Define all object files we are compiling
objects := $(sources:.cpp=.o) $(sources:.c=.o)

# Needed libraries
libs := -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

# Needed headers
includes := -I/usr/include

# Build the library itself
all: $(objects)
	@echo "Building Glui2 lib..."
	g++ -Wall -Wextra $(libs) -shared -o $(product) Glui2/*.o
	@echo "Done!"

# Compile each individual object file
%.o: %.cpp %.h
	@echo "Creating object file for \"$<\""
	g++ -Wall -Wextra $(libs) -fPIC -c $< -o $@ $(includes)
	@echo "Done with object file"

# Install the lib
install:
	@echo Copying to lib...
	cp $(product) /usr/lib/.
	mkdir -p /usr/include/Glui2
	cp Glui2/*.h /usr/include/Glui2/.
	@echo Done with installing

# Clean object files
clean:
	@echo Cleaning...
	rm -rf Glui2/*.o $(product)
	@echo Done with cleaning
