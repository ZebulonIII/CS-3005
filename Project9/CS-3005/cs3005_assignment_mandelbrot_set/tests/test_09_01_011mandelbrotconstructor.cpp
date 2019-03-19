#include "MandelbrotSet.h"
#include "MandelbrotSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class MandelbrotSetConstructorTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 300;
    default_height = 200;
    default_min_x = -1.5;
    default_max_x =  1.5;
    default_min_y = -1.0;
    default_max_y =  1.0;
    default_max_escape_count = 255;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  MandelbrotSet js;
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  int default_max_escape_count;
};



TEST_F( MandelbrotSetConstructorTest, setsDefaultWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorTest, setsDefaultHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorTest, setsDefaultMinX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorTest, setsDefaultMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorTest, setsDefaultMinY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorTest, setsDefaultMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorTest, setsDefaultMaxNumber ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

class MandelbrotSetConstructorParamTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    default_width = 300;
    default_height = 200;
    default_min_x = -1.5;
    default_max_x =  1.5;
    default_min_y = -1.0;
    default_max_y =  1.0;
    default_max_escape_count = 255;
  }

  void SetUp1( ) {
    default_width = 200;
    default_height = 100;
    default_min_x = -1.0;
    default_max_x =  1.7;
    default_min_y = -1.9;
    default_max_y =  0.3;
    default_max_escape_count = 255;
  }

  void SetUp2( ) {
    default_width = 200;
    default_height = 100;
    default_min_x = -1.0;
    default_max_x = -0.7;
    default_min_y =  0.9;
    default_max_y =  1.3;
    default_max_escape_count = 255;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  int default_max_escape_count;
};



TEST_F( MandelbrotSetConstructorParamTest, setsWidth ) {

  /* Setup */
  SetUp1( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );


  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsHeight ) {

  /* Setup */
  SetUp1( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMinX ) {

  /* Setup */
  SetUp1( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMaxX ) {

  /* Setup */
  SetUp1( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMinY ) {

  /* Setup */
  SetUp1( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMaxY ) {

  /* Setup */
  SetUp1( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMaxNumber ) {

  /* Setup */
  SetUp1( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( MandelbrotSetConstructorParamTest, setsWidth2 ) {

  /* Setup */
  SetUp2( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );


  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsHeight2 ) {

  /* Setup */
  SetUp2( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMinX2 ) {

  /* Setup */
  SetUp2( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMaxX2 ) {

  /* Setup */
  SetUp2( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMinY2 ) {

  /* Setup */
  SetUp2( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMaxY2 ) {

  /* Setup */
  SetUp2( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( MandelbrotSetConstructorParamTest, setsMaxNumber2 ) {

  /* Setup */
  SetUp2( );
  MandelbrotSet js( default_height, default_width,
                    default_min_x, default_max_x, default_min_y, default_max_y );

  /* Stimulus */
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}
