#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class ColorTableImageMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mInputStream.str( "" );
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
};


TEST_F( ColorTableImageMenuTest, usesColorTable ) {

  /* Setup */
  mInputStream.str( "set-color-table-size 5 \
set-color 0 14 15 16 \
set-color 1 7 8 9 \
set-color 2 4 5 6 \
set-color 3 10 20 30 \
set-color 4 1 2 3 \
grid 200 300 101 \
grid-set 0 0 0 \
grid-set 0 1 3 \
grid-set 0 2 2 \
grid-set 0 3 1 \
grid-set 0 4 101 \
grid-set 1 0 0 \
grid-set 1 1 30 \
grid-set 1 2 29 \
grid-set 1 3 28 \
grid-set 1 4 101 \
grid-set 2 0 0 \
grid-set 2 1 45 \
grid-set 2 2 44 \
grid-set 2 3 43 \
grid-set 2 4 101 \
grid-apply-color-table \
write color-image.ppm \
quit" );

  /* Stimulus */
  imageMenu( mInputStream, mOutputStream );

  /* Comparison */
  PPM ppm_tmp;
  mInputStream.clear( );
  mInputStream.str( "color-image.ppm" );
  readUserImage( mInputStream, mOutputStream, ppm_tmp );
  remove( "color-image.ppm" );
  const PPM& ppm = ppm_tmp;

  EXPECT_EQ( 300, ppm.getWidth( ) );
  EXPECT_EQ( 200, ppm.getHeight( ) );
  EXPECT_EQ( 30, ppm.getMaxColorValue( ) );

  EXPECT_EQ( 10, ppm.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( 30, ppm.getChannel( 0, 0, 2 ) );

  EXPECT_EQ( 10, ppm.getChannel( 1, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 1, 0, 1 ) );
  EXPECT_EQ( 30, ppm.getChannel( 1, 0, 2 ) );

  EXPECT_EQ( 10, ppm.getChannel( 2, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 2, 0, 1 ) );
  EXPECT_EQ( 30, ppm.getChannel( 2, 0, 2 ) );

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
