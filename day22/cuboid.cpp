module;

#include <optional>

module reactor_reboot:cuboid;

using reactor_reboot::Cuboid;

[[nodiscard]] int64_t
Cuboid::volume( ) const
{
	return m_xRange.volume( ) * m_yRange.volume( ) * m_zRange.volume( );
}

[[nodiscard]] bool
Cuboid::intersects( const Cuboid& other ) const
{
	return m_xRange.intersects( other.m_xRange )
		&& m_yRange.intersects( other.m_yRange )
		&& m_zRange.intersects( other.m_zRange );
}

[[nodiscard]] std::optional<Cuboid>
Cuboid::intersection( const Cuboid& other ) const
{
	auto xIntersection{ m_xRange.intersection( other.m_xRange ) };
	auto yIntersection{ m_yRange.intersection( other.m_yRange ) };
	auto zIntersection{ m_zRange.intersection( other.m_zRange ) };

	if( !xIntersection || !yIntersection || !zIntersection )
		return std::nullopt;

	return Cuboid{ *xIntersection, *yIntersection, *zIntersection };
}

[[nodiscard]] std::vector<Cuboid>
Cuboid::subtract( const Cuboid& other ) const
{
	auto overlap = intersection( other );
	if( !overlap )
		return { *this };  // No overlap, return the original cuboid

	std::vector<Cuboid> result;

	// Left part (along x-axis)
	if( m_xRange.m_min < overlap->m_xRange.m_min )
	{
		result.push_back( Cuboid{
			Range{m_xRange.m_min, overlap->m_xRange.m_min - 1},
			m_yRange,
			m_zRange
			} );
	}

	// Right part (along x-axis)
	if( m_xRange.m_max > overlap->m_xRange.m_max )
	{
		result.push_back( Cuboid{
			Range{overlap->m_xRange.m_max + 1, m_xRange.m_max},
			m_yRange,
			m_zRange
			} );
	}

	// Bottom part (along y-axis, only within the x-overlap)
	if( m_yRange.m_min < overlap->m_yRange.m_min )
	{
		result.push_back( Cuboid{
			overlap->m_xRange,
			Range{m_yRange.m_min, overlap->m_yRange.m_min - 1},
			m_zRange
			} );
	}

	// Top part (along y-axis, only within the x-overlap)
	if( m_yRange.m_max > overlap->m_yRange.m_max )
	{
		result.push_back( Cuboid{
			overlap->m_xRange,
			Range{overlap->m_yRange.m_max + 1, m_yRange.m_max},
			m_zRange
			} );
	}

	// Front part (along z-axis, only within the x-y-overlap)
	if( m_zRange.m_min < overlap->m_zRange.m_min )
	{
		result.push_back( Cuboid{
			overlap->m_xRange,
			overlap->m_yRange,
			Range{m_zRange.m_min, overlap->m_zRange.m_min - 1}
			} );
	}

	// Back part (along z-axis, only within the x-y-overlap)
	if( m_zRange.m_max > overlap->m_zRange.m_max )
	{
		result.push_back( Cuboid{
			overlap->m_xRange,
			overlap->m_yRange,
			Range{overlap->m_zRange.m_max + 1, m_zRange.m_max}
			} );
	}

	return result;
}
