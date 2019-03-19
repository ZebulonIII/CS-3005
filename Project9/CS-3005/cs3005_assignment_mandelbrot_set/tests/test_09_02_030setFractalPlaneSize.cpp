#include "image_menu.h"
#include "image_menu.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>

class ComplexFractalSetFractalPlaneSizeTest : public ::testing::Test {
protected:

  virtual void SetUp( ) {
    mExpectedOutput = "";
    mInputStream.str( "" );
    mOutputStream.str( "" );
  }

  virtual void TearDown( ) {
  }

  /* data members */
  std::string mExpectedOutput;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
};



TEST_F( ComplexFractalSetFractalPlaneSizeTest, setsJuliaSetPlaneSize ) {

  /* Setup */
  JuliaSet js;
  js.setPlaneSize( -1.9, 1.8, -1.7, 1.6 );
  mInputStream.str( "1.1 -1.2 -1.3 1.4" );
  mExpectedOutput = "Min X? Max X? Min Y? Max Y? ";

  /* Stimulus */
  setFractalPlaneSize( mInputStream, mOutputStream, js );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( -1.2, js_const.getMinX( ) );
  EXPECT_EQ(  1.1, js_const.getMaxX( ) );
  EXPECT_EQ( -1.3, js_const.getMinY( ) );
  EXPECT_EQ(  1.4, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( ComplexFractalSetFractalPlaneSizeTest, setsJuliaSetPlaneSize2 ) {

  /* Setup */
  JuliaSet js;
  js.setPlaneSize( -1.9, 1.8, -1.7, 1.6 );
  mInputStream.str( "-1.1 1.2 1.3 -1.4" );
  mExpectedOutput = "Min X? Max X? Min Y? Max Y? ";

  /* Stimulus */
  setFractalPlaneSize( mInputStream, mOutputStream, js );
  const JuliaSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( -1.1, js_const.getMinX( ) );
  EXPECT_EQ(  1.2, js_const.getMaxX( ) );
  EXPECT_EQ( -1.4, js_const.getMinY( ) );
  EXPECT_EQ(  1.3, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( ComplexFractalSetFractalPlaneSizeTest, setsMandelbrotSetPlaneSize ) {

  /* Setup */
  MandelbrotSet js;
  js.setPlaneSize( -1.9, 1.8, -1.7, 1.6 );
  mInputStream.str( "1.1 -1.2 -1.3 1.4" );
  mExpectedOutput = "Min X? Max X? Min Y? Max Y? ";

  /* Stimulus */
  setFractalPlaneSize( mInputStream, mOutputStream, js );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( -1.2, js_const.getMinX( ) );
  EXPECT_EQ(  1.1, js_const.getMaxX( ) );
  EXPECT_EQ( -1.3, js_const.getMinY( ) );
  EXPECT_EQ(  1.4, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}


TEST_F( ComplexFractalSetFractalPlaneSizeTest, setsMandelbrotSetPlaneSize2 ) {

  /* Setup */
  MandelbrotSet js;
  js.setPlaneSize( -1.9, 1.8, -1.7, 1.6 );
  mInputStream.str( "-1.1 1.2 1.3 -1.4" );
  mExpectedOutput = "Min X? Max X? Min Y? Max Y? ";

  /* Stimulus */
  setFractalPlaneSize( mInputStream, mOutputStream, js );
  const MandelbrotSet& js_const = js;

  /* Comparison */
  EXPECT_EQ( mExpectedOutput, mOutputStream.str( ) );
  EXPECT_EQ( -1.1, js_const.getMinX( ) );
  EXPECT_EQ(  1.2, js_const.getMaxX( ) );
  EXPECT_EQ( -1.4, js_const.getMinY( ) );
  EXPECT_EQ(  1.3, js_const.getMaxY( ) );

  /* Tear-down */
  // Done automatically
}
