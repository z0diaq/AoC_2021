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
	if( !xIntersection ) return std::nullopt; // Early exit

	auto yIntersection{ m_ranges[ Y ].intersection( other.m_ranges[ Y ] ) };
	if( !yIntersection ) return std::nullopt; // Early exit

	auto zIntersection{ m_ranges[ Z ].intersection( other.m_ranges[ Z ] ) };
	if( !zIntersection ) return std::nullopt; // Early exit

	return Cuboid{ *xIntersection, *yIntersection, *zIntersection };
}

[[nodiscard]] std::vector<Cuboid>
Cuboid::subtract( const Cuboid& other ) const
{
	auto overlap = intersection( other );
	if( !overlap )
		return { *this };  // No overlap, return the original cuboid

	std::vector<Cuboid> result;
	result.reserve( 6 ); // Pre-allocate space for maximum possible fragments

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

[[nodiscard]] bool
Cuboid::canMergeWith( const Cuboid& other ) const
{
	// Check if two cuboids can be merged (they must share a face and have identical remaining dimensions)

	// Adjacent along X axis
	bool adjacentX = ( m_ranges[ X ].m_max == other.m_ranges[ X ].m_min ||
		other.m_ranges[ X ].m_max == m_ranges[ X ].m_min ) &&
		m_ranges[ Y ] == other.m_ranges[ Y ] &&
		m_ranges[ Z ] == other.m_ranges[ Z ];

	// Adjacent along Y axis
	bool adjacentY = ( m_ranges[ Y ].m_max == other.m_ranges[ Y ].m_min ||
		other.m_ranges[ Y ].m_max == m_ranges[ Y ].m_min ) &&
		m_ranges[ X ] == other.m_ranges[ X ] &&
		m_ranges[ Z ] == other.m_ranges[ Z ];

	// Adjacent along Z axis
	bool adjacentZ = ( m_ranges[ Z ].m_max == other.m_ranges[ Z ].m_min ||
		other.m_ranges[ Z ].m_max == m_ranges[ Z ].m_min ) &&
		m_ranges[ X ] == other.m_ranges[ X ] &&
		m_ranges[ Y ] == other.m_ranges[ Y ];

	return adjacentX || adjacentY || adjacentZ;
}

[[nodiscard]] Cuboid
Cuboid::mergeWith( const Cuboid& other ) const
{
	// Merge with cuboid along X axis
	if( ( m_ranges[ X ].m_max == other.m_ranges[ X ].m_min ||
		other.m_ranges[ X ].m_max == m_ranges[ X ].m_min ) &&
		m_ranges[ Y ] == other.m_ranges[ Y ] &&
		m_ranges[ Z ] == other.m_ranges[ Z ] ) {

		return Cuboid{
			Range{std::min( m_ranges[ X ].m_min, other.m_ranges[ X ].m_min ),
				  std::max( m_ranges[ X ].m_max, other.m_ranges[ X ].m_max )},
			m_ranges[ Y ],
			m_ranges[ Z ]
		};
	}

	// Merge with cuboid along Y axis
	if( ( m_ranges[ Y ].m_max == other.m_ranges[ Y ].m_min ||
		other.m_ranges[ Y ].m_max == m_ranges[ Y ].m_min ) &&
		m_ranges[ X ] == other.m_ranges[ X ] &&
		m_ranges[ Z ] == other.m_ranges[ Z ] ) {

		return Cuboid{
			m_ranges[ X ],
			Range{std::min( m_ranges[ Y ].m_min, other.m_ranges[ Y ].m_min ),
				  std::max( m_ranges[ Y ].m_max, other.m_ranges[ Y ].m_max )},
			m_ranges[ Z ]
		};
	}

	// Merge with cuboid along Z axis
	if( ( m_ranges[ Z ].m_max == other.m_ranges[ Z ].m_min ||
		other.m_ranges[ Z ].m_max == m_ranges[ Z ].m_min ) &&
		m_ranges[ X ] == other.m_ranges[ X ] &&
		m_ranges[ Y ] == other.m_ranges[ Y ] ) {

		return Cuboid{
			m_ranges[ X ],
			m_ranges[ Y ],
			Range{std::min( m_ranges[ Z ].m_min, other.m_ranges[ Z ].m_min ),
				  std::max( m_ranges[ Z ].m_max, other.m_ranges[ Z ].m_max )}
		};
	}

	// If not adjacent, return the original cuboid (this case should never happen if canMergeWith is used first)
	return *this;
}