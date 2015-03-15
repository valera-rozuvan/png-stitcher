# png-stitcher
Stitch together several PNG images into one PNG image.

Takes 2 or more input PNG files, and produces 1 output PNG file which is a
stitched version of the 2 or more input PNG files. Currently only stitches
files vertically. The files must be of the same width and height. Currently
no error checking is done on the width and height.

To compile on a Windows machine, run the following command (see build.bat):

    g++ lodepng.cpp main.cpp^
        -ansi -pedantic -Wall -Wextra -LC:\SDL2-2.0.3\lib\x86 -O3^
        -o png-stitcher.exe

SDL2-2.0.3 Lib for Windows can be downloaded from:

    https://www.libsdl.org/download-2.0.php

The author successfully compiled this program on a Windows 7 machine using
g++ (GCC) 4.8.1. (without warnings, and errors). Your result may vary.

License: The source of this program is licensed under GNU GENERAL PUBLIC
LICENSE Version 2. Please see file
[LICESE](https://github.com/valera-rozuvan/png-stitcher/blob/master/LICENSE)
for more detail.
