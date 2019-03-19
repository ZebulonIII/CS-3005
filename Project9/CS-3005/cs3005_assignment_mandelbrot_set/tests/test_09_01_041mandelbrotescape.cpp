#include "MandelbrotSet.h"
#include "MandelbrotSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class MandelbrotSetEscapeTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 300;
    default_height = 200;
    default_min_x = -1.5;
    default_max_x =  1.5;
    default_min_y = -1.0;
    default_max_y =  1.0;
    default_max_escape_count = 255;
    default_size = 60000;

    expected_width = 350;
    expected_height = 250;
    expected_min_x = -1.0;
    expected_max_x =  1.5;
    expected_min_y = -0.2;
    expected_max_y =  1.2;
    expected_max_escape_count = 123;
    expected_size = 87500;
    js.setGridSize( expected_height, expected_width );
    js.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
    js.setMaxNumber( expected_max_escape_count );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  MandelbrotSet js;
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  int default_max_escape_count;
  unsigned int default_size;

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  int expected_max_escape_count;
  unsigned int expected_size;
};


TEST_F( MandelbrotSetEscapeTest, constructorSizesVector ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  MandelbrotSet js_default;
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_EQ( default_size, js_const.getNumbers( ).size( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetEscapeTest, setGridSizeResizesVector ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_size, js_const.getNumbers( ).size( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetEscapeTest, getNumberChecksRowTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( -1, expected_width/2 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, getNumberChecksRowTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height, expected_width/2 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetEscapeTest, getNumberChecksColumnTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height/2, -1 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, getNumberChecksColumnTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height/2, expected_width );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetEscapeTest, setNumberSetsValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height/2, expected_width/2, 7 );
  const MandelbrotSet& js_const = js;
  int actual_escape_count = js_const.getNumber( expected_height/2, expected_width/2 );
  const int expected_escape_count = 7;

  /* Comparison */
  EXPECT_EQ( expected_escape_count, actual_escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberSetsValueMinimumColumn ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height/2, 0, 7 );
  const MandelbrotSet& js_const = js;
  int actual_escape_count = js_const.getNumber( expected_height/2, 0 );
  const int expected_escape_count = 7;

  /* Comparison */
  EXPECT_EQ( expected_escape_count, actual_escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberSetsValueMaximumColumn ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height/2, expected_width-1, 7 );
  const MandelbrotSet& js_const = js;
  int actual_escape_count = js_const.getNumber( expected_height/2, expected_width-1 );
  const int expected_escape_count = 7;

  /* Comparison */
  EXPECT_EQ( expected_escape_count, actual_escape_count );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetEscapeTest, setNumberSetsValueMinimumRow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( 0, expected_width/2, 7 );
  const MandelbrotSet& js_const = js;
  int actual_escape_count = js_const.getNumber( 0, expected_width/2 );
  const int expected_escape_count = 7;

  /* Comparison */
  EXPECT_EQ( expected_escape_count, actual_escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberSetsValueMaximumRow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height-1, expected_width/2, 7 );
  const MandelbrotSet& js_const = js;
  int actual_escape_count = js_const.getNumber( expected_height-1, expected_width/2 );
  const int expected_escape_count = 7;

  /* Comparison */
  EXPECT_EQ( expected_escape_count, actual_escape_count );

  /* Tear-down */
  // Done automatically
}




TEST_F( MandelbrotSetEscapeTest, setNumberChecksRowTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( -1, expected_width/2, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( -1, expected_width/2 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberChecksRowTooLowVeryLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( -1000000, expected_width/2, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( -1000000, expected_width/2 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberChecksRowTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height, expected_width/2, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height, expected_width/2 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetEscapeTest, setNumberChecksRowTooHighVeryHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height+1000000, expected_width/2, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height+1000000, expected_width/2 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetEscapeTest, setNumberChecksColumnTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height/2, -1, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height/2, -1 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberChecksColumnTooLowVeryLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height/2, -1000000, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height/2, -1000000 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberChecksColumnTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height/2, expected_width, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height/2, expected_width );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, setNumberChecksColumnTooHighVeryHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setNumber( expected_height/2, expected_width+1000000, 7 );
  const MandelbrotSet& js_const = js;
  int escape_count = js_const.getNumber( expected_height/2, expected_width+1000000 );

  /* Comparison */
  EXPECT_EQ( -1, escape_count );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, vectorIndexesAreUnique ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  int row, column, count;
  js.setMaxNumber( expected_width*expected_height+1 );
  count = 1;
  for( row = 0; row < expected_height; row++ ) {
    for( column = 0; column < expected_width; column++, count++ ) {
      js.setNumber( row, column, count );
    }
  }
  const MandelbrotSet& js_const = js;

  /* Comparison */

  /* When this test fails, it is *very* verbose and causes
   * problems for CodeGrinder.  We'll generate only one
   * test output that corresponds to the *first* error.
   * Beware, there are probably more than one.
   */
  // count = 1;
  // for( row = 0; row < expected_height; row++ ) {
  //   for( column = 0; column < expected_width; column++, count++ ) {
  //     EXPECT_EQ( count, js_const.getNumber( row, column ) )
  //       << "(row,column) = (" << row << "," << column << ")" << std::endl;
  //   }
  // }

  /*
   * This version will only report the first failure.
   */
  bool failed = false;
  count = 1;
  for( row = 0; row < expected_height; row++ ) {
    for( column = 0; column < expected_width; column++, count++ ) {
      if( count != js_const.getNumber( row, column ) ) {
        EXPECT_EQ( count, js_const.getNumber( row, column ) )
          << "(row,column) = (" << row << "," << column << ")" << "  BEWARE.  THERE ARE PROBABLY MANY MORE THAT FAIL." << std::endl;
        failed = true;
        break;
      }
    }
    if( failed ) {
      break;
    }
  }

  /* Tear-down */
  // Done automatically
}



TEST_F( MandelbrotSetEscapeTest, calculatesNextPoint1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double x0, y0, x1, y1, a, b;
  a = 1.0;
  b = -1.0;
  x0 = 0.;
  y0 = 0.;
  double expected_x1 = x0*x0 - y0*y0 + a;
  double expected_y1 = 2*x0*y0 + b;
  js_const.calculateNextPoint( x0, y0, a, b, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesNextPoint2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double x0, y0, x1, y1, a, b;
  a = 0.5;
  b = 0.25;
  x0 = -1.0;
  y0 = 1.0;
  double expected_x1 = x0*x0 - y0*y0 + a;
  double expected_y1 = 2*x0*y0 + b;
  js_const.calculateNextPoint( x0, y0, a, b, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesNextPoint3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double x0, y0, x1, y1, a, b;
  a = -0.123;
  b = 1.23;
  x0 = -0.3;
  y0 = 0.2;
  double expected_x1 = x0*x0 - y0*y0 + a;
  double expected_y1 = 2*x0*y0 + b;
  js_const.calculateNextPoint( x0, y0, a, b, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesNextPoint4 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double x0, y0, x1, y1, a, b;
  a = 0.3;
  b = -0.02;
  x0 = 3.1;
  y0 = 2.2;
  double expected_x1 = x0*x0 - y0*y0 + a;
  double expected_y1 = 2*x0*y0 + b;
  js_const.calculateNextPoint( x0, y0, a, b, x1, y1 );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x1, x1 );
  EXPECT_DOUBLE_EQ( expected_y1, y1 );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount0_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a = 0.1;
  b = 2.0;

  /* Comparison */
  EXPECT_EQ( 0, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount0_1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a = 0.1;
  b = -2.0;

  /* Comparison */
  EXPECT_EQ( 0, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount0_2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a = -2.0;
  b =  0.1;

  /* Comparison */
  EXPECT_EQ( 0, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount0_3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a =  2.0;
  b =  0.1;

  /* Comparison */
  EXPECT_EQ( 0, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount1_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a = 0.0;
  b = 2.0;

  /* Comparison */
  EXPECT_EQ( 1, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount1_1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a = 0.0;
  b = -2.0;

  /* Comparison */
  EXPECT_EQ( 1, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount1_2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a =  1.41;
  b = -1.41;

  /* Comparison */
  EXPECT_EQ( 1, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount1_3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a =  2.0;
  b =  0.0;

  /* Comparison */
  EXPECT_EQ( 1, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount1_4 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a =  -1.0;
  b =  0.5;

  /* Comparison */
  EXPECT_EQ( 4, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCount1_5 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a =  -0.80;
  b =  -0.50;

  /* Comparison */
  EXPECT_EQ( 5, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPlaneEscapeCountMax_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double a, b;
  a =  0.0;
  b =  0.0;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.calculatePlaneEscapeCount( a, b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPixelEscapeCount_0 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = 0, column = 0;

  /* Comparison */
  EXPECT_EQ( 2, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPixelEscapeCount_1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = 0, column = expected_width - 1;

  /* Comparison */
  EXPECT_EQ( 1, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPixelEscapeCount_2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = expected_height - 1, column = 0;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPixelEscapeCount_3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = expected_height - 1, column = expected_width - 1;

  /* Comparison */
  EXPECT_EQ( 1, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPixelEscapeCount_4 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = expected_height/2, column = expected_width/2;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesPixelEscapeCount_5 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( 200, 200 );
  js.setPlaneSize( -2.0, 2.0, -2.0, 2.0 );
  js.setMaxNumber( 3 );
  int row = 80, column = 170;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( 1, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, doesNotCalculatesPixelEscapeCountRowTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = -1, column = expected_width/2;

  /* Comparison */
  EXPECT_EQ( -1, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, doesNotCalculatesPixelEscapeCountRowTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = expected_height, column = expected_width/2;

  /* Comparison */
  EXPECT_EQ( -1, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, doesNotCalculatesPixelEscapeCountColumnTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = expected_height/2, column = -1;

  /* Comparison */
  EXPECT_EQ( -1, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, doesNotCalculatesPixelEscapeCountColumnTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  int row = expected_height/2, column = expected_width;

  /* Comparison */
  EXPECT_EQ( -1, js_const.calculateNumber( row, column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetEscapeTest, calculatesAllNumbers ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.calculateAllNumbers( );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( 2, js_const.getNumber( 0, 0 ) )
    << "(row,column) = (" << 0 << "," << 0 << ")" << std::endl;

  EXPECT_EQ( expected_max_escape_count, js_const.getNumber( expected_height-1, 0 ) )
    << "(row,column) = (" << (expected_height-1) << "," << 0 << ")" << std::endl;

  EXPECT_EQ( 1, js_const.getNumber( 0, expected_width-1 ) )
    << "(row,column) = (" << 0 << "," << (expected_width-1) << ")" << std::endl;

  EXPECT_EQ( 1, js_const.getNumber( expected_height-1, expected_width-1 ) )
    << "(row,column) = (" << (expected_height-1) << "," << (expected_width-1) << ")" << std::endl;

  EXPECT_EQ( expected_max_escape_count, js_const.getNumber( expected_height/2, expected_width/2 ) )
    << "(row,column) = (" << (expected_height/2) << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( 4, js_const.getNumber( 13*expected_height/20, 12*expected_width/20 ) )
    << "(row,column) = (" << 13*expected_height/20 << "," << 12*expected_width/20 << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( -1, expected_width/2 ) )
    << "(row,column) = (" << -1 << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( expected_height, expected_width/2 ) )
    << "(row,column) = (" << (expected_height) << "," << (expected_width/2) << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( expected_height/2, -1 ) )
    << "(row,column) = (" << (expected_height/2) << "," << -1 << ")" << std::endl;

  EXPECT_EQ( -1, js_const.getNumber( expected_height/2, expected_width ) )
    << "(row,column) = (" << (expected_height/2) << "," << (expected_width) << ")" << std::endl;

  /* Tear-down */
  // Done automatically
}
