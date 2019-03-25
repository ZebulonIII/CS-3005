#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class applyGridColorTableTest : public ::testing::Test {
protected:

  applyGridColorTableTest( ) : ct( 5 ) {
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
  int expected_max_escape_count;
  int default_width, default_height;
};


TEST_F( applyGridColorTableTest, setsPPM ) {

  /* Setup */
  mInputStream.str( "" );
  mExpectedOutput = "";

  /* Stimulus */
  applyGridColorTable( mInputStream, mOutputStream, *mGrid, ct, ppm );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( default_width, ppm.getWidth( ) );
  EXPECT_EQ( default_height, ppm.getHeight( ) );
  EXPECT_EQ( expected_max_color_value, ppm.getMaxColorValue( ) );

  EXPECT_EQ( 10, ppm.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( expected_max_color_value, ppm.getChannel( 0, 0, 2 ) );

  EXPECT_EQ( 10, ppm.getChannel( 1, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 1, 0, 1 ) );
  EXPECT_EQ( expected_max_color_value, ppm.getChannel( 1, 0, 2 ) );

  EXPECT_EQ( 10, ppm.getChannel( 2, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 2, 0, 1 ) );
  EXPECT_EQ( expected_max_color_value, ppm.getChannel( 2, 0, 2 ) );

  EXPECT_EQ( 1, ppm.getChannel( 0, 4, 0 ) );
  EXPECT_EQ( 2, ppm.getChannel( 0, 4, 1 ) );
  EXPECT_EQ( 3, ppm.getChannel( 0, 4, 2 ) );

  EXPECT_EQ( 1, ppm.getChannel( 1, 4, 0 ) );
  EXPECT_EQ( 2, ppm.getChannel( 1, 4, 1 ) );
  EXPECT_EQ( 3, ppm.getChannel( 1, 4, 2 ) );

  EXPECT_EQ( 1, ppm.getChannel( 2, 4, 0 ) );
  EXPECT_EQ( 2, ppm.getChannel( 2, 4, 1 ) );
  EXPECT_EQ( 3, ppm.getChannel( 2, 4, 2 ) );

  int row, column;
  int r_expected, g_expected, b_expected;
  for( row = 0; row < 3; row++ ) {
    for( column = 3; column >= 1; column-- ) {

      if( column % 3 == 0 ) {
        r_expected = 7;
        g_expected = 8;
        b_expected = 9;
      } else if( column % 3 == 1 ) {
        r_expected = 14;
        g_expected = 15;
        b_expected = 16;
      } else if( column % 3 == 2 ) {
        r_expected = 4;
        g_expected = 5;
        b_expected = 6;
      }

      EXPECT_EQ( r_expected, ppm.getChannel( row, column, 0 ) )
        << "(row,column) = (" << row << "," << column << ")" << std::endl;
      EXPECT_EQ( g_expected, ppm.getChannel( row, column, 1 ) )
        << "(row,column) = (" << row << "," << column << ")" << std::endl;
      EXPECT_EQ( b_expected, ppm.getChannel( row, column, 2 ) )
        << "(row,column) = (" << row << "," << column << ")" << std::endl;
    }
  }


  /* Tear-down */
  // Done automatically
}
