import trick_shot;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <regex>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <gtest/gtest.h>

using namespace trick_shot;

void
Result::ProcessOne( const std::string& data )
{
	m_targetAreaDescription = data;
}

struct Point {
	int m_x, m_y;
};

struct Range
{
	int m_min, m_max;

	bool InRange( int value ) const
	{
		return value >= m_min && value <= m_max;
	}
};

// Thread-safe target area representation
class TargetArea {
private:
	Range m_rangeX, m_rangeY;

public:
	TargetArea( int minX, int maxX, int minY, int maxY )
		: m_rangeX{ minX, maxX }, m_rangeY{ minY, maxY } {
	}

	bool Contains( const Point& p ) const {
		return m_rangeX.InRange( p.m_x ) && m_rangeY.InRange( p.m_y );
	}

	auto Bounds( ) const {
		return std::make_pair( m_rangeX, m_rangeY );
	}

	bool Overshoot( const Point& pt ) const
	{
		return pt.m_x > m_rangeX.m_max || pt.m_y < m_rangeY.m_min;
	}
};

int FindMaxHeight( const TargetArea& target );

std::string
Result::FinishPartOne( )
{
	// sample format
	// target area: x=20..30, y=-10..-5
	std::regex pattern( "target area: x=(-?\\d+)\\.\\.(-?\\d+), y=(-?\\d+)\\.\\.(-?\\d+)" );

	std::smatch matches;
	if( !std::regex_match( m_targetAreaDescription, matches, pattern ) ) {
		throw std::invalid_argument( "Invalid format" );
	}

	const int maxHeight{ FindMaxHeight( TargetArea(
		std::stoi( matches[ 1 ].str( ) ),   // minX
		std::stoi( matches[ 2 ].str( ) ),   // maxX
		std::stoi( matches[ 3 ].str( ) ),   // minY
		std::stoi( matches[ 4 ].str( ) )    // maxY
	) ) };

	return std::to_string( maxHeight );
}

std::pair<bool, int> SimulateTrajectory( int vx, int vy, const TargetArea& target ) {
	Point pos{ 0, 0 };
	int max_height = 0;

	while( false == target.Overshoot( pos ) ) {
		pos.m_x += vx;
		pos.m_y += vy;
		max_height = std::max( max_height, pos.m_y );

		// Update velocities
		vx = std::max( 0, vx - 1 );  // Horizontal drag
		vy -= 1;                     // Gravity

		if( target.Contains( pos ) ) {
			return { true, max_height };
		}
	}

	return { false, 0 };
}

int FindMaxHeight( const TargetArea& target ) {
	const Range rangeX{ target.Bounds( ).first };
	const Range rangeY{ target.Bounds( ).second };

	// Calculate velocity bounds
	const int v_xmax{ rangeX.m_max };
	const int v_ymax{ abs( rangeY.m_min ) };  // Maximum possible upward velocity

	int maxHeight{ 0 };

	for( int vx{ 1 }; vx <= v_xmax; ++vx )
	{
		for( int vy{ 1 }; vy <= v_ymax; ++vy )
		{
			auto [found, localMaxHeight] = SimulateTrajectory( vx, vy, target );
			if( found )
				maxHeight = std::max( maxHeight, localMaxHeight );
		}
	}

	return maxHeight;
}

TEST( FindMaxHeight, UseTrainingData )
{
	const int maxHeight = FindMaxHeight( TargetArea( 20, 30, -10, -5 ) );
	ASSERT_EQ( maxHeight, 45 );
}
