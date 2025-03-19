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
