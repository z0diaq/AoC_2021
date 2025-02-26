#include <gtest/gtest.h>
#include <algorithm>

import beacon_scanner;

using namespace beacon_scanner;

TEST( PointTest, Equality )
{
	Point p1{ {1, 2, 3} };
	Point p2{ {1, 2, 3} };
	Point p3{ {4, 5, 6} };

	EXPECT_EQ( p1, p2 );
	EXPECT_NE( p1, p3 );
}

TEST( PointTest, Addition )
{
	Point p1{ {1, 2, 3} };
	Point p2{ {4, 5, 6} };
	Point expected{ {5, 7, 9} };

	EXPECT_EQ( p1 + p2, expected );
}

TEST( PointTest, Subtraction )
{
	Point p1{ {5, 7, 9} };
	Point p2{ {1, 2, 3} };
	Point expected{ {4, 5, 6} };

	EXPECT_EQ( p1 - p2, expected );
}

TEST( PointTest, LessThan )
{
	Point p1{ {1, 2, 3} };
	Point p2{ {1, 2, 4} };
	Point p3{ {1, 3, 2} };

	EXPECT_TRUE( p1 < p2 );
	EXPECT_TRUE( p1 < p3 );
	EXPECT_FALSE( p2 < p1 );
}

TEST( PointTest, GenerateRotations ) {
	Point p{ {1, 2, 3} };
	auto rotations = p.GenerateRotations( );

	EXPECT_EQ( rotations.size( ), 24 );

	EXPECT_TRUE( std::find( rotations.begin( ), rotations.end( ), p ) != rotations.end( ) );

	Point r1{ {1, 2, 3} };   // Original
	Point r2{ {1, -3, 2} };  // Rotated
	Point r3{ {-1, -2, 3} }; // Inverted x and y

	EXPECT_TRUE( std::find( rotations.begin( ), rotations.end( ), r1 ) != rotations.end( ) );
	EXPECT_TRUE( std::find( rotations.begin( ), rotations.end( ), r2 ) != rotations.end( ) );
	EXPECT_TRUE( std::find( rotations.begin( ), rotations.end( ), r3 ) != rotations.end( ) );

	std::sort( rotations.begin( ), rotations.end( ) );
	auto duplicate = std::adjacent_find( rotations.begin( ), rotations.end( ) );
	EXPECT_EQ( duplicate, rotations.end( ) );
}

TEST( PointTest, Hash )
{
	Point p1{ {1, 2, 3} };
	Point p2{ {1, 2, 3} };
	Point p3{ {3, 2, 1} };

	PointHash hasher;

	// Same points should have same hash
	EXPECT_EQ( hasher( p1 ), hasher( p2 ) );

	// Different points likely have different hashes (not guaranteed but probable)
	// This is a weak test but better than nothing
	EXPECT_NE( hasher( p1 ), hasher( p3 ) );
}
