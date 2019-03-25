#include "ColorTable.h"
#include "ColorTable.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <sstream>
#include <string>

class ColorOutputTest : public ::testing::Test {
protected:
  ColorOutputTest( )
    : color( 13, 17, 19 ) {
  }

  virtual void SetUp( ) {
  }

  virtual void TearDown( ) {
  }

  /* data members */
  Color color;
  std::stringstream mOutputStream;
  std::string mExpectedOutput;
};


TEST_F( ColorOutputTest, correctlyFormats ) {

  /* Setup */
  mExpectedOutput = "13:17:19";

  /* Stimulus */
  mOutputStream << color;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}

TEST_F( ColorOutputTest, correctlyFormatsAnother ) {

  /* Setup */
  color.setRed( 31 );
  color.setGreen( 71 );
  color.setBlue( 91 );
  mExpectedOutput = "31:71:91";

  /* Stimulus */
  mOutputStream << color;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );

  /* Tear-down */
  // Done automatically
}
