#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorInvertTest : public ::testing::Test {
protected:
  ColorInvertTest( )
    : color( 13, 17, 19 ), parameterized_red( 13 ), parameterized_green( 17 ), parameterized_blue( 19 ),
      max_color_value( 100 ),
      inverted_red( 87 ), inverted_green( 83 ), inverted_blue( 81 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Color color;
  int parameterized_red;
  int parameterized_green;
  int parameterized_blue;
  int max_color_value;
  int inverted_red;
  int inverted_green;
  int inverted_blue;
};

TEST_F( ColorInvertTest, invertsRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( max_color_value );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( inverted_red, color_const.getRed( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, invertsGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( max_color_value );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( inverted_green, color_const.getGreen( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, invertsBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( max_color_value );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( inverted_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, doesNotInvertTooSmall ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( 18 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, doesNotInvertDueToRed ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  parameterized_red = 101;
  color.setRed( parameterized_red );
  color.invert( 100 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, doesNotInvertDueToGreen ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  parameterized_green = 101;
  color.setGreen( parameterized_green );
  color.invert( 100 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, doesNotInvertDueToBlue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  parameterized_blue = 1234;
  color.setBlue( parameterized_blue );
  color.invert( parameterized_blue-1 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( parameterized_red, color_const.getRed( ) );
  EXPECT_EQ( parameterized_green, color_const.getGreen( ) );
  EXPECT_EQ( parameterized_blue, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorInvertTest, doesInvertMax ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color.invert( 19 );
  const Color& color_const = color;

  /* Comparison */
  EXPECT_EQ( 6, color_const.getRed( ) );
  EXPECT_EQ( 2, color_const.getGreen( ) );
  EXPECT_EQ( 0, color_const.getBlue( ) );

  /* Tear-down */
  // Done automatically
}
