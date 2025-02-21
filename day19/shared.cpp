import beacon_scanner;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <optional>

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

}


std::optional<std::pair<Point, std::vector<Point>>>
FindMatch( const Scanner& scanner1, const Scanner& scanner2, size_t requiredMatches = 12 )
{
	const auto& points1 = scanner1.GetPoints( );

	// Try each rotation of scanner2
	for( const auto& rotated_points2 : scanner2.GetAllRotations( ) )
	{
		// Try each pair of points as potential matches
		for( const auto& p1 : points1 )
		{
			for( const auto& p2 : rotated_points2 )
			{
				// Calculate offset between these points
				auto offset = p1 - p2;

				// Transform all points of scanner2 by this offset
				std::vector<Point> transformed;
				std::ranges::transform( rotated_points2, std::back_inserter( transformed ),
					[&offset]( const Point& p ) { return p + offset; } );

				// Count matches
				size_t matches = std::ranges::count_if( transformed,
					[&points1]( const Point& p ) {
						return std::find( points1.begin( ), points1.end( ), p ) != points1.end( );
					} );

				if( matches >= requiredMatches )
					return std::make_pair( offset, transformed );
			}
		}
	}

	return std::nullopt;
}

