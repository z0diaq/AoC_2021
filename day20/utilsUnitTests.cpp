import trench_map;

using namespace trench_map;

#include <string>
#include <vector>
#include <bitset>

#include <gtest/gtest.h>

extern unsigned long Area3x3( const LitPixelsSet& _image, const std::string& _algorithm, const Bounds& _bounds, const bool _isInfiniteLit, const int _column, const int _row );

// Helper function to create a test image
LitPixelsSet createImage( const std::vector<std::string>& imageRows )
{
	LitPixelsSet result;

	for( size_t y = 0; y < imageRows.size( ); ++y )
	{
		for( size_t x = 0; x < imageRows[ y ].length( ); ++x )
		{
			if( imageRows[ y ][ x ] == '#' )
				result.insert( { static_cast< int >( x ), static_cast< int >( y ) } );
		}
	}

	return result;
}

// Test fixture for Area3x3 tests
class Area3x3Test : public ::testing::Test {
protected:
	// Example from AoC Day 20
	std::vector<std::string> exampleImage =
	{
		"#..#.",
		"#....",
		"##..#",
		"..#..",
		"..###"
	};

	LitPixelsSet litPixels;
	Bounds bounds;
	std::string algorithm;

	void SetUp( ) override
	{
		litPixels = createImage( exampleImage );

		// Set bounds (example image is 5x5)
		bounds.m_minX = 0;
		bounds.m_maxX = 5;
		bounds.m_minY = 0;
		bounds.m_maxY = 5;

		// Example enhancement algorithm (first 20 chars shown)
		algorithm =
			"..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..##"
			"#..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###"
			".######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#."
			".#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#....."
			".#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.."
			"...####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#....."
			"..##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#";
	}
};


TEST_F( Area3x3Test, CenterPixel )
{
	// Center pixel at (2,2) has the following 3x3 neighborhood in the example:
	// #..
	// .#.
	// #..
	// Which should convert to binary 100010100 = decimal 276 (MSB first)

	int column = 2;
	int row = 2;
	bool infiniteIsLit = false;

	unsigned long result = Area3x3( litPixels, algorithm, bounds, infiniteIsLit, column, row );
	EXPECT_EQ( result, 34 );
}
