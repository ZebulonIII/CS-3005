#include "MandelbrotSet.h"
#include "MandelbrotSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class MandelbrotSetSetterTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 300;
    default_height = 200;
    default_min_x = -1.5;
    default_max_x =  1.5;
    default_min_y = -1.0;
    default_max_y =  1.0;
    default_max_escape_count = 255;

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

    invalid_coordinate_small = -2.0001;
    invalid_coordinate_large =  2.0001;
    new_min_x = -0.5;
    new_max_x =  1.25;
    new_min_y = -0.1;
    new_max_y =  0.9;
    invalid_parameter_small = -2.0001;
    invalid_parameter_large =  2.0001;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  MandelbrotSet js;
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  int default_max_escape_count;

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  int expected_max_escape_count;

  double invalid_coordinate_small, invalid_coordinate_large;
  double new_min_x, new_max_x;
  double new_min_y, new_max_y;
  double invalid_parameter_small, invalid_parameter_large;
};



TEST_F( MandelbrotSetSetterTest, setsValidWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, doesNotSetInvalidWidth1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( expected_height-1, 1 );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, doesNotSetInvalidWidthNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( expected_height-1, -100 );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, setsValidHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, doesNotSetInvalidHeight1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( 1, expected_width-1 );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, doesNotSetInvalidHeightNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( -100, expected_width-1 );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, doesNotSetInvalidWidthAndHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( 1, 1 );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, setsValidMinX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, setsValidMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, reordersMinXMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_max_x, new_min_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, setsValidMinY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, setsValidMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, reordersMinYMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_min_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, reordersMinXMaxXMinYMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_max_x, new_min_x,
                   new_max_y, new_min_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsInvalidMinX1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( invalid_coordinate_small, new_max_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsInvalidMinX2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( invalid_coordinate_large, new_max_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsInvalidMaxX1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, invalid_coordinate_small,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsInvalidMaxX2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, invalid_coordinate_large,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetSetterTest, rejectsInvalidMinY1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   invalid_coordinate_small, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsInvalidMinY2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   invalid_coordinate_large, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsInvalidMaxY1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, invalid_coordinate_small );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsInvalidMaxY2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, invalid_coordinate_large );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsEqualMinXMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_min_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, rejectsEqualMinYMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, allowsSmallPlaneSize ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -0.01;
  new_max_x =  0.01;
  new_min_y = -1.01;
  new_max_y = -0.99;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, allowsSmallPlaneSizeSwappedX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -0.01;
  new_max_x =  0.01;
  new_min_y = -1.01;
  new_max_y = -0.99;
  js.setPlaneSize( new_max_x, new_min_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, allowsSmallPlaneSizeSwappedY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -0.01;
  new_max_x =  0.01;
  new_min_y = -1.01;
  new_max_y = -0.99;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_min_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, allowsFullPlaneSize ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -2.00;
  new_max_x =  2.00;
  new_min_y = -2.00;
  new_max_y =  2.00;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, allowsFullPlaneSizeSwappedX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -2.00;
  new_max_x =  2.00;
  new_min_y = -2.00;
  new_max_y =  2.00;
  js.setPlaneSize( new_max_x, new_min_x,
                   new_min_y, new_max_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( MandelbrotSetSetterTest, allowsFullPlaneSizeSwappedY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -2.00;
  new_max_x =  2.00;
  new_min_y = -2.00;
  new_max_y =  2.00;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_min_y );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( MandelbrotSetSetterTest, setsValidMaxNumber ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, doesNotSetInvalidMaxNumber1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setMaxNumber( -1 );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetSetterTest, doesNotSetInvalidMaxNumber2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setMaxNumber( -100 );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}
