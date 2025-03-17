module;

#include <optional>
#include <tuple>

module reactor_reboot:cuboid;

using reactor_reboot::Cuboid;

[[nodiscard]] size_t
Cuboid::volume( ) const
{
	return m_ranges[ X ].volume( ) * m_ranges[ Y ].volume( ) * m_ranges[ Z ].volume( );
}

[[nodiscard]] bool
Cuboid::intersects( const Cuboid& other ) const
{
	return m_ranges[ X ].intersects( other.m_ranges[ X ] )
		&& m_ranges[ Y ].intersects( other.m_ranges[ Y ] )
		&& m_ranges[ Z ].intersects( other.m_ranges[ Z ] );
}

[[nodiscard]] std::optional<Cuboid>
Cuboid::intersection( const Cuboid& other ) const
{
	auto xIntersection{ m_ranges[ X ].intersection( other.m_ranges[ X ] ) };
	auto yIntersection{ m_ranges[ Y ].intersection( other.m_ranges[ Y ] ) };
	auto zIntersection{ m_ranges[ Z ].intersection( other.m_ranges[ Z ] ) };

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
	if( m_ranges[ X ].m_min < overlap->m_ranges[ X ].m_min )
	{
		result.push_back( Cuboid{
			Range{m_ranges[ X ].m_min, overlap->m_ranges[ X ].m_min},
			m_ranges[ Y ],
			m_ranges[ Z ]
			} );
	}

	// Right part (along x-axis)
	if( m_ranges[ X ].m_max > overlap->m_ranges[ X ].m_max )
	{
		result.push_back( Cuboid{
			Range{overlap->m_ranges[ X ].m_max, m_ranges[ X ].m_max},
			m_ranges[ Y ],
			m_ranges[ Z ]
			} );
	}

	// Bottom part (along y-axis, only within the x-overlap)
	if( m_ranges[ Y ].m_min < overlap->m_ranges[ Y ].m_min )
	{
		result.push_back( Cuboid{
			overlap->m_ranges[ X ],
			Range{m_ranges[ Y ].m_min, overlap->m_ranges[ Y ].m_min},
			m_ranges[ Z ]
			} );
	}

	// Top part (along y-axis, only within the x-overlap)
	if( m_ranges[ Y ].m_max > overlap->m_ranges[ Y ].m_max )
	{
		result.push_back( Cuboid{
			overlap->m_ranges[ X ],
			Range{overlap->m_ranges[ Y ].m_max, m_ranges[ Y ].m_max},
			m_ranges[ Z ]
			} );
	}

	// Front part (along z-axis, only within the x-y-overlap)
	if( m_ranges[ Z ].m_min < overlap->m_ranges[ Z ].m_min )
	{
		result.push_back( Cuboid{
			overlap->m_ranges[ X ],
			overlap->m_ranges[ Y ],
			Range{m_ranges[ Z ].m_min, overlap->m_ranges[ Z ].m_min}
			} );
	}

	// Back part (along z-axis, only within the x-y-overlap)
	if( m_ranges[ Z ].m_max > overlap->m_ranges[ Z ].m_max )
	{
		result.push_back( Cuboid{
			overlap->m_ranges[ X ],
			overlap->m_ranges[ Y ],
			Range{overlap->m_ranges[ Z ].m_max, m_ranges[ Z ].m_max}
			} );
	}

	return result;
}

[[nodiscard]] bool
Cuboid::operator==( const Cuboid& _rhs ) const
{
	return std::tie( m_ranges[ X ], m_ranges[ Y ], m_ranges[ Z ] ) == std::tie( _rhs.m_ranges[ X ], _rhs.m_ranges[ Y ], _rhs.m_ranges[ Z ] );
}
