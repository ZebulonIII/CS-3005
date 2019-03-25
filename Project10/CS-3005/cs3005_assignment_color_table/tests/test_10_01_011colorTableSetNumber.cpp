#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorTableSetNumberOfColorTest : public ::testing::Test {
protected:
  ColorTableSetNumberOfColorTest( )
    : color_table( 13 ), expected_num_color( 17 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  ColorTable color_table;
  size_t expected_num_color;
};

TEST_F( ColorTableSetNumberOfColorTest, setsNumberOfColors ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.setNumberOfColors( expected_num_color );
  const ColorTable& color_table_const = color_table;

  /* Comparison */
  EXPECT_EQ( expected_num_color, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableSetNumberOfColorTest, setsNumberOfColors2 ) {

  /* Setup */
  expected_num_color = 72;

  /* Stimulus */
  color_table.setNumberOfColors( expected_num_color );
  const ColorTable& color_table_const = color_table;

  /* Comparison */
  EXPECT_EQ( expected_num_color, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableSetNumberOfColorTest, setsNumberOfColorsOther ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.setNumberOfColors( expected_num_color+13 );
  const ColorTable& color_table_const = color_table;

  /* Comparison */
  EXPECT_EQ( expected_num_color+13, color_table_const.getNumberOfColors( ) );

  /* Tear-down */
  // Done automatically
}
