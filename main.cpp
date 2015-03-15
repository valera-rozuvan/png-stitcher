/**
 * png-stitcher
 * version 0.1
 *
 *
 * Author:
 *     Valera Rozuvan | valera.rozuvan@gmail.com
 *
 *
 * Last modified:
 *     15.03.2015
 *
 *
 * Description:
 *     Takes 2 or more input PNG files, and produces 1 output PNG file
 * which is a stitched version of the 2 or more input PNG files. Currently only
 * stitches files vertically. The files must be of the same width and height.
 * Currently no error checking is done on the width and height.
 *
 *
 * 3rd party dependencies:
 *     1.) lodepng - PNG encoder and decoder in C and C++.
 *         https://github.com/lvandeve/lodepng
 *
 *
 * Compiling:
 *     To compile on a Windows machine, run the following command (see
 * build.bat):
 *     g++ lodepng.cpp main.cpp^
 *         -ansi -pedantic -Wall -Wextra -O3^
 *         -o png-stitcher.exe
 *
 * The author successfully compiled this program on a Windows 7 machine using
 * g++ (GCC) 4.8.1. (without warnings, and errors). Your result may vary.
 *
 *
 * License:
 *     The source of this program is licensed under GNU GENERAL PUBLIC LICENSE
 * Version 2. Please see file LICESE for more detail.
 */

#include "lodepng.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  vector<unsigned char> image, image3;
  unsigned w, h, i, error;
  vector<unsigned char> buffer, buffer3;
  lodepng::State state;


  // Check if user gave at least 3 filenames as arguments to this program.
  // 2 files to stitch, and 1 file as the output.
  if (argc < 4) {
    cout << "Please provide at least 3 filenames." << endl;
    return 0;
  }


  // Configure PNG state options.
  state.decoder.color_convert = 0;
  // Make it reproduce even unknown chunks in the saved image.
  state.decoder.remember_unknown_chunks = 1;


  // Read all images to stitch together one by one, and append to master
  // output image.
  for (i = 1; i < static_cast<unsigned>(argc - 1); i += 1) {
    lodepng::load_file(buffer, argv[i]);
    error = lodepng::decode(image, w, h, state, buffer);
    if (error) {
      cout << "[ERROR]: processing file " << i << " '" << argv[i] << "'." << endl;
      cout << "[decoder error " << error << "]: " << lodepng_error_text(error) << endl;

      return 0;
    }
    buffer.clear();

    image3.reserve( image3.size() + image.size() );
    image3.insert( image3.end(), image.begin(), image.end() );
    image.clear();
  }


  // Write the stitched master output image to a file.
  state.encoder.text_compression = 1;
  error = lodepng::encode(buffer3, image3, w, (argc - 2) * h, state);
  if (error) {
    cout << "[ERROR]: saving file" << endl;
    cout << "[encoder error " << error << "]: " << lodepng_error_text(error) << endl;

    return 0;
  }
  lodepng::save_file(buffer3, argv[argc - 1]);


  // All went well.
  return 0;
}
