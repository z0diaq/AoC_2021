module;

#include <array>

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

		constexpr Point ApplyRotation( const Matrix& matrix ) const
		{
			return Point{ std::array{
				matrix[ 0 ][ 0 ] * m_coords[ 0 ] + matrix[ 0 ][ 1 ] * m_coords[ 1 ] + matrix[ 0 ][ 2 ] * m_coords[ 2 ],
				matrix[ 1 ][ 0 ] * m_coords[ 0 ] + matrix[ 1 ][ 1 ] * m_coords[ 1 ] + matrix[ 1 ][ 2 ] * m_coords[ 2 ],
				matrix[ 2 ][ 0 ] * m_coords[ 0 ] + matrix[ 2 ][ 1 ] * m_coords[ 1 ] + matrix[ 2 ][ 2 ] * m_coords[ 2 ]
			} };
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
