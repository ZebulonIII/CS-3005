#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class JuliaMandlebrotShowMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected1 = "julia) Choose to make a Julia set.";
    mExpected2 = "mandelbrot) Choose to make a Mandelbrot set.";

    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpected1;
  std::string mExpected2;
  std::stringstream mOutputStream;
};


TEST_F( JuliaMandlebrotShowMenuTest, displaysMenu ) {

  /* Setup */
  // automatic

  /* Stimulus */
  showMenu( mOutputStream );

  /* Comparison */
  std::size_t found = mOutputStream.str( ).find( mExpected1 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected1 << "' in the menu, but didn't find it.";

  found = mOutputStream.str( ).find( mExpected2 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected2 << "' in the menu, but didn't find it.";

  /* Tear-down */
  // Done automatically
}
