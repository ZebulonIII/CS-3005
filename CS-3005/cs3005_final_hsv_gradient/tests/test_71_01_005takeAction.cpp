#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class HSVGradientTakeActionTest : public ::testing::Test {
protected:

  HSVGradientTakeActionTest( )
    : color_table( 8 ),
      expected_color_0{ 255, 254, 253 },
      expected_color_1{ 249, 248, 247 },
      expected_color_2{  20,  87,  24 },
      expected_color_3{  73, 105,  69 },
      expected_color_4{ 126, 123, 115 },
      expected_color_5{ 179, 141, 160 },
      expected_color_6{ 232, 159, 206 },
      expected_color_7{ 252, 251, 250 },
      h1( 123.456 ), s1( 0.765 ), v1( 0.345 ),
      h2( 321.654 ), s2( 0.314 ), v2( 0.912 ) {
  }

  virtual void SetUp( ) {
    mExpected = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
    color_table[ 0 ] = expected_color_0;
    color_table[ 1 ] = expected_color_1;
    color_table[ 2 ] = expected_color_1;
    color_table[ 3 ] = expected_color_1;
    color_table[ 4 ] = expected_color_1;
    color_table[ 5 ] = expected_color_1;
    color_table[ 6 ] = expected_color_1;
    color_table[ 7 ] = expected_color_7;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mChoice;
  std::string mExpected;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM input_image1, input_image2, output_image;
  JuliaSet grid;
  ColorTable color_table;
  Color expected_color_0;
  Color expected_color_1;
  Color expected_color_2;
  Color expected_color_3;
  Color expected_color_4;
  Color expected_color_5;
  Color expected_color_6;
  Color expected_color_7;
  double h1, s1, v1;
  double h2, s2, v2;
};


TEST_F( HSVGradientTakeActionTest, setsGradientColors ) {

  /* Setup */
  mExpected = "First position? First hue? First saturation? First value? Second position? Second hue? Second saturation? Second value? ";
  mInputStream.str( "2 123.456 0.765 0.345 6 321.654 0.314 0.912" );
  mChoice = "set-hsv-color-gradient";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid, color_table );

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( expected_color_2, color_table[ 2 ] );
  EXPECT_EQ( expected_color_3, color_table[ 3 ] );
  EXPECT_EQ( expected_color_4, color_table[ 4 ] );
  EXPECT_EQ( expected_color_5, color_table[ 5 ] );
  EXPECT_EQ( expected_color_6, color_table[ 6 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( HSVGradientTakeActionTest, setsGradientColors2 ) {

  /* Setup */
  mExpected = "First position? First hue? First saturation? First value? Second position? Second hue? Second saturation? Second value? ";
  mInputStream.str( "2 321.654 0.314 0.912 6 123.456 0.765 0.345" );
  mChoice = "set-hsv-color-gradient";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid, color_table );

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( expected_color_6, color_table[ 2 ] );
  EXPECT_EQ( expected_color_5, color_table[ 3 ] );
  EXPECT_EQ( expected_color_4, color_table[ 4 ] );
  EXPECT_EQ( expected_color_3, color_table[ 5 ] );
  EXPECT_EQ( expected_color_2, color_table[ 6 ] );

  /* Tear-down */
  // Done automatically
}
