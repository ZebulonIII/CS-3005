#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorTableConstructorTest : public ::testing::Test {
protected:
  ColorTableConstructorTest( )
    : color_table( 13 ), expected_num_color( 13 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  ColorTable color_table;
  size_t expected_num_color;
};

TEST_F( ColorTableConstructorTest, setsNumberOfColors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const ColorTable& color_table_const = color_table;

  /* Comparison */
  EXPECT_EQ( expected_num_color, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableConstructorTest, setsNumberOfColors2 ) {

  /* Setup */
  expected_num_color = 75;
  ColorTable c2( expected_num_color );

  /* Stimulus */
  const ColorTable& color_table_const = c2;

  /* Comparison */
  EXPECT_EQ( expected_num_color, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableConstructorTest, setsNumberOfColors123 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  ColorTable ct( 123 );
  const ColorTable& color_table_const = ct;

  /* Comparison */
  EXPECT_EQ( 123, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}
