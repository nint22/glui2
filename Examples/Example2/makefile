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
# This makefile is used for an example application
# 
################################################################

# Supress verbose output
.SILENT:

# Define the source code / implementation files
sources := main.cpp

# Define the output product
product := Example2

# Needed libraries
libs := -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm -lglui2

# Needed headers (and extra libs)
includes := -I/usr/include

# Build the example itself
all: $(sources)
	@echo Buildin Example1...
	g++ -Wall -Wextra $(libs) $(includes) -o $(product) $(sources)
	@echo Done!

# Clean object files
clean:
	rm -rf *.o $(product)
