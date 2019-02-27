#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class timesAndDivideFunctionsTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mInputStream.str( "" );
    mOutputStream.str( "" );
    mExpectedOutput = "";

    //
    ppm_a.setWidth( 2 );
    ppm_a.setHeight( 2 );
    ppm_a.setMaxColorValue( 255 );
    ppm_a.setChannel( 0, 0, 0, 100 );
    ppm_a.setChannel( 0, 0, 1, 150 );
    ppm_a.setChannel( 0, 0, 2, 200 );

    ppm_a.setChannel( 0, 1, 0, 200 );
    ppm_a.setChannel( 0, 1, 1, 150 );
    ppm_a.setChannel( 0, 1, 2, 100 );

    ppm_a.setChannel( 1, 0, 0, 0 );
    ppm_a.setChannel( 1, 0, 1, 150 );
    ppm_a.setChannel( 1, 0, 2, 255 );

    ppm_a.setChannel( 1, 1, 0, 255 );
    ppm_a.setChannel( 1, 1, 1, 255 );
    ppm_a.setChannel( 1, 1, 2, 255 );

    //
    ppm_b.setWidth( 2 );
    ppm_b.setHeight( 2 );
    ppm_b.setMaxColorValue( 255 );
    ppm_b.setChannel( 0, 0, 0, 150 );
    ppm_b.setChannel( 0, 0, 1, 80 );
    ppm_b.setChannel( 0, 0, 2, 101 );

    ppm_b.setChannel( 0, 1, 0, 100 );
    ppm_b.setChannel( 0, 1, 1,  99 );
    ppm_b.setChannel( 0, 1, 2, 101 );

    ppm_b.setChannel( 1, 0, 0, 150 );
    ppm_b.setChannel( 1, 0, 1, 100 );
    ppm_b.setChannel( 1, 0, 2,  50 );

    ppm_b.setChannel( 1, 1, 0, 255 );
    ppm_b.setChannel( 1, 1, 1, 255 );
    ppm_b.setChannel( 1, 1, 2, 255 );

    /* *2.0 */
    ppm_product_a.setWidth( 2 );
    ppm_product_a.setHeight( 2 );
    ppm_product_a.setMaxColorValue( 255 );
    ppm_product_a.setChannel( 0, 0, 0, 200 );
    ppm_product_a.setChannel( 0, 0, 1, 255 );
    ppm_product_a.setChannel( 0, 0, 2, 255 );

    ppm_product_a.setChannel( 0, 1, 0, 255 );
    ppm_product_a.setChannel( 0, 1, 1, 255 );
    ppm_product_a.setChannel( 0, 1, 2, 200 );

    ppm_product_a.setChannel( 1, 0, 0, 0 );
    ppm_product_a.setChannel( 1, 0, 1, 255 );
    ppm_product_a.setChannel( 1, 0, 2, 255 );

    ppm_product_a.setChannel( 1, 1, 0, 255 );
    ppm_product_a.setChannel( 1, 1, 1, 255 );
    ppm_product_a.setChannel( 1, 1, 2, 255 );

    /* *-0.01 */
    ppm_product_b.setWidth( 2 );
    ppm_product_b.setHeight( 2 );
    ppm_product_b.setMaxColorValue( 255 );
    ppm_product_b.setChannel( 0, 0, 0, 0 );
    ppm_product_b.setChannel( 0, 0, 1, 0 );
    ppm_product_b.setChannel( 0, 0, 2, 0 );

    ppm_product_b.setChannel( 0, 1, 0, 0 );
    ppm_product_b.setChannel( 0, 1, 1, 0 );
    ppm_product_b.setChannel( 0, 1, 2, 0 );

    ppm_product_b.setChannel( 1, 0, 0, 0 );
    ppm_product_b.setChannel( 1, 0, 1, 0 );
    ppm_product_b.setChannel( 1, 0, 2, 0 );

    ppm_product_b.setChannel( 1, 1, 0, 0 );
    ppm_product_b.setChannel( 1, 1, 1, 0 );
    ppm_product_b.setChannel( 1, 1, 2, 0 );


    /* /0.5 */
    ppm_quotient_a.setWidth( 2 );
    ppm_quotient_a.setHeight( 2 );
    ppm_quotient_a.setMaxColorValue( 255 );
    ppm_quotient_a.setChannel( 0, 0, 0, 200 );
    ppm_quotient_a.setChannel( 0, 0, 1, 255 );
    ppm_quotient_a.setChannel( 0, 0, 2, 255 );

    ppm_quotient_a.setChannel( 0, 1, 0, 255 );
    ppm_quotient_a.setChannel( 0, 1, 1, 255 );
    ppm_quotient_a.setChannel( 0, 1, 2, 200 );

    ppm_quotient_a.setChannel( 1, 0, 0, 0 );
    ppm_quotient_a.setChannel( 1, 0, 1, 255 );
    ppm_quotient_a.setChannel( 1, 0, 2, 255 );

    ppm_quotient_a.setChannel( 1, 1, 0, 255 );
    ppm_quotient_a.setChannel( 1, 1, 1, 255 );
    ppm_quotient_a.setChannel( 1, 1, 2, 255 );

    ppm_quotient_a.setWidth( 1 );
    ppm_quotient_a.setHeight( 1 );
    ppm_quotient_a.setMaxColorValue( 255 );
    ppm_quotient_a.setChannel( 0, 0, 0, 200 );
    ppm_quotient_a.setChannel( 0, 0, 1, 255 );
    ppm_quotient_a.setChannel( 0, 0, 2, 255 );

    /* /-100. */
    ppm_quotient_b.setWidth( 2 );
    ppm_quotient_b.setHeight( 2 );
    ppm_quotient_b.setMaxColorValue( 255 );
    ppm_quotient_b.setChannel( 0, 0, 0, 0 );
    ppm_quotient_b.setChannel( 0, 0, 1, 0 );
    ppm_quotient_b.setChannel( 0, 0, 2, 0 );

    ppm_quotient_b.setChannel( 0, 1, 0, 0 );
    ppm_quotient_b.setChannel( 0, 1, 1, 0 );
    ppm_quotient_b.setChannel( 0, 1, 2, 0 );

    ppm_quotient_b.setChannel( 1, 0, 0, 0 );
    ppm_quotient_b.setChannel( 1, 0, 1, 0 );
    ppm_quotient_b.setChannel( 1, 0, 2, 0 );

    ppm_quotient_b.setChannel( 1, 1, 0, 0 );
    ppm_quotient_b.setChannel( 1, 1, 1, 0 );
    ppm_quotient_b.setChannel( 1, 1, 2, 0 );

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
  std::string mExpectedOutput;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM ppm_a, ppm_b, ppm_product_a, ppm_product_b, ppm_quotient_a, ppm_quotient_b;
};

