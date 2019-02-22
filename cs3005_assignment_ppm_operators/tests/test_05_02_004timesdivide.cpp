#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class PPMTimesDivideTest : public ::testing::Test {
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

    /* *2.0 */
    ppm_product_a.setWidth( 1 );
    ppm_product_a.setHeight( 1 );
    ppm_product_a.setMaxColorValue( 255 );
    ppm_product_a.setChannel( 0, 0, 0, 200 );
    ppm_product_a.setChannel( 0, 0, 1, 255 );
    ppm_product_a.setChannel( 0, 0, 2, 255 );

    /* *-0.01 */
    ppm_product_b.setWidth( 1 );
    ppm_product_b.setHeight( 1 );
    ppm_product_b.setMaxColorValue( 255 );
    ppm_product_b.setChannel( 0, 0, 0, 0 );
    ppm_product_b.setChannel( 0, 0, 1, 0 );
    ppm_product_b.setChannel( 0, 0, 2, 0 );

    /* /0.5 */
    ppm_quotient_a.setWidth( 1 );
    ppm_quotient_a.setHeight( 1 );
    ppm_quotient_a.setMaxColorValue( 255 );
    ppm_quotient_a.setChannel( 0, 0, 0, 200 );
    ppm_quotient_a.setChannel( 0, 0, 1, 255 );
    ppm_quotient_a.setChannel( 0, 0, 2, 255 );

    /* /-100. */
    ppm_quotient_b.setWidth( 1 );
    ppm_quotient_b.setHeight( 1 );
    ppm_quotient_b.setMaxColorValue( 255 );
    ppm_quotient_b.setChannel( 0, 0, 0, 0 );
    ppm_quotient_b.setChannel( 0, 0, 1, 0 );
    ppm_quotient_b.setChannel( 0, 0, 2, 0 );
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
  PPM ppm_a, ppm_b;
  PPM ppm_product_a, ppm_product_b;
  PPM ppm_quotient_a, ppm_quotient_b;
};

TEST_F( PPMTimesDivideTest, timesDoesNotModifyLHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  PPM ppm_result;
  ppm_result = ppm_a * 2.0;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_a, ppm_a ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, timesDoesNotModifyRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = 2.0;
  PPM ppm_result;
  ppm_result = ppm_a * rhs;

  /* Comparison */
  EXPECT_EQ( 2.0, rhs );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, timesReturnsResult ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  PPM ppm_result;
  ppm_result = ppm_a * 2.0;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_product_a, ppm_result ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, timesRecievesConstLHSAndRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const double rhs = 2.0;
  PPM ppm_result;
  ppm_result = copy_a * rhs;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_product_a, ppm_result ) );
  EXPECT_EQ( true, identical_pixels( ppm_a, copy_a ) );
  EXPECT_EQ( 2.0, rhs );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, timesDoesNotExceedMaximumValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = 2.0;
  PPM ppm_result = ppm_a * rhs;

  /* Comparison */
  EXPECT_EQ( ppm_product_a.getChannel( 0, 0, 1 ), ppm_result.getChannel( 0, 0, 1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, timesDoesNotPassMinimumValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = -0.01;
  PPM ppm_result = ppm_b * rhs;

  /* Comparison */
  EXPECT_EQ( ppm_product_b.getChannel( 0, 0, 0 ), ppm_result.getChannel( 0, 0, 0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, timesMultipliesByFractionalValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = 0.5;
  PPM ppm_result = ppm_b * rhs;

  /* Comparison */
  EXPECT_EQ( 75, ppm_result.getChannel( 0, 0, 0 ) );

  /* Tear-down */
  // Done automatically
}






TEST_F( PPMTimesDivideTest, divideDoesNotModifyLHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  PPM ppm_result;
  ppm_result = ppm_a / 0.5;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_a, ppm_a ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, divideDoesNotModifyRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = 0.5;
  PPM ppm_result;
  ppm_result = ppm_a / rhs;

  /* Comparison */
  EXPECT_EQ( 0.5, rhs );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, divideReturnsResult ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  PPM ppm_result;
  ppm_result = ppm_a / 0.5;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_quotient_a, ppm_result ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, divideRecievesConstLHSAndRHS ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const double rhs = 0.5;
  PPM ppm_result;
  ppm_result = copy_a / rhs;

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_quotient_a, ppm_result ) );
  EXPECT_EQ( true, identical_pixels( ppm_a, copy_a ) );
  EXPECT_EQ( 0.5, rhs );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, divideDoesNotExceedMaximumValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = 0.5;
  PPM ppm_result = ppm_a / rhs;

  /* Comparison */
  EXPECT_EQ( ppm_quotient_a.getChannel( 0, 0, 1 ), ppm_result.getChannel( 0, 0, 1 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, divideDoesNotPassMinimumValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = -100.0;
  PPM ppm_result = ppm_b / rhs;

  /* Comparison */
  EXPECT_EQ( ppm_quotient_b.getChannel( 0, 0, 0 ), ppm_result.getChannel( 0, 0, 0 ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMTimesDivideTest, divideDividesByFractionalValue ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const double rhs = 0.5;
  PPM ppm_result = ppm_b / rhs;

  /* Comparison */
  EXPECT_EQ( 160, ppm_result.getChannel( 0, 0, 1 ) );

  /* Tear-down */
  // Done automatically
}
