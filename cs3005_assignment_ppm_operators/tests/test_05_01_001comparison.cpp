#include "PPM.h"
#include "PPM.h" // Did you #ifndef your file?

#include "gtest/gtest.h"
#include <fstream>
#include <cstdio>

class PPMComparisonTest : public ::testing::Test {
protected:

  void writeFile( const std::string& filename, int width, int height ) {
    int max_value = 255;
    int i, j, k, v;
    unsigned char c;
    std::ofstream fout( filename, std::ios::binary );
    fout << "P6\n" << width << "\n" << height << "\n" << max_value << "\n";
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
  }


  virtual void SetUp( ) {
    writeFile( "small.ppm", 3, 4 );
    writeFile( "medium.ppm", 5, 6 );
    writeFile( "large.ppm", 7, 8 );
    {
      std::ifstream fin;
      fin.open( "small.ppm", std::ios::binary );
      ASSERT_TRUE( static_cast< bool >( fin ) );
      fin >> ppm_small1;
      fin.close( );
    }
    {
      std::ifstream fin;
      fin.open( "small.ppm", std::ios::binary );
      ASSERT_TRUE( static_cast< bool >( fin ) );
      fin >> ppm_small2;
      fin.close( );
    }

    {
      std::ifstream fin;
      fin.open( "medium.ppm", std::ios::binary );
      ASSERT_TRUE( static_cast< bool >( fin ) );
      fin >> ppm_medium1;
      fin.close( );
    }
    {
      std::ifstream fin;
      fin.open( "medium.ppm", std::ios::binary );
      ASSERT_TRUE( static_cast< bool >( fin ) );
      fin >> ppm_medium2;
      fin.close( );
    }

    {
      std::ifstream fin;
      fin.open( "large.ppm", std::ios::binary );
      ASSERT_TRUE( static_cast< bool >( fin ) );
      fin >> ppm_large1;
      fin.close( );
    }
    {
      std::ifstream fin;
      fin.open( "large.ppm", std::ios::binary );
      ASSERT_TRUE( static_cast< bool >( fin ) );
      fin >> ppm_large2;
      fin.close( );
    }
  }

  virtual void TearDown( ) {
    remove( "small.ppm" );
    remove( "medium.ppm" );
    remove( "large.ppm" );
  }

  /* data members */
  PPM ppm_small1, ppm_small2;
  PPM ppm_medium1, ppm_medium2;
  PPM ppm_large1, ppm_large2;
};

TEST_F( PPMComparisonTest, findsEqual ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_medium1 == ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotEqual ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, ppm_medium1 == ppm_small2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotEqual1 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_medium1 != ppm_small2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotEqual2 ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_small1 != ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotNotEqual ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, ppm_medium1 != ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsLessThan ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_small1 < ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotLessThan ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, ppm_large1 < ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsGreaterThan ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_large1 > ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotGreaterThan ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, ppm_small1 > ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsLessThanOrEqualToLess ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_small1 <= ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsLessThanOrEqualToEqual ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_medium1 <= ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotLessThanOrEqualTo ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, ppm_large1 <= ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsGreaterThanOrEqualToGreater ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_large1 >= ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsGreaterThanOrEqualToEqual ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( true, ppm_medium1 >= ppm_medium2 );

  /* Tear-down */
  // Done automatically
}

TEST_F( PPMComparisonTest, findsNotGreaterThanOrEqualTo ) {

  /* Setup */
  // Done automatically

  /* Stimulus */
  // Done automatically

  /* Comparison */
  EXPECT_EQ( false, ppm_small1 >= ppm_medium2 );

  /* Tear-down */
  // Done automatically
}
