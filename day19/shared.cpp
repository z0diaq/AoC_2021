import beacon_scanner;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <unordered_set>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>
#include <ranges>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace beacon_scanner;

Result::Result( )
{

}

void
Result::Init( )
{

}

void
Result::Teardown( )
{
	m_scanners.clear( );
}


std::optional<std::pair<Point, std::vector<Point>>>
FindMatch( const Scanner& scanner1, const Scanner& scanner2, const size_t requiredMatches = 12 )
{
	const auto& points1{ scanner1.GetPoints( ) };
	std::unordered_set<Point, PointHash> pointSet1( points1.begin( ), points1.end( ) );

	// list of points with all rotations
	const auto& rotatedPoints2{ scanner2.GetAllRotations( ) };
	for( size_t rotationNumber = 0; rotationNumber != 24; ++rotationNumber )
	{
		for( const auto& p1 : points1 )
		{
			//try to find match for any point from not rotated scanner with those from rotated
			for( size_t pointNo{ 0 }; pointNo != rotatedPoints2.size( ); ++pointNo )
			{
				const auto offset = p1 - rotatedPoints2[ pointNo ][ rotationNumber ];

				// Transform all points of scanner2
				std::vector<Point> transformed;
				transformed.reserve( rotatedPoints2.size( ) );

				std::ranges::transform( rotatedPoints2, std::back_inserter( transformed ),
					[&offset, rotationNumber]( const std::vector<Point>& p )
					{
						return p[ rotationNumber ] + offset;
					}
				);

				// Count matches
				size_t matches{ 0 };
				std::vector<Point> matchingPoints;

				for( const auto& transformedPoint : transformed )
				{
					if( pointSet1.count( transformedPoint ) )
					{
						++matches;
						matchingPoints.push_back( transformedPoint );
					}
				}

				if( matches >= requiredMatches )
				{
					// Only return points that don't overlap
					std::vector<Point> nonOverlappingPoints;
					for( const auto& p : transformed )
					{
						if( pointSet1.count( p ) == 0 )
							nonOverlappingPoints.push_back( p );
					}

					return std::make_pair( offset, nonOverlappingPoints );  // Only return non-overlapping points!
				}
			}
		}
	}

	return std::nullopt;
}

size_t CountUniqueBeacons( const std::vector<Scanner>& scanners )
{
	std::unordered_set<Point, PointHash> uniqueBeacons;
	std::vector<bool> aligned( scanners.size( ), false );
	std::vector<Point> scannerPositions;
	aligned[ 0 ] = true;

	const auto& first_points = scanners[ 0 ].GetPoints( );
	uniqueBeacons.insert( first_points.begin( ), first_points.end( ) );
	scannerPositions.push_back( Point{ {0,0,0} } );

	// Keep trying to align scanners until all are aligned
	while( std::ranges::find( aligned, false ) != aligned.end( ) )
	{
		for( size_t i = 0; i < scanners.size( ); ++i )
		{
			if( !aligned[ i ] )
			{
				for( size_t j = 0; j < scanners.size( ); ++j )
				{
					if( aligned[ j ] )
					{
						if( auto match = FindMatch( scanners[ j ], scanners[ i ] ) )
						{
							aligned[ i ] = true;
							scannerPositions.push_back( match->first );

							size_t beforeSize = uniqueBeacons.size( );
							uniqueBeacons.insert( match->second.begin( ), match->second.end( ) );
							size_t afterSize = uniqueBeacons.size( );

							break;
						}
					}
				}
			}
		}
	}

	return uniqueBeacons.size( );
}
