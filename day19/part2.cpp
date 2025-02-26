import beacon_scanner;

#include <string>
#include <vector>

using namespace beacon_scanner;

int FindMaxManhattanDistance( const std::vector<Point>& scannerPositions );

void
Result::ProcessTwo( const std::string& data )
{
	ProcessOne( data );
}

std::string
Result::FinishPartTwo( )
{
	const auto scannerPositions{ CountUniqueBeaconsWithScannerPositions( ).second };

	return std::to_string( FindMaxManhattanDistance( scannerPositions ) );
}

int
ManhattanDistance( const Point& p1, const Point& p2 )
{
	return std::abs( p1.m_coords[ 0 ] - p2.m_coords[ 0 ] ) +
		std::abs( p1.m_coords[ 1 ] - p2.m_coords[ 1 ] ) +
		std::abs( p1.m_coords[ 2 ] - p2.m_coords[ 2 ] );
}

// Find the maximum Manhattan distance between any pair of scanners
int
FindMaxManhattanDistance( const std::vector<Point>& scannerPositions )
{
	int maxDistance = 0;

	for( size_t left = 0; left < scannerPositions.size( ); ++left )
	{
		for( size_t right = left + 1; right < scannerPositions.size( ); ++right )
		{
			int distance = ManhattanDistance( scannerPositions[ left ], scannerPositions[ right ] );
			maxDistance = std::max( maxDistance, distance );
		}
	}

	return maxDistance;
}
