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
  unsigned width, height, error, i;
  lodepng::State png_state;
  vector<unsigned char> input_image, output_image, file_buffer;


  // Check if user gave at least 3 filenames as arguments to this program.
  // 2 files to stitch, and 1 file as the output.
  if (argc < 4) {
    cout << "Please provide at least 3 filenames." << endl;

    return 0;
  }


  // Configure PNG state options.
  png_state.decoder.color_convert = 0;
  // Make it reproduce even unknown chunks in the saved image.
  png_state.decoder.remember_unknown_chunks = 1;


  // Read all images to stitch together one by one, and append to master
  // output image.
  for (i = 1; i < static_cast<unsigned>(argc - 1); i += 1) {
    lodepng::load_file(file_buffer, argv[i]);
    error = lodepng::decode(input_image, width, height, png_state, file_buffer);
    if (error) {
      cout << "[ERROR]: processing file " << i << " '" << argv[i] << "'." << endl;
      cout << "[decoder error " << error << "]: " << lodepng_error_text(error) << endl;

      return 0;
    }
    file_buffer.clear();

    output_image.reserve(output_image.size() + input_image.size());
    output_image.insert(output_image.end(), input_image.begin(), input_image.end());

    input_image.clear();
  }


  // Write the stitched master output image to a file.
  png_state.encoder.text_compression = 1;
  error = lodepng::encode(file_buffer, output_image, width, (argc - 2) * height, png_state);
  if (error) {
    cout << "[ERROR]: saving file" << endl;
    cout << "[encoder error " << error << "]: " << lodepng_error_text(error) << endl;

    return 0;
  }
  lodepng::save_file(file_buffer, argv[argc - 1]);


  // All went well.
  return 0;
}
