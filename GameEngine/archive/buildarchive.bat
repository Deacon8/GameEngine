@echo off
#remove -g and -wall for non-debug build

set appName = GameEngine;
set useDebug = -g -Wall
set includePaths = -I/../external
set externalLibs = -L/../external/libs
gcc %useDebug% src/Test.c -o bin/%appName%.exe includePaths externalLibs

#cd bin
./%appName%
#.exe