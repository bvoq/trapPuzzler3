#!/bin/sh


# main2.cpp will be compiled instead of main.cpp (containing all the graphical user interface).
# It will only contain command line commands for generating levels.
# make sure this file is compilable with chmod +x

g++ -DcompiledWithoutOpenframeworks -std=c++11 -pthread main2.cpp \
eyes.cpp \
globals.cpp \
grid.cpp \
levelGen.cpp \
movement.cpp \
parallelLevelCreation.cpp \
puzzleSolver.cpp \
winningAnimation.cpp \
-o generator.o



