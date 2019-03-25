#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class setColorTableSizeTest : public ::testing::Test {
protected:

  setColorTableSizeTest( ) : ct( 5 ) {
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
};


TEST_F( setColorTableSizeTest, setsSize ) {

  /* Setup */
  mInputStream.str( "10" );
  mExpectedOutput = "Size? ";
  expected_num_color = 10;

  /* Stimulus */
  setColorTableSize( mInputStream, mOutputStream, ct );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( expected_num_color, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( setColorTableSizeTest, setsSize123 ) {

  /* Setup */
  mInputStream.str( "123" );
  mExpectedOutput = "Size? ";
  expected_num_color = 123;

  /* Stimulus */
  setColorTableSize( mInputStream, mOutputStream, ct );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( expected_num_color, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}
