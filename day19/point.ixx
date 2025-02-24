module;

#include <array>
#include <vector>

export module beacon_scanner:point;

export namespace beacon_scanner
{
	using Coords = std::array<int, 3>;
	using Matrix = std::array<Coords, 3>;

	struct Point {
		Coords m_coords;

		auto operator<=>( const Point& ) const = default;

		constexpr Point operator+( const Point& other ) const {
			return Point{ std::array{
				m_coords[ 0 ] + other.m_coords[ 0 ],
				m_coords[ 1 ] + other.m_coords[ 1 ],
				m_coords[ 2 ] + other.m_coords[ 2 ]
			} };
		}

		constexpr Point operator-( const Point& other ) const {
			return Point{ std::array{
				m_coords[ 0 ] - other.m_coords[ 0 ],
				m_coords[ 1 ] - other.m_coords[ 1 ],
				m_coords[ 2 ] - other.m_coords[ 2 ]
			} };
		}

		std::vector<Point> GenerateRotations( ) const
		{
			const auto [x, y, z] = m_coords;
			return std::vector<Point>{
				{x, y, z}, {x, -z, y}, {x, -y, -z}, {x, z, -y},
				{-x, -y, z}, {-x, -z, -y}, {-x, y, -z}, {-x, z, y},
				{y, z, x}, {y, -x, z}, {y, -z, -x}, {y, x, -z},
				{-y, -z, x}, {-y, -x, -z}, {-y, z, -x}, {-y, x, z},
				{z, x, y}, {z, -y, x}, {z, -x, -y}, {z, y, -x},
				{-z, -x, y}, {-z, -y, -x}, {-z, x, -y}, {-z, y, x}
			};
		}
	};

	struct PointHash
	{
		size_t operator()( const Point& point ) const
		{
			return std::hash<int>( )( point.m_coords[ 0 ] ) ^
				( std::hash<int>( )( point.m_coords[ 1 ] ) << 1 ) ^
				( std::hash<int>( )( point.m_coords[ 2 ] ) << 2 );
		}
	};
}
