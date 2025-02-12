module;

#include <utility>
#include <cmath>

export module trick_shot:utils;

import :target_area;

export namespace trick_shot
{
	std::pair<int, int> FindMaxHeight( const TargetArea& target );

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

	std::pair<int, int> FindMaxHeight( const TargetArea& target ) {
		const Range rangeX{ target.Bounds( ).first };
		const Range rangeY{ target.Bounds( ).second };

		// Calculate velocity bounds
		const int v_xmax{ rangeX.m_max };
		const int v_ymax{ abs( rangeY.m_min ) };  // Maximum possible upward velocity

		int maxHeight{ 0 };
		int foundResults{ 0 };

		for( int vx{ 1 }; vx <= v_xmax; ++vx )
		{
			for( int vy{ -v_ymax }; vy <= v_ymax; ++vy )
			{
				auto [found, localMaxHeight] = SimulateTrajectory( vx, vy, target );
				if( found )
				{
					++foundResults;
					maxHeight = std::max( maxHeight, localMaxHeight );
				}
			}
		}

		return std::make_pair( maxHeight, foundResults );
	}
}
