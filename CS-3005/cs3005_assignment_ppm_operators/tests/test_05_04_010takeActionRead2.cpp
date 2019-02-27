#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

#include "test_05_04_000takeActionOperatorClass.h"

TEST_F( takeActionOperatorTest, doesRead2 ) {

  /* Setup */
  std::string filename = "test_image.ppm";
  writeFile( filename );
  mPrompt = "Input filename? ";
  mChoice = "read2";
  mInputStream.str( filename.c_str( ) );
  readFile( filename, mPPM );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = input_image2;
  const PPM& ppm_const2 = mPPM;

  /* Comparison */
  EXPECT_EQ( ppm_const.getHeight( ), ppm_const2.getHeight( ) );
  EXPECT_EQ( ppm_const.getWidth( ), ppm_const2.getWidth( ) );
  EXPECT_EQ( ppm_const.getMaxColorValue( ), ppm_const2.getMaxColorValue( ) );
  int row, column, channel;
  for( row = 0; row < expected_height; row++ ) {
    for( column = 0; column < expected_width; column++ ) {
      for( channel = 0; channel < 3; channel++ ) {
        EXPECT_EQ( ppm_const.getChannel( row, column, channel ), ppm_const2.getChannel( row, column, channel ) )
          << "row: " << row << " column: " << column << " channel: " << channel;
      }
    }
  }

  /* Tear-down */
  // Done automatically
}
