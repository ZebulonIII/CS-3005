#include "MandelbrotSet.h"
#include "MandelbrotSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class MandelbrotSetCoordinatesTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 300;
    default_height = 200;
    default_min_x = -1.5;
    default_max_x =  1.5;
    default_min_y = -1.0;
    default_max_y =  1.0;
    default_max_escape_count = 255;
    default_delta_x =  0.01;
    default_delta_y =  0.01;

    expected_width = 350;
    expected_height = 250;
    expected_min_x = -1.0;
    expected_max_x =  1.5;
    expected_min_y = -0.2;
    expected_max_y =  1.2;
    expected_max_escape_count = 123;
    js.setGridSize( expected_height, expected_width );
    js.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
    js.setMaxNumber( expected_max_escape_count );

    expected_delta_x = 2.5 / 349;
    expected_delta_y = 1.4 / 249;
    row = 135;
    column = 5;
    expected_x = -.96418338108882521490;
    expected_y = 0.44096385542168674830;

    new_delta_x = 3.5 / 349;
    new_delta_y = 3.4 / 249;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  MandelbrotSet js_default;
  MandelbrotSet js;
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  int default_max_escape_count;
  double default_delta_x, default_delta_y;

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  int expected_max_escape_count;

  double expected_delta_x, expected_delta_y;
  int row, column;
  double expected_x, expected_y;

  double new_delta_x, new_delta_y;
};



TEST_F( MandelbrotSetCoordinatesTest, constructorSetsDeltaX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_delta_x, js_const.getDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, constructorSetsDeltaY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_delta_y, js_const.getDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, setsValidDeltaX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js_default.setDeltas( new_delta_x, new_delta_y );
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_delta_x, js_const.getDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, setsValidDeltaY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js_default.setDeltas( new_delta_x, new_delta_y );
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_delta_y, js_const.getDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, doesNotSetInvalidDeltaX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js_default.setDeltas( -new_delta_x, new_delta_y );
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_delta_x, js_const.getDeltaX( ) );
  EXPECT_DOUBLE_EQ( default_delta_y, js_const.getDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, doesNotSetInvalidDeltaY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js_default.setDeltas( new_delta_x, -new_delta_y );
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_delta_x, js_const.getDeltaX( ) );
  EXPECT_DOUBLE_EQ( default_delta_y, js_const.getDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, doesNotSetInvalidDeltaXAndY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js_default.setDeltas( -new_delta_x, -new_delta_y );
  const MandelbrotSet& js_const = js_default;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_delta_x, js_const.getDeltaX( ) );
  EXPECT_DOUBLE_EQ( default_delta_y, js_const.getDeltaY( ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( MandelbrotSetCoordinatesTest, calculatesDeltaX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.calculateDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesDeltaXSameSignPositive ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x =  0.5;
  expected_max_x =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.7 / 349;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.calculateDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesDeltaXSameSignNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x = -1.5;
  expected_max_x = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.9 / 349;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.calculateDeltaX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesDeltaY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.calculateDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesDeltaYSameSignPositive ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y =  0.2;
  expected_max_y =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 1.0 / 249;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.calculateDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesDeltaYSameSignNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y = -1.2;
  expected_max_y = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 0.6 / 249;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.calculateDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, setGridSizeSetsDeltas ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_width = 150;
  expected_height = 125;
  js.setGridSize( expected_height, expected_width );
  expected_delta_x = 2.5 / 149;
  expected_delta_y = 1.4 / 124;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.getDeltaX( ) );
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.getDeltaY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, setPlaneSizeSetsDeltas ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x = -1.2;
  expected_max_x =  0.6;
  expected_min_y = -1.2;
  expected_max_y = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 1.8 / 349;
  expected_delta_y = 0.6 / 249;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_delta_x, js_const.getDeltaX( ) );
  EXPECT_DOUBLE_EQ( expected_delta_y, js_const.getDeltaY( ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneX2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x =  0.5;
  expected_max_x =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.7 / 349;
  column = 13;
  expected_x = column * expected_delta_x + expected_min_x;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneX3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x = -1.5;
  expected_max_x = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.9 / 349;
  column = 217;
  expected_x = column * expected_delta_x + expected_min_x;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneX4 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x = -1.5;
  expected_max_x = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.9 / 349;
  column = 299;
  expected_x = column * expected_delta_x + expected_min_x;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneX5 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_x = -1.5;
  expected_max_x = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_x = 0.9 / 349;
  column = 0;
  expected_x = column * expected_delta_x + expected_min_x;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, js_const.calculatePlaneXFromPixelColumn( column ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, rejectsTooLowColumn ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneXFromPixelColumn( -1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, rejectsTooHighColumn ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneXFromPixelColumn( expected_width ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneY2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y =  0.2;
  expected_max_y =  1.2;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 1.0 / 249;
  row = 111;
  expected_y = expected_max_y - row * expected_delta_y;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneY3 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y = -1.2;
  expected_max_y = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 0.6 / 249;
  row = 83;
  expected_y = expected_max_y - row * expected_delta_y;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneY4 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y = -1.2;
  expected_max_y = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 0.6 / 249;
  row = 249;
  expected_y = expected_max_y - row * expected_delta_y;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetCoordinatesTest, calculatesPlaneY5 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  expected_min_y = -1.2;
  expected_max_y = -0.6;
  js.setPlaneSize( expected_min_x, expected_max_x,
                   expected_min_y, expected_max_y );
  expected_delta_y = 0.6 / 249;
  row = 0;
  expected_y = expected_max_y - row * expected_delta_y;
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_y, js_const.calculatePlaneYFromPixelRow( row ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, rejectsTooLowRow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneYFromPixelRow( -1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, rejectsTooHighRow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, js_const.calculatePlaneYFromPixelRow( expected_height ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, calculatesPixelToPlane ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double x, y;
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( row, column, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_x, x );
  EXPECT_DOUBLE_EQ( expected_y, y );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, rejectsColumnOrRowTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double x, y;
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( -1, column, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Stimulus */
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( row, -1, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetCoordinatesTest, rejectsColumnOrRowTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;
  double x, y;
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( expected_height, column, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Stimulus */
  js_const.calculatePlaneCoordinatesFromPixelCoordinates( row, expected_width, x, y );

  /* Comparison */
  EXPECT_DOUBLE_EQ( 0.0, x );
  EXPECT_DOUBLE_EQ( 0.0, y );

  /* Tear-down */
  // Done automatically
}
