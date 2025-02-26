#include <gtest/gtest.h>
import beacon_scanner;

using namespace beacon_scanner;

extern int ManhattanDistance( const Point& p1, const Point& p2 );

TEST( DistanceTest, ManhattanDistancePositive )
{
	Point p1{ {1, 2, 3} };
	Point p2{ {4, 5, 6} };

	// |4-1| + |5-2| + |6-3| = 3 + 3 + 3 = 9
	EXPECT_EQ( ManhattanDistance( p1, p2 ), 9 );
}

TEST( DistanceTest, ManhattanDistanceNegative )
{
	Point p1{ {-1, -2, -3} };
	Point p2{ {-4, -5, -6} };

	// |-4-(-1)| + |-5-(-2)| + |-6-(-3)| = |-3| + |-3| + |-3| = 9
	EXPECT_EQ( ManhattanDistance( p1, p2 ), 9 );
}

TEST( DistanceTest, ManhattanDistanceMixed )
{
	Point p1{ {-1, 2, -3} };
	Point p2{ {4, -5, 6} };

	// |4-(-1)| + |-5-2| + |6-(-3)| = |5| + |-7| + |9| = 21
	EXPECT_EQ( ManhattanDistance( p1, p2 ), 21 );
}

TEST( DistanceTest, ManhattanDistanceZero )
{
	Point p1{ {0, 0, 0} };
	Point p2{ {0, 0, 0} };

	EXPECT_EQ( ManhattanDistance( p1, p2 ), 0 );
}

TEST( DistanceTest, ManhattanDistanceSymmetry )
{
	Point p1{ {1, 2, 3} };
	Point p2{ {4, 5, 6} };

	// Distance should be the same regardless of order
	EXPECT_EQ( ManhattanDistance( p1, p2 ), ManhattanDistance( p2, p1 ) );
}

TEST( DistanceTest, FindMaxManhattanDistance )
{
	// We need to declare the function as extern
	extern int FindMaxManhattanDistance( const std::vector<Point>&scannerPositions );

	// Create a set of test scanner positions
	std::vector<Point> scanners{
		{{0, 0, 0}},
		{{1200, 1200, 1200}},
		{{-1200, -1200, -1200}},
		{{1200, -1200, 0}}
	};

	// Max should be between (-1200,-1200,-1200) and (1200,1200,1200) = 7200
	EXPECT_EQ( FindMaxManhattanDistance( scanners ), 7200 );
}