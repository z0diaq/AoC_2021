import beacon_scanner;

#include <algorithm>
#include <stdexcept>
#include <optional>
#include <unordered_set>
#include <vector>
#include <array>
#include <ranges>

using namespace beacon_scanner;

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

std::pair<size_t, std::vector<Point>>
Result::CountUniqueBeaconsWithScannerPositions( ) const
{
	std::vector<bool> aligned( m_scanners.size( ), false );
	std::vector<std::pair<std::vector<Point>, Point>> alignedScanners;
	aligned[ 0 ] = true;

	// Start with the first scanner at origin
	alignedScanners.emplace_back( m_scanners[ 0 ].GetPoints( ), Point{ {0, 0, 0} } );

	// Keep trying to align scanners until all are aligned
	bool found_new_alignment = true;
	while( found_new_alignment )
	{
		found_new_alignment = false;
		for( size_t i = 0; i < m_scanners.size( ); ++i )
		{
			if( !aligned[ i ] )
			{
				for( size_t j = 0; j < alignedScanners.size( ); ++j ) {
					const auto& alignedPoints = alignedScanners[ j ].first;
					Scanner temp_scanner;
					for( const auto& point : alignedPoints )
						temp_scanner.AddPoint( Point{ point.m_coords } );

					if( auto match = FindMatch( temp_scanner, m_scanners[ i ] ) )
					{
						aligned[ i ] = true;
						found_new_alignment = true;

						// Transform all points of scanner i using the match offset
						std::vector<Point> transformedPoints;
						const auto& rotatedPoints = m_scanners[ i ].GetAllRotations( );

						// Find the rotation that gave us the match
						int matchingRotation = -1;
						const auto& offset = match->first;

						// We need to determine which rotation gave us the match
						for( size_t rotationNumber = 0; rotationNumber < 24; ++rotationNumber ) {
							size_t matchCount = 0;
							std::vector<Point> testPoints;

							for( const auto& pointRotations : rotatedPoints ) {
								testPoints.push_back( pointRotations[ rotationNumber ] + offset );
							}

							// Convert alignedPoints to a set for faster lookups
							std::unordered_set<Point, PointHash> alignedSet(
								alignedPoints.begin( ), alignedPoints.end( ) );

							for( const auto& testPoint : testPoints ) {
								if( alignedSet.count( testPoint ) > 0 ) {
									matchCount++;
								}
							}

							if( matchCount >= 12 ) {
								matchingRotation = (int)rotationNumber;
								break;
							}
						}

						if( matchingRotation == -1 ) {
							throw std::runtime_error( "Could not find matching rotation" );
						}

						// Transform all points using the matching rotation
						std::vector<Point> allTransformedPoints;
						for( const auto& pointRotations : rotatedPoints ) {
							allTransformedPoints.push_back(
								pointRotations[ matchingRotation ] + offset );
						}

						// Add the transformed scanner to our list
						alignedScanners.emplace_back( std::move( allTransformedPoints ), offset );
						break;
					}
				}
			}
		}
	}

	// Check if all scanners were aligned
	if( std::ranges::find( aligned, false ) != aligned.end( ) )
		throw std::runtime_error( "Could not align all scanners" );

	// Now collect all unique points
	std::unordered_set<Point, PointHash> uniqueBeacons;
	for( const auto& [points, _] : alignedScanners )
	{
		for( const auto& point : points )
			uniqueBeacons.insert( point );
	}

	std::vector<Point> scannerPositions;
	scannerPositions.reserve( alignedScanners.size( ) );

	for( const auto& [_, position] : alignedScanners )
		scannerPositions.push_back( position );

	return { uniqueBeacons.size( ), scannerPositions };
}
