#include "JuliaSet.h"
#include "JuliaSet.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class JuliaSetConstructorTest : public ::testing::Test {
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
};



TEST_F( JuliaSetConstructorTest, setsDefaultWidth ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultHeight ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMinX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMaxX ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMinY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMaxY ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultA ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_a, js_const.getA( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultB ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorTest, setsDefaultMaxNumber ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}

class JuliaSetConstructorParamTest : public ::testing::Test {
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
  }

  void SetUp1( ) {
    default_width = 200;
    default_height = 100;
    default_min_x = -1.0;
    default_max_x =  1.7;
    default_min_y = -1.9;
    default_max_y =  0.3;
    default_a = -0.560492;
    default_b = -0.748235;
    default_max_escape_count = 255;
  }

  void SetUp2( ) {
    default_width = 200;
    default_height = 100;
    default_min_x = -1.0;
    default_max_x = -0.7;
    default_min_y =  0.9;
    default_max_y =  1.3;
    default_a =  0.560492;
    default_b = -0.874235;
    default_max_escape_count = 255;
  }

  virtual void TearDown( ) {
  }

  /* data members */
  int default_width, default_height;
  double default_min_x, default_max_x;
  double default_min_y, default_max_y;
  double default_a, default_b;
  int default_max_escape_count;
};



TEST_F( JuliaSetConstructorParamTest, setsWidth ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );


  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsHeight ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMinX ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMaxX ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMinY ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMaxY ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsA ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_a, js_const.getA( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsB ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMaxNumber ) {

  /* Setup */
  SetUp1( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( JuliaSetConstructorParamTest, setsWidth2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );


  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_width, js_const.getWidth( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsHeight2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_height, js_const.getHeight( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMinX2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_x, js_const.getMinX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMaxX2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_x, js_const.getMaxX( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMinY2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_min_y, js_const.getMinY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMaxY2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_max_y, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsA2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_a, js_const.getA( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsB2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_DOUBLE_EQ( default_b, js_const.getB( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( JuliaSetConstructorParamTest, setsMaxNumber2 ) {

  /* Setup */
  SetUp2( );
  JuliaSet js( default_height, default_width,
               default_min_x, default_max_x, default_min_y, default_max_y,
               default_a, default_b );

  /* Stimulus */
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( default_max_escape_count, js_const.getMaxNumber( ) );

  /* Tear-down */
  // Done automatically
}
