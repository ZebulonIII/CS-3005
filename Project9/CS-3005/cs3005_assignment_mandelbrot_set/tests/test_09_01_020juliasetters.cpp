#include "JuliaSet.h"
#include "JuliaSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetSetterTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 300;
    default_height = 200;
    default_min_x = -1.5;
    default_max_x =  1.5;
    default_min_y = -1.0;
    default_max_y =  1.0;
    default_a = -0.650492;
    default_b = -0.478235;
    default_max_escape_count = 255;

    expected_width = 350;
    expected_height = 250;
    expected_min_x = -1.0;
    expected_max_x =  1.5;
    expected_min_y = -0.2;
    expected_max_y =  1.2;
    expected_a =  0.314;
    expected_b = -0.271;
    expected_max_escape_count = 123;
    js.setGridSize( expected_height, expected_width );
    js.setPlaneSize( expected_min_x, expected_max_x,
                     expected_min_y, expected_max_y );
    js.setParameters( expected_a, expected_b );
    js.setMaxNumber( expected_max_escape_count );

    invalid_coordinate_small = -2.0001;
    invalid_coordinate_large =  2.0001;
    new_min_x = -0.5;
    new_max_x =  1.25;
    new_min_y = -0.1;
    new_max_y =  0.9;
    invalid_parameter_small = -2.0001;
    invalid_parameter_large =  2.0001;
    new_a = 0.111;
    new_b = 0.222;
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

  int expected_width, expected_height;
  double expected_min_x, expected_max_x;
  double expected_min_y, expected_max_y;
  double expected_a, expected_b;
  int expected_max_escape_count;

  double invalid_coordinate_small, invalid_coordinate_large;
  double new_min_x, new_max_x;
  double new_min_y, new_max_y;
  double invalid_parameter_small, invalid_parameter_large;
  double new_a, new_b;
};



TEST_F( JuliaSetSetterTest, setsValidWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidWidth1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( expected_height-1, 1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidWidthNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( expected_height-1, -100 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidHeight1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( 1, expected_width-1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidHeightNegative ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( -100, expected_width-1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidWidthAndHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setGridSize( 1, 1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_width, js_const.getWidth( ) );
  EXPECT_EQ( expected_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMinX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, reordersMinXMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_max_x, new_min_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMinY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, reordersMinYMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_min_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, reordersMinXMaxXMinYMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_max_x, new_min_x,
                   new_max_y, new_min_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidMinX1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( invalid_coordinate_small, new_max_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidMinX2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( invalid_coordinate_large, new_max_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidMaxX1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, invalid_coordinate_small,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidMaxX2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, invalid_coordinate_large,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( JuliaSetSetterTest, rejectsInvalidMinY1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   invalid_coordinate_small, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidMinY2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   invalid_coordinate_large, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidMaxY1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, invalid_coordinate_small );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidMaxY2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, invalid_coordinate_large );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsEqualMinXMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_min_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsEqualMinYMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( expected_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( expected_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( expected_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, allowsSmallPlaneSize ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -0.01;
  new_max_x =  0.01;
  new_min_y = -1.01;
  new_max_y = -0.99;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, allowsSmallPlaneSizeSwappedX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -0.01;
  new_max_x =  0.01;
  new_min_y = -1.01;
  new_max_y = -0.99;
  js.setPlaneSize( new_max_x, new_min_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, allowsSmallPlaneSizeSwappedY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -0.01;
  new_max_x =  0.01;
  new_min_y = -1.01;
  new_max_y = -0.99;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_min_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, allowsFullPlaneSize ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -2.00;
  new_max_x =  2.00;
  new_min_y = -2.00;
  new_max_y =  2.00;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, allowsFullPlaneSizeSwappedX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -2.00;
  new_max_x =  2.00;
  new_min_y = -2.00;
  new_max_y =  2.00;
  js.setPlaneSize( new_max_x, new_min_x,
                   new_min_y, new_max_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( JuliaSetSetterTest, allowsFullPlaneSizeSwappedY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  new_min_x = -2.00;
  new_max_x =  2.00;
  new_min_y = -2.00;
  new_max_y =  2.00;
  js.setPlaneSize( new_min_x, new_max_x,
                   new_max_y, new_min_y );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( new_min_x, js_const.getMinX( ) );
  EXPECT_DOUBLE_EQ( new_max_x, js_const.getMaxX( ) );
  EXPECT_DOUBLE_EQ( new_min_y, js_const.getMinY( ) );
  EXPECT_DOUBLE_EQ( new_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( JuliaSetSetterTest, setsValidA ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_a, js_const.getA( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidB ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidASmall ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setParameters( invalid_parameter_small, new_b );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_a, js_const.getA( ) );
  EXPECT_DOUBLE_EQ( expected_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidALarge ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setParameters( invalid_parameter_large, new_b );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_a, js_const.getA( ) );
  EXPECT_DOUBLE_EQ( expected_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidBSmall ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setParameters( new_a, invalid_parameter_small );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_a, js_const.getA( ) );
  EXPECT_DOUBLE_EQ( expected_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, rejectsInvalidBLarge ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setParameters( new_a, invalid_parameter_large );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( expected_a, js_const.getA( ) );
  EXPECT_DOUBLE_EQ( expected_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, setsValidMaxNumber ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidMaxNumber1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setMaxNumber( -1 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetSetterTest, doesNotSetInvalidMaxNumber2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  js.setMaxNumber( -100 );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( expected_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}
