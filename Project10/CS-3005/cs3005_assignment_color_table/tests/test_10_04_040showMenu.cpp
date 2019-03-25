#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <string>

class ColorTableShowMenuTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpected1 = "grid-apply-color-table) Use the grid values to set colors in the output image using the color table.";
    mExpected2 = "set-color-table-size) Change the number of slots in the color table.";
    mExpected3 = "set-color) Set the RGB values for one slot in the color table.";
    mExpected4 = "set-random-color) Randomly set the RGB values for one slot in the color table.";
    mExpected5 = "set-color-gradient) Smoothly set the RGB values for a range of slots in the color table.";
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpected1;
  std::string mExpected2;
  std::string mExpected3;
  std::string mExpected4;
  std::string mExpected5;
  std::stringstream mOutputStream;
};


TEST_F( ColorTableShowMenuTest, displaysMenu ) {

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

  found = mOutputStream.str( ).find( mExpected3 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected3 << "' in the menu, but didn't find it.";

  found = mOutputStream.str( ).find( mExpected4 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected4 << "' in the menu, but didn't find it.";

  found = mOutputStream.str( ).find( mExpected5 );
  EXPECT_NE( std::string::npos, found )
    << " Looking for '" << mExpected5 << "' in the menu, but didn't find it.";

  /* Tear-down */
  // Done automatically
}
