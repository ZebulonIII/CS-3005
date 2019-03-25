#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ColorTableGetMaxColorChannelTest : public ::testing::Test {
protected:
  ColorTableGetMaxColorChannelTest( )
    : color_table( 21 ) {
  }

  virtual void SetUp( ) {
    int value;
    int i,j;
    max = 0;
    for( i = 0; i < 21; i++ ) {
      for( j = 0; j < 3; j++ ) {
        value = (i*j + 13) % 74;
        if( value > max ) {
          max = value;
        }
        color_table[ i ].setChannel( j, value );
      }
    }
  }
  virtual void SetUp2( ) {
    int value;
    int i,j;
    max = 0;
    for( i = 0; i < 21; i++ ) {
      for( j = 0; j < 3; j++ ) {
        value = (i*j + 31) % 47;
        if( value > max ) {
          max = value;
        }
        color_table[ i ].setChannel( j, value );
      }
    }
  }

  virtual void TearDown( ) {
  }

  /* data members */
  ColorTable color_table;
  size_t expected_num_color;
  int max;
};

TEST_F( ColorTableGetMaxColorChannelTest, getsMaxChannelValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const ColorTable& color_table_const = color_table;

  /* Comparison */
  EXPECT_EQ( max, color_table_const.getMaxChannelValue( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( ColorTableGetMaxColorChannelTest, getsMaxChannelValue2 ) {

  /* Setup */
  SetUp2( );

  /* Stimulus */
  const ColorTable& color_table_const = color_table;

  /* Comparison */
  EXPECT_EQ( max, color_table_const.getMaxChannelValue( ) );

  /* Tear-down */
  // Done automatically
}