TEST_F( timesAndDivideFunctionsTest, timesDoesNotModifySrc1Parameter ) {

  /* Setup */
  mInputStream.str( "2.0" );
  mExpectedOutput = "Factor? ";

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM& a = ppm_a;
  PPM ppm_result;
  times( mInputStream, mOutputStream, a, ppm_result );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( copy_a, ppm_a ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( timesAndDivideFunctionsTest, timesSetsCorrectResultA ) {

  /* Setup */
  mInputStream.str( "2.0" );
  mExpectedOutput = "Factor? ";

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM& a = ppm_a;
  PPM ppm_result = ppm_a;
  times( mInputStream, mOutputStream, a, ppm_result );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( ppm_product_a, ppm_result ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( timesAndDivideFunctionsTest, timesSetsCorrectResultB ) {

  /* Setup */
  mInputStream.str( "-100." );
  mExpectedOutput = "Factor? ";

  /* Stimulus */
  const PPM copy_b = ppm_b;
  const PPM& b = ppm_b;
  PPM ppm_result = ppm_b;
  times( mInputStream, mOutputStream, b, ppm_result );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( ppm_product_b, ppm_result ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( timesAndDivideFunctionsTest, divideDoesNotModifySrc1Parameter ) {

  /* Setup */
  mInputStream.str( "0.5" );
  mExpectedOutput = "Factor? ";

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM& a = ppm_a;
  PPM ppm_result;
  divide( mInputStream, mOutputStream, a, ppm_result );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( copy_a, ppm_a ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( timesAndDivideFunctionsTest, divideSetsCorrectResultA ) {

  /* Setup */
  mInputStream.str( "0.5" );
  mExpectedOutput = "Factor? ";

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM& a = ppm_a;
  PPM ppm_result = ppm_a;
  divide( mInputStream, mOutputStream, a, ppm_result );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( ppm_quotient_a, ppm_result ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( timesAndDivideFunctionsTest, divideSetsCorrectResultB ) {

  /* Setup */
  mInputStream.str( "-100.0" );
  mExpectedOutput = "Factor? ";

  /* Stimulus */
  const PPM copy_b = ppm_b;
  const PPM& b = ppm_b;
  PPM ppm_result = ppm_b;
  divide( mInputStream, mOutputStream, b, ppm_result );

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( true, identical_pixels( ppm_quotient_b, ppm_result ) );

  /* Tear-down */
  // Done automatically
}
