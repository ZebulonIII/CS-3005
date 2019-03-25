#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class setColorGradientTest : public ::testing::Test {
protected:

  setColorGradientTest( ) : ct( 5 ) {
  }

  virtual void SetUp( ) {
    mGrid = new JuliaSet( );
    mExpectedOutput = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    expected_max_escape_count = 101;
    mGrid->setMaxNumber( expected_max_escape_count );

    mGrid->setNumber( 0, 0, 0 );
    mGrid->setNumber( 0, 1, 3 );
    mGrid->setNumber( 0, 2, 2 );
    mGrid->setNumber( 0, 3, 1 );
    mGrid->setNumber( 0, 4, expected_max_escape_count );

    mGrid->setNumber( 1, 0, 0 );
    mGrid->setNumber( 1, 1, 3+27 );
    mGrid->setNumber( 1, 2, 2+27 );
    mGrid->setNumber( 1, 3, 1+27 );
    mGrid->setNumber( 1, 4, expected_max_escape_count );

    mGrid->setNumber( 2, 0, 0 );
    mGrid->setNumber( 2, 1, 3+42 );
    mGrid->setNumber( 2, 2, 2+42 );
    mGrid->setNumber( 2, 3, 1+42 );
    mGrid->setNumber( 2, 4, expected_max_escape_count );

    expected_max_color_value = 30;

    ct[ 4 ] = Color( 1, 2, 3 );
    ct[ 3 ] = Color( 10, 20, expected_max_color_value );
    ct[ 2 ] = Color( 4, 5, 6 );
    ct[ 1 ] = Color( 7, 8, 9 );
    ct[ 0 ] = Color( 14, 15, 16 );

    default_width = 300;
    default_height = 200;
  }

  virtual void TearDown( ) {
    if( mGrid != 0 ) {
      delete mGrid;
      mGrid = 0;
    }
  }

  /* data members */
  std::string mExpectedOutput;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  NumberGrid *mGrid;
  ColorTable ct;
  PPM ppm;
  int expected_max_color_value;
  int expected_num_color;
  int expected_max_escape_count;
  int default_width, default_height;
  Color expected_color;
};


TEST_F( setColorGradientTest, setsColor ) {

  /* Setup */
  mInputStream.str( "4 0 0 0 7 200 200 200" );
  mExpectedOutput = "First position? First red? First green? First blue? Second position? Second red? Second green? Second blue? ";
  ct.setNumberOfColors( 8 );
  Color g1( 0, 0, 0 );
  Color g2( 200, 200, 200 );
  Color e4( 0, 0, 0 );
  Color e5( 66, 66, 66 );
  Color e6( 133, 133, 133 );
  Color e7( 200, 200, 200 );

  /* Stimulus */
  setColorGradient( mInputStream, mOutputStream, ct );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( e4, ct[ 4 ] );
  EXPECT_EQ( e5, ct[ 5 ] );
  EXPECT_EQ( e6, ct[ 6 ] );
  EXPECT_EQ( e7, ct[ 7 ] );

  /* Tear-down */
  // Done automatically
}
