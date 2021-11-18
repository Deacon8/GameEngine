@echo off
#remove -g and -wall for non-debug build
gcc -g -Wall src/Test.c -o bin/Test.exe
cd bin
Test.exe