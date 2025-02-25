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

		constexpr bool operator<( const Point& other ) const
		{
			return std::tie( m_coords ) < std::tie( other.m_coords );
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
			size_t h1 = std::hash<int>( )( point.m_coords[ 0 ] );
			size_t h2 = std::hash<int>( )( point.m_coords[ 1 ] );
			size_t h3 = std::hash<int>( )( point.m_coords[ 2 ] );

			// Use the boost hash_combine technique for better distribution
			h1 ^= h2 + 0x9e3779b9 + ( h1 << 6 ) + ( h1 >> 2 );
			h1 ^= h3 + 0x9e3779b9 + ( h1 << 6 ) + ( h1 >> 2 );

			return h1;
		}
	};
}
