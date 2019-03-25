#include "JuliaSet.h"
#include "JuliaSet.h" // Did you #ifndef your file?
#include "PPM.h"
#include "PPM.h"
#include "ColorTable.h"
#include "ColorTable.h"

#include "gtest/gtest.h"
#include <fstream>


class JuliaSetPPMTest : public ::testing::Test {
public:

  JuliaSetPPMTest( ) : ct( 5 ) {
  }

protected:


  virtual void SetUp( ) {
    default_width = 300;
    default_height = 200;
    default_min_x = -2.0;
    default_max_x =  2.0;
    default_min_y = -1.5;
    default_max_y =  1.5;
    default_a = -0.650492;
    default_b = -0.478235;
    default_max_escape_count = 255;
    default_size = 120000;

    expected_width = 5;
    expected_height = 3;
    expected_min_x = -1.0;
    expected_max_x =  1.5;
    expected_min_y = -0.2;
    expected_max_y =  1.2;
    expected_a =  0.314;
    expected_b = -0.271;
    expected_max_escape_count = 101;
    expected_size = 75000;
    js.setMaxNumber( expected_max_escape_count );

    js.setNumber( 0, 0, 0 );
    js.setNumber( 0, 1, 3 );
    js.setNumber( 0, 2, 2 );
    js.setNumber( 0, 3, 1 );
    js.setNumber( 0, 4, expected_max_escape_count );

    js.setNumber( 1, 0, 0 );
    js.setNumber( 1, 1, 3+27 );
    js.setNumber( 1, 2, 2+27 );
    js.setNumber( 1, 3, 1+27 );
    js.setNumber( 1, 4, expected_max_escape_count );

    js.setNumber( 2, 0, 0 );
    js.setNumber( 2, 1, 3+42 );
    js.setNumber( 2, 2, 2+42 );
    js.setNumber( 2, 3, 1+42 );
    js.setNumber( 2, 4, expected_max_escape_count );

    expected_max_color_value = 30;

    ct[ 4 ] = Color( 1, 2, 3 );
    ct[ 3 ] = Color( 10, 20, expected_max_color_value );
    ct[ 2 ] = Color( 4, 5, 6 );
    ct[ 1 ] = Color( 7, 8, 9 );
    ct[ 0 ] = Color( 14, 15, 16 );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  JuliaSet js;
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  double default_a, default_b;
  int default_max_escape_count;
  int default_size;

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  double expected_a, expected_b;
  int expected_max_escape_count;
  int expected_size;

  int expected_max_color_value;
  ColorTable ct;
  PPM ppm;
};


TEST_F( JuliaSetPPMTest, setsPPMWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm, ct );

  /* Comparison */
  EXPECT_EQ( default_width, ppm.getWidth( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( JuliaSetPPMTest, setsPPMHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( default_height, ppm.getHeight( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( JuliaSetPPMTest, setsPPMMaxColorValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( expected_max_color_value, ppm.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetPPMTest, setsPPMMaxColorValueWhenBlue ) {

  /* Setup */
  ct[ 4 ] = Color( 1, 2, 3 );
  ct[ 3 ] = Color( 19, 20, expected_max_color_value );
  ct[ 2 ] = Color( 4, 5, 6 );
  ct[ 1 ] = Color( 7, 8, 9 );
  ct[ 0 ] = Color( 14, 15, 16 );


  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( expected_max_color_value, ppm.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetPPMTest, setsPPMMaxColorValueWhenGreen ) {

  /* Setup */
  ct[ 4 ] = Color( 1, 2, 3 );
  ct[ 3 ] = Color( 19, expected_max_color_value, 20  );
  ct[ 2 ] = Color( 4, 5, 6 );
  ct[ 1 ] = Color( 7, 8, 9 );
  ct[ 0 ] = Color( 14, 15, 16 );


  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( expected_max_color_value, ppm.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetPPMTest, setsPPMMaxColorValueWhenRed ) {

  /* Setup */
  ct[ 4 ] = Color( 1, 2, 3 );
  ct[ 3 ] = Color( expected_max_color_value, 19, 20  );
  ct[ 2 ] = Color( 4, 5, 6 );
  ct[ 1 ] = Color( 7, 8, 9 );
  ct[ 0 ] = Color( 14, 15, 16 );


  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( expected_max_color_value, ppm.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetPPMTest, setsPPMZeroColor ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( 10, ppm.getChannel( 0, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 0, 0, 1 ) );
  EXPECT_EQ( expected_max_color_value, ppm.getChannel( 0, 0, 2 ) );

  EXPECT_EQ( 10, ppm.getChannel( 1, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 1, 0, 1 ) );
  EXPECT_EQ( expected_max_color_value, ppm.getChannel( 1, 0, 2 ) );

  EXPECT_EQ( 10, ppm.getChannel( 2, 0, 0 ) );
  EXPECT_EQ( 20, ppm.getChannel( 2, 0, 1 ) );
  EXPECT_EQ( expected_max_color_value, ppm.getChannel( 2, 0, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetPPMTest, setsPPMMaxEscapeCountColor ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( 1, ppm.getChannel( 0, 4, 0 ) );
  EXPECT_EQ( 2, ppm.getChannel( 0, 4, 1 ) );
  EXPECT_EQ( 3, ppm.getChannel( 0, 4, 2 ) );

  EXPECT_EQ( 1, ppm.getChannel( 1, 4, 0 ) );
  EXPECT_EQ( 2, ppm.getChannel( 1, 4, 1 ) );
  EXPECT_EQ( 3, ppm.getChannel( 1, 4, 2 ) );

  EXPECT_EQ( 1, ppm.getChannel( 2, 4, 0 ) );
  EXPECT_EQ( 2, ppm.getChannel( 2, 4, 1 ) );
  EXPECT_EQ( 3, ppm.getChannel( 2, 4, 2 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetPPMTest, setsPPMEscapeCountColor ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  js_const.setPPM( ppm,ct );

  /* Comparison */
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


TEST_F( JuliaSetPPMTest, setsPPMWorksWithOnly3Colors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  ct.setNumberOfColors( 3 );
  ct[ 2 ] = Color( 4, 5, 6 );
  ct[ 1 ] = Color( 7, 8, 9 );
  ct[ 0 ] = Color( 14, 15, 16 );

  js_const.setPPM( ppm,ct );

  /* Comparison */
  int row, column;
  int r_expected, g_expected, b_expected;
  for( row = 0; row < 3; row++ ) {
    for( column = 0; column < 5; column++ ) {

      if( column == 0 ) {
        r_expected = 7;
        g_expected = 8;
        b_expected = 9;
      } else if( column == 4 ) {
        r_expected = 4;
        g_expected = 5;
        b_expected = 6;
      } else {
        r_expected = 14;
        g_expected = 15;
        b_expected = 16;
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


TEST_F( JuliaSetPPMTest, setsPPMDoesNothingWithLessThan3Colors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;
  ct.setNumberOfColors( 2 );
  ct[ 1 ] = Color( 7, 8, 9 );
  ct[ 0 ] = Color( 14, 15, 16 );
  ppm.setWidth( 1 );
  ppm.setHeight( 2 );
  ppm.setMaxColorValue( 3 );
  js_const.setPPM( ppm,ct );

  /* Comparison */
  EXPECT_EQ( 1, ppm.getWidth( ) );
  EXPECT_EQ( 2, ppm.getHeight( ) );
  EXPECT_EQ( 3, ppm.getMaxColorValue( ) );

  /* Tear-down */
  // Done automatically
}
