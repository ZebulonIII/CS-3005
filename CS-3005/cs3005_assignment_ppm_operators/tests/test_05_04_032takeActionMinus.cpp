#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

#include "test_05_04_000takeActionOperatorClass.h"

TEST_F( takeActionOperatorTest, doesMinus ) {

  /* Setup */
  mPrompt = "";
  mChoice = "-";
  mInputStream.str( "" );
  mOutputStream.str( "" );
  // input_image1 and input_image2 are set in the setUp() method above.
  const PPM ppm_image1_original = input_image1;
  const PPM ppm_image2_original = input_image2;

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image );
  const PPM& ppm_const = mMinusPPM;
  const PPM& ppm_const2 = output_image;

  /* Comparison */
  identical_ppms( ppm_const, ppm_const2 );
  identical_ppms( ppm_image1_original, input_image1 );
  identical_ppms( ppm_image2_original, input_image2 );

  /* Tear-down */
  // Done automatically
}
