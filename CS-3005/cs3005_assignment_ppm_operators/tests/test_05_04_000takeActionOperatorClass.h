#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cmath>

class takeActionOperatorTest : public ::testing::Test {
protected:

  void setSourcePPM( int height, int width, int max_color_value, int red, int green, int blue ) {
    // save values
    mHeight = height;
    mWidth = width;
    mMaxColorValue = max_color_value;
    mRed = red;
    mGreen = green;
    mBlue = blue;
    mExpectedColorimetricValues.resize( mHeight * mWidth );

    // configure PPM
    mPPM.setHeight( height );
    mPPM.setWidth( width );
    mPPM.setMaxColorValue( max_color_value );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        red = ( red + 2 ) % ( max_color_value + 1 );
        green = ( green + 3 ) % ( max_color_value + 1 );
        blue = ( blue + 7 ) % ( max_color_value + 1 );
        mPPM.setPixel( row, column, red, green, blue );
        mExpectedColorimetricValues[ row*mWidth + column ] = 0.2126*red + 0.7152*green + 0.0722*blue;
      }
    }
  }

  void clearDestinationPPM( ) {
    mFilteredPPM.setHeight( 0 );
    mFilteredPPM.setWidth( 0 );
    mFilteredPPM.setMaxColorValue( 0 );
  }

  void compareLinearColorimetricValues( ) {
    const PPM& ppm_orig_const = mPPM;

    int row, column, channel;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        for( channel = 0; channel < 3; channel++ ) {
          EXPECT_NEAR( mExpectedColorimetricValues[ row*mWidth+column ], ppm_orig_const.linearColorimetricPixelValue( row, column ), 0.001 )
            << "row: " << row << "  column: " << column;
        }
      }
    }
  }

  virtual bool identical_ppms( const PPM& expected, const PPM& actual, bool show_error=true ) {

    EXPECT_EQ( expected.getHeight( ), actual.getHeight( ) );
    EXPECT_EQ( expected.getWidth( ), actual.getWidth( ) );
    EXPECT_EQ( expected.getMaxColorValue( ), actual.getMaxColorValue( ) );

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

  void compareGrayPixels( int expected_channel ) {
    const PPM& ppm_orig_const = mPPM;
    const PPM& ppm_gray_const = mFilteredPPM;

    int row, column, channel;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        for( channel = 0; channel < 3; channel++ ) {
          EXPECT_EQ( ppm_orig_const.getChannel( row, column, expected_channel ), ppm_gray_const.getChannel( row, column, channel ) )
            << "row: " << row << "  column: " << column << "  channel: " << channel;
        }
      }
    }
  }


  void writeFile( const std::string& filename ) {
    int width = 13;
    int height = 7;
    int max_value = 255;
    int i, j, k, v;
    unsigned char c;
    std::ofstream fout( filename, std::ios::binary );
    fout << "P6 " << width << " " << height << " " << max_value << "\n";
    for ( i = 0; i < height ; i++ ) {
      for ( j = 0; j < width ; j++ ) {
        for ( k = 0; k < 3 ; k++ ) {
          v = ( ( i * width + j ) * 3 + k ) % ( max_value + 1 );
          c = ( unsigned char )v;
          fout.write( (char *)&c, 1 );
        }
      }
    }
    fout.close();
    expected_width = width;
    expected_height = height;
    expected_max_color_value = max_value;
  }

  void readFile( const std::string& filename, PPM& ppm ) {
    std::ifstream fin( filename, std::ios::binary );
    unsigned char new_line;
    int width, height, mcv;
    std::string magic;
    fin >> magic >> width >> height >> mcv;
    EXPECT_EQ( "P6", magic );
    EXPECT_LT( 0, height );
    EXPECT_LT( 0, width );
    EXPECT_LE( 0, mcv );
    EXPECT_GE( 255, mcv );

    fin.read( (char *)&new_line, 1 );
    EXPECT_EQ( '\n', (int)new_line );
    ppm.setHeight( height );
    ppm.setWidth( width );
    ppm.setMaxColorValue( mcv );

    int row, column, channel;
    unsigned char v;
    for ( row = 0; row < height ; row++ ) {
      for ( column = 0; column < width ; column++ ) {
        for ( channel = 0; channel < 3 ; channel++ ) {
          fin.read( (char*)&v, 1 );
          EXPECT_LE( 0, ( int )v );
          EXPECT_GE( mcv, ( int )v );
          ppm.setChannel( row, column, channel, ( int ) v );
        }
      }
    }
    fin.close();
  }


  virtual void SetUp( ) {
    mHeight = 35;
    mWidth = 45;
    input_image1.setHeight( mHeight );
    input_image1.setWidth( mWidth );
    input_image1.setMaxColorValue( 137 );
    int row, column;
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        input_image1.setPixel( row, column, 100, 101, 102 );
      }
    }

    input_image2.setHeight( mHeight );
    input_image2.setWidth( mWidth );
    input_image2.setMaxColorValue( 200 );
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        input_image2.setPixel( row, column, 10, 20, (row*column)%201 );
      }
    }

    mPlusPPM.setHeight( mHeight );
    mPlusPPM.setWidth( mWidth );
    mPlusPPM.setMaxColorValue( 137 );
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        mPlusPPM.setPixel( row, column, 110, 121, std::min(137, 102+(row*column)%201) );
      }
    }

    mMinusPPM.setHeight( mHeight );
    mMinusPPM.setWidth( mWidth );
    mMinusPPM.setMaxColorValue( 137 );
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        mMinusPPM.setPixel( row, column, 90, 81, std::max(0, 102-(row*column)%201) );
      }
    }

    mTimesPPM.setHeight( mHeight );
    mTimesPPM.setWidth( mWidth );
    mTimesPPM.setMaxColorValue( 137 );
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        mTimesPPM.setPixel( row, column, 50, 50, 51 );
      }
    }

    mDividePPM.setHeight( mHeight );
    mDividePPM.setWidth( mWidth );
    mDividePPM.setMaxColorValue( 137 );
    for( row = 0; row < mHeight; row++ ) {
      for( column = 0; column < mWidth; column++ ) {
        mDividePPM.setPixel( row, column, 33, 33, 34 );
      }
    }

  }

  virtual void TearDown( ) {
    mPPM.setHeight( 0 );
    mFilteredPPM.setHeight( 0 );
    input_image1.setHeight( 0 );
    input_image2.setHeight( 0 );
    output_image.setHeight( 0 );
  }

  /* data members */
  std::string mPrompt;
  std::stringstream mInputStream;
  std::stringstream mOutputStream;
  std::string mExpectedOutput;
  std::string mChoice;
  PPM input_image1, input_image2, output_image;
  int mRed, mGreen, mBlue;
  int mHeight, mWidth, mMaxColorValue;
  std::vector< double > mExpectedColorimetricValues;

  PPM mPPM;
  PPM mFilteredPPM;
  PPM mPlusPPM;
  PPM mMinusPPM;
  PPM mTimesPPM;
  PPM mDividePPM;
  int expected_height, expected_width, expected_max_color_value;
};
