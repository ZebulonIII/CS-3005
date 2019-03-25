#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>

class ColorTableRandomTest : public ::testing::Test {
protected:
  ColorTableRandomTest( )
    : color_table( 13 ),
      expected_default_color{ 0, 0, 0 },
      expected_error_color{ -1, -1, -1 },
      expected_non_random_color{ 300, 29, 31 } {

        /* srand seeds at 100 usecond resolution */
        struct timeval time;
        gettimeofday(&time,NULL);
        srand((time.tv_sec * 10000) + (time.tv_usec / 100));
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  ColorTable color_table;
  Color expected_default_color;
  Color expected_error_color;
  Color expected_non_random_color;
};

TEST_F( ColorTableRandomTest, setsNonRandomColor ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table[ 12 ] = expected_non_random_color;

  /* Comparison */
  EXPECT_EQ( expected_non_random_color, color_table[ 12 ] );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, setsRandomColor ) {

  /* Setup */
  // Done automatically
  color_table[ 12 ] = expected_non_random_color;

  /* Stimulus */
  color_table.setRandomColor( 255, 12 );

  /* Comparison */
  EXPECT_EQ( expected_non_random_color == color_table[ 12 ], false );
  EXPECT_GE( 255, color_table[ 12 ].getRed( ) );
  EXPECT_GE( 255, color_table[ 12 ].getGreen( ) );
  EXPECT_GE( 255, color_table[ 12 ].getBlue( ) );
  EXPECT_LE( 0, color_table[ 12 ].getRed( ) );
  EXPECT_LE( 0, color_table[ 12 ].getGreen( ) );
  EXPECT_LE( 0, color_table[ 12 ].getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, setsRandomSmall ) {

  /* Setup */
  // Done automatically
  color_table[ 12 ] = expected_non_random_color;

  /* Stimulus */
  color_table.setRandomColor( 1, 12 );

  /* Comparison */
  EXPECT_EQ( expected_non_random_color == color_table[ 12 ], false );
  EXPECT_GE( 1, color_table[ 12 ].getRed( ) );
  EXPECT_GE( 1, color_table[ 12 ].getGreen( ) );
  EXPECT_GE( 1, color_table[ 12 ].getBlue( ) );
  EXPECT_LE( 0, color_table[ 12 ].getRed( ) );
  EXPECT_LE( 0, color_table[ 12 ].getGreen( ) );
  EXPECT_LE( 0, color_table[ 12 ].getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, setsRandomColorMaxColorLow ) {

  /* Setup */
  // Done automatically
  color_table[ 12 ] = expected_non_random_color;

  /* Stimulus */
  color_table.setRandomColor( 0, 12 );

  /* Comparison */
  EXPECT_EQ( expected_non_random_color == color_table[ 12 ], false );
  EXPECT_EQ( 0, color_table[ 12 ].getRed( ) );
  EXPECT_EQ( 0, color_table[ 12 ].getGreen( ) );
  EXPECT_EQ( 0, color_table[ 12 ].getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, doesNotSetRandomColorMaxColorTooLow ) {

  /* Setup */
  // Done automatically
  color_table[ 12 ] = expected_non_random_color;

  /* Stimulus */
  color_table.setRandomColor( -1, 12 );

  /* Comparison */
  EXPECT_EQ( expected_non_random_color == color_table[ 12 ], true );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, doesNotSetRandomColorMaxColorTooLowVery ) {

  /* Setup */
  // Done automatically
  color_table[ 12 ] = expected_non_random_color;

  /* Stimulus */
  color_table.setRandomColor( -1000000, 12 );

  /* Comparison */
  EXPECT_EQ( expected_non_random_color == color_table[ 12 ], true );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, setsRandomColorPositionLow ) {

  /* Setup */
  // Done automatically
  color_table[ 0 ] = expected_non_random_color;

  /* Stimulus */
  color_table.setRandomColor( 255, 0 );

  /* Comparison */
  EXPECT_EQ( expected_non_random_color == color_table[ 0 ], false );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, setsRandomColorPositionHigh ) {

  /* Setup */
  // Done automatically
  color_table[ 12 ] = expected_non_random_color;

  /* Stimulus */
  color_table.setRandomColor( 255, 12 );

  /* Comparison */
  EXPECT_EQ( expected_non_random_color == color_table[ 12 ], false );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, doesNotSetRandomColorPositionTooLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.setRandomColor( 255, -1 );

  /* Comparison */
  EXPECT_EQ( expected_error_color == color_table[ -1 ], true );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, doesNotSetRandomColorPositionTooLowVeryLow ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.setRandomColor( 255, -1000000 );

  /* Comparison */
  EXPECT_EQ( expected_error_color == color_table[ -1000000 ], true );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, doesNotSetRandomColorPositionTooHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.setRandomColor( 255, 13 );

  /* Comparison */
  EXPECT_EQ( expected_error_color == color_table[ 13 ], true );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, doesNotSetRandomColorPositionTooHighVeryHigh ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table.setRandomColor( 255, 13000000 );

  /* Comparison */
  EXPECT_EQ( expected_error_color == color_table[ 13000000 ], true );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, setRandomColorDoesNotCallSrand ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table[ 3 ] = expected_non_random_color;
  color_table[ 4 ] = expected_non_random_color;
  color_table[ 5 ] = expected_non_random_color;

  color_table.setRandomColor( 255, 3 );
  color_table.setRandomColor( 255, 4 );
  color_table.setRandomColor( 255, 5 );

  /* Comparison */
  EXPECT_NE( color_table[ 3 ].getRed( ), color_table[ 4 ].getRed( ) );
  EXPECT_NE( color_table[ 3 ].getRed( ), color_table[ 5 ].getRed( ) );
  EXPECT_NE( color_table[ 3 ].getGreen( ), color_table[ 4 ].getGreen( ) );
  EXPECT_NE( color_table[ 3 ].getGreen( ), color_table[ 5 ].getGreen( ) );
  EXPECT_NE( color_table[ 3 ].getBlue( ), color_table[ 4 ].getBlue( ) );
  EXPECT_NE( color_table[ 3 ].getBlue( ), color_table[ 5 ].getBlue( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorTableRandomTest, setRandomColorSetsEachChannelSeparately ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  color_table[ 3 ] = Color( 1, 1, 1 );
  color_table.setRandomColor( 255, 3 );

  /* Comparison */
  EXPECT_NE( ( ( color_table[ 3 ].getRed( ) == color_table[ 3 ].getGreen( ) ) &&
                ( color_table[ 3 ].getRed( ) == color_table[ 3 ].getBlue( ) ) ), true );

  /* Tear-down */
  // Done automatically
}
