#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class PPMPlusMinusTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    ppm_a.setWidth( 1 );
    ppm_a.setHeight( 1 );
    ppm_a.setMaxColorValue( 255 );
    ppm_a.setChannel( 0, 0, 0, 100 );
    ppm_a.setChannel( 0, 0, 1, 150 );
    ppm_a.setChannel( 0, 0, 2, 200 );

    ppm_b.setWidth( 1 );
    ppm_b.setHeight( 1 );
    ppm_b.setMaxColorValue( 255 );
    ppm_b.setChannel( 0, 0, 0, 150 );
    ppm_b.setChannel( 0, 0, 1, 80 );
    ppm_b.setChannel( 0, 0, 2, 101 );

    ppm_sum.setWidth( 1 );
    ppm_sum.setHeight( 1 );
    ppm_sum.setMaxColorValue( 255 );
    ppm_sum.setChannel( 0, 0, 0, 250 );
    ppm_sum.setChannel( 0, 0, 1, 230 );
    ppm_sum.setChannel( 0, 0, 2, 255 );

    ppm_diff.setWidth( 1 );
    ppm_diff.setHeight( 1 );
    ppm_diff.setMaxColorValue( 255 );
    ppm_diff.setChannel( 0, 0, 0, 0 );
    ppm_diff.setChannel( 0, 0, 1, 70 );
    ppm_diff.setChannel( 0, 0, 2, 99 );
  }

  virtual void TearDown( ) {
  }

  virtual bool identical_pixels( const PPM& expected, const PPM& actual, bool show_error=true ) {
    int row, col, chan;
    bool same = true;
    for ( row = 0; row < expected.getHeight( ); row++ ) {
      for ( col = 0; col < expected.getWidth( ); col++ ) {
        for ( chan = 0; chan < 3 ; chan++ ) {
          if ( expected.getChannel( row, col, chan ) != actual.getChannel( row, col, chan ) ) {
            same = false;
            if( show_error ) {
              EXPECT_EQ( expected.getChannel( row, col, chan ), actual.getChannel( row, col, chan ) )
                << " row = " << row << " col = " << col << " chan = " << chan;
            }
          }
        }
      }
    }
    return same;
  }

  /* data members */
  PPM ppm_a, ppm_b, ppm_sum, ppm_diff;
};

TEST_F( PPMPlusMinusTest, plusDoesNotModifyLHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  PPM ppm_result;
  ppm_result = ppm_a + ppm_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_a, ppm_a ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMPlusMinusTest, plusDoesNotModifyRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_b = ppm_b;
  PPM ppm_result;
  ppm_result = ppm_a + ppm_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_b, ppm_b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMPlusMinusTest, plusReturnsResult ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  PPM ppm_result;
  ppm_result = ppm_a + ppm_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_sum, ppm_result ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMPlusMinusTest, plusRecievesConstLHSAndRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM ppm_result;
  ppm_result = copy_a + copy_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_sum, ppm_result ) );
  EXPECT_EQ( true, identical_pixels( ppm_a, copy_a ) );
  EXPECT_EQ( true, identical_pixels( ppm_b, copy_b ) );

  /* Tear-down */
  // Done automatically
}







TEST_F( PPMPlusMinusTest, minusDoesNotModifyLHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  PPM ppm_result;
  ppm_result = ppm_a - ppm_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_a, ppm_a ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMPlusMinusTest, minusDoesNotModifyRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_b = ppm_b;
  PPM ppm_result;
  ppm_result = ppm_a - ppm_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_b, ppm_b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMPlusMinusTest, minusReturnsResult ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  PPM ppm_result;
  ppm_result = ppm_a - ppm_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_diff, ppm_result ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMPlusMinusTest, minusRecievesConstLHSAndRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM ppm_result;
  ppm_result = copy_a - copy_b;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_diff, ppm_result ) );
  EXPECT_EQ( true, identical_pixels( ppm_a, copy_a ) );
  EXPECT_EQ( true, identical_pixels( ppm_b, copy_b ) );

  /* Tear-down */
  // Done automatically
}
