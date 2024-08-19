# GameEngine
A game engine I wrote in Highschool

It's written in C, with OpenGL, and minimal external libraries

It handles rendering, with object creation similar to game engines I've used like Unity \
I got bogged down at the time with transformations as I hadn't taken any matrix math courses at that point, so rotations especially could use some work

It uses \
GLAD for OpenGL function loading \
GLFW for windowing \
HandmadeMath.h for basic math functions \
stb_image.h for image loading

Might be hard to compile, it uses a MinGW makefile and some batch scripts \
The executable is in the bin folder, didn't know to exclude it at the time \
