#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class ColorTableTakeActionTest : public ::testing::Test {
protected:

  ColorTableTakeActionTest( ) : ct( 5 ) { }

  virtual void SetUp( ) {
    mExpected = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

    input_image1.setHeight( 1 );
    input_image1.setWidth( 2 );
    input_image1.setMaxColorValue( 3 );
    input_image1.setPixel( 0, 0, 1, 2, 3 );
    input_image1.setPixel( 0, 1, 2, 1, 0 );

    input_image2.setHeight( 2 );
    input_image2.setWidth( 1 );
    input_image2.setMaxColorValue( 4 );
    input_image2.setPixel( 0, 0, 4, 2, 0 );
    input_image2.setPixel( 1, 0, 0, 1, 2 );

    output_image.setHeight( 1 );
    output_image.setWidth( 1 );
    output_image.setMaxColorValue( 5 );
    output_image.setPixel( 0, 0, 5, 3, 1 );

    default_width = 300;
    default_height = 200;
    grid.setGridSize( default_height, default_width );
    expected_max_escape_count = 101;
    grid.setMaxNumber( expected_max_escape_count );

    grid.setNumber( 0, 0, 0 );
    grid.setNumber( 0, 1, 3 );
    grid.setNumber( 0, 2, 2 );
    grid.setNumber( 0, 3, 1 );
    grid.setNumber( 0, 4, expected_max_escape_count );

    grid.setNumber( 1, 0, 0 );
    grid.setNumber( 1, 1, 3+27 );
    grid.setNumber( 1, 2, 2+27 );
    grid.setNumber( 1, 3, 1+27 );
    grid.setNumber( 1, 4, expected_max_escape_count );

    grid.setNumber( 2, 0, 0 );
    grid.setNumber( 2, 1, 3+42 );
    grid.setNumber( 2, 2, 2+42 );
    grid.setNumber( 2, 3, 1+42 );
    grid.setNumber( 2, 4, expected_max_escape_count );

    ct[ 4 ] = Color( 1, 2, 3 );
    ct[ 3 ] = Color( 10, 20, 30 );
    ct[ 2 ] = Color( 4, 5, 6 );
    ct[ 1 ] = Color( 7, 8, 9 );
    ct[ 0 ] = Color( 14, 15, 16 );

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
  ColorTable ct;
  int expected_num_color;
  Color expected_color;
  int default_width, default_height;
  int expected_max_escape_count;
};


TEST_F( ColorTableTakeActionTest, setsColorTableSize ) {

  /* Setup */
  mExpected = "Size? ";
  mInputStream.str( "17" );
  mChoice = "set-color-table-size";
  expected_num_color = 17;

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid, ct );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( expected_num_color, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableTakeActionTest, setsColor ) {

  /* Setup */
  mExpected = "Position? Red? Green? Blue? ";
  mInputStream.str( "3 45 67 23 " );
  mChoice = "set-color";
  expected_color.setRed( 45 );
  expected_color.setGreen( 67 );
  expected_color.setBlue( 23 );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid, ct );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( expected_color, color_table_const[ 3 ] );

  /* Tear-down */
  // Done automatically
}


TEST_F( ColorTableTakeActionTest, setsRandomColor ) {

  /* Setup */
  mInputStream.str( "2" );
  mExpected = "Position? ";
  mChoice = "set-random-color";
  expected_color.setRed( 4 );
  expected_color.setGreen( 5 );
  expected_color.setBlue( 6 );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid, ct );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( false, expected_color == color_table_const[ 2 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableTakeActionTest, setsColorGradient ) {

  /* Setup */
  mInputStream.str( "4 0 0 0 7 200 200 200" );
  mExpected = "First position? First red? First green? First blue? Second position? Second red? Second green? Second blue? ";

  mChoice = "set-color-gradient";
  ct.setNumberOfColors( 8 );
  Color g1( 0, 0, 0 );
  Color g2( 200, 200, 200 );
  Color e4( 0, 0, 0 );
  Color e5( 66, 66, 66 );
  Color e6( 133, 133, 133 );
  Color e7( 200, 200, 200 );

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid, ct );

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( e4, ct[ 4 ] );
  EXPECT_EQ( e5, ct[ 5 ] );
  EXPECT_EQ( e6, ct[ 6 ] );
  EXPECT_EQ( e7, ct[ 7 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableTakeActionTest, appliesColorTable ) {

  /* Setup */
  mInputStream.str( "" );
  mExpected = "";
  mChoice = "grid-apply-color-table";

  /* Stimulus */
  takeAction( mInputStream, mOutputStream, mChoice, input_image1, input_image2, output_image, grid, ct );
  const PPM& ppm = output_image;

  /* Comparison */
  EXPECT_EQ( mExpected, mOutputStream.str( ) );
  EXPECT_EQ( default_width, ppm.getWidth( ) );
  EXPECT_EQ( default_height, ppm.getHeight( ) );
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
