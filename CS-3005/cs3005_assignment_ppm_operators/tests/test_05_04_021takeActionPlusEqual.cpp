#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

#include "test_05_04_000takeActionOperatorClass.h"

TEST_F( takeActionOperatorTest, doesPlusEquals ) {

  /* Setup */
  mPrompt = "";
  mChoice = "+=";
  mInputStream.str( "" );
  mOutputStream.str( "" );
  // input_image1 and input_image2 are set in the setUp() method above.
  const PPM ppm_image2_original = input_image2;
  const PPM ppm_output_original = output_image;

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = mPlusPPM;
  const PPM& ppm_const2 = input_image1;

  /* Comparison */
  identical_ppms( ppm_const, ppm_const2 );
  identical_ppms( ppm_image2_original, input_image2 );
  identical_ppms( ppm_output_original, output_image );

  /* Tear-down */
  // Done automatically
}
