#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class plusAndMinusEqualsFunctionsTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mPrompt = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );

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

    //
    ppm_sum.setWidth( 2 );
    ppm_sum.setHeight( 2 );
    ppm_sum.setMaxColorValue( 255 );
    ppm_sum.setChannel( 0, 0, 0, 250 );
    ppm_sum.setChannel( 0, 0, 1, 230 );
    ppm_sum.setChannel( 0, 0, 2, 255 );

    ppm_sum.setChannel( 0, 1, 0, 255 );
    ppm_sum.setChannel( 0, 1, 1, 249 );
    ppm_sum.setChannel( 0, 1, 2, 201 );

    ppm_sum.setChannel( 1, 0, 0, 150 );
    ppm_sum.setChannel( 1, 0, 1, 250 );
    ppm_sum.setChannel( 1, 0, 2, 255 );

    ppm_sum.setChannel( 1, 1, 0, 255 );
    ppm_sum.setChannel( 1, 1, 1, 255 );
    ppm_sum.setChannel( 1, 1, 2, 255 );

    //
    ppm_diff.setWidth( 2 );
    ppm_diff.setHeight( 2 );
    ppm_diff.setMaxColorValue( 255 );
    ppm_diff.setChannel( 0, 0, 0, 0 );
    ppm_diff.setChannel( 0, 0, 1, 70 );
    ppm_diff.setChannel( 0, 0, 2, 99 );

    ppm_diff.setChannel( 0, 1, 0, 100 );
    ppm_diff.setChannel( 0, 1, 1,  51 );
    ppm_diff.setChannel( 0, 1, 2,   0 );

    ppm_diff.setChannel( 1, 0, 0,   0 );
    ppm_diff.setChannel( 1, 0, 1,  50 );
    ppm_diff.setChannel( 1, 0, 2, 205 );

    ppm_diff.setChannel( 1, 1, 0,   0 );
    ppm_diff.setChannel( 1, 1, 1,   0 );
    ppm_diff.setChannel( 1, 1, 2,   0 );

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
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  PPM ppm_a, ppm_b, ppm_sum, ppm_diff;
};


TEST_F( plusAndMinusEqualsFunctionsTest, plusEqualsDoesNotModifySrc2Parameter ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM& a = ppm_a;
  const PPM& b = ppm_b;
  plusEquals( mInputStream, mOutputStream, a, b );

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_b, ppm_b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( plusAndMinusEqualsFunctionsTest, plusEqualsDoesModifySrc1Parameter ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM& a = ppm_a;
  const PPM& b = ppm_b;
  plusEquals( mInputStream, mOutputStream, a, b );

  /* Comparison */
  EXPECT_EQ( false, identical_pixels( copy_a, ppm_a, false ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( plusAndMinusEqualsFunctionsTest, plusEqualsSetsCorrectResult ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM& a = ppm_a;
  const PPM& b = ppm_b;
  plusEquals( mInputStream, mOutputStream, a, b );

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_sum, ppm_a ) );

  /* Tear-down */
  // Done automatically
}




TEST_F( plusAndMinusEqualsFunctionsTest, minusEqualsDoesNotModifySrc2Parameter ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM& a = ppm_a;
  const PPM& b = ppm_b;
  minusEquals( mInputStream, mOutputStream, a, b );

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( copy_b, ppm_b ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( plusAndMinusEqualsFunctionsTest, minusEqualsDoesModifySrc1Parameter ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM& a = ppm_a;
  const PPM& b = ppm_b;
  minusEquals( mInputStream, mOutputStream, a, b );

  /* Comparison */
  EXPECT_EQ( false, identical_pixels( copy_a, ppm_a, false ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( plusAndMinusEqualsFunctionsTest, minusEqualsSetsCorrectResult ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  const PPM copy_a = ppm_a;
  const PPM copy_b = ppm_b;
  PPM& a = ppm_a;
  const PPM& b = ppm_b;
  minusEquals( mInputStream, mOutputStream, a, b );

  /* Comparison */
  EXPECT_EQ( true, identical_pixels( ppm_diff, ppm_a ) );

  /* Tear-down */
  // Done automatically
}
