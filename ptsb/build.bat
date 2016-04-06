ECHO OFF
ECHO This build tool uses GNU C/C++ toolchain to compile and link.
ECHO CYGWIN or MINGW is mandatorily required!
ECHO ----
g++ -std=c++11 -O3 -o ptsp.exe brutes.cpp logging.cpp utilities.cpp main.cpp -Wall -O3 -DGRAD -DEXTRA_CREDIT_RECURSIVE -DEXTRA_CREDIT_NON_RECURSIVE

ECHO DONE
ECHO The runnable is ptsb.exe
ECHO ON
