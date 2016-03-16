ECHO OFF
ECHO This build tool uses GNU C/C++ toolchain to compile and link.
ECHO CYGWIN or MINGW is mandatorily required!
ECHO ----
g++ -std=c++98 -O3 -o testRunner.exe testRunner.cpp unitTests.cpp recursive.cpp logging.cpp bruteForce.cpp kadane.cpp arrayUtils.cpp
ECHO DONE
ECHO The runnable is main.exe
ECHO ON
