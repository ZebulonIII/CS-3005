#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class setColorTest : public ::testing::Test {
protected:

  setColorTest( ) : ct( 5 ) {
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


TEST_F( setColorTest, setsColor ) {

  /* Setup */
  mInputStream.str( "2 23 45 67" );
  mExpectedOutput = "Position? Red? Green? Blue? ";
  expected_color.setRed( 23 );
  expected_color.setGreen( 45 );
  expected_color.setBlue( 67 );

  /* Stimulus */
  setColor( mInputStream, mOutputStream, ct );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( expected_color, color_table_const[ 2 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( setColorTest, setsColor2 ) {

  /* Setup */
  mInputStream.str( "3 45 67 23 " );
  mExpectedOutput = "Position? Red? Green? Blue? ";
  expected_color.setRed( 45 );
  expected_color.setGreen( 67 );
  expected_color.setBlue( 23 );

  /* Stimulus */
  setColor( mInputStream, mOutputStream, ct );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( expected_color, color_table_const[ 3 ] );

  /* Tear-down */
  // Done automatically
}
