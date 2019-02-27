#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class showMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected = "\n\
Actions available:\n\
\n\
read1) Read file into input image 1.\n\
read2) Read file into input image 2.\n\
write) Write output image to file.\n\
copy) Copy input image 1 to output image.\n\
red-gray) Set output image from input image 1's grayscale from red.\n\
green-gray) Set output image from input image 1's grayscale from green.\n\
blue-gray) Set output image from input image 1's grayscale from blue.\n\
linear-gray) Set output image from input image 1's grayscale from linear colorimetric.\n\
+) Set output image from sum of input image 1 and input image 2\n\
+=) Set input image 1 by adding in input image 2\n\
-) Set output image from difference of input image 1 and input image 2\n\
-=) Set input image 1 by subtracting input image 2\n\
*) Set output image from input image 1 multiplied by a number\n\
*=) Set input image 1 by multiplying by a number\n\
/) Set output image from input image 1 divided by a number\n\
/=) Set input image 1 by dividing by a number\n\
# Comment to end of line\n\
size) Set the size of input image 1\n\
max) Set the max color value of input image 1\n\
channel) Set a channel value in input image 1\n\
pixel) Set a pixel's 3 values in input image 1\n\
clear) Set all pixels to 0,0,0 in input image 1\n\
diamond) Draw a diamond shape in input image 1\n\
circle) Draw a circle shape in input image 1\n\
box) Draw a box shape in input image 1\n\
quit) Quit\n\
\n\
";

    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpected;
  std::stringstream mOutputStream;
};


TEST_F( showMenuTest, displaysMenu ) {

  /* Setup */
  // automatic

  /* Stimulus */
  showMenu( mOutputStream );

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}
