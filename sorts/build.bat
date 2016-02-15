ECHO OFF
ECHO This build tool uses GNU C/C++ toolchain to compile and link.
ECHO CYGWIN or MINGW is mandatorily required!
ECHO ----
g++ -O3 -std=c++11 -Wstrict-overflow -Wno-missing-field-initializers -Wno-missing-field-initializers -Wall -o sortMain.exe insertionSort.cpp selectionSort.cpp mergeSort.cpp timing.cpp sortMain.cpp
ECHO DONE
ECHO The runnable is sortMain.exe
ECHO ON
