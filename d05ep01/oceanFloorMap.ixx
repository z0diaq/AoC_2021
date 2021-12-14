module;

#include <vector>
#include <stdexcept>
#include <algorithm>

#if 0
#include <ranges>
#endif

export module hydrothermal_venture:ocean_floor_map;
import :data;

export namespace hydrothermal_venture
{
	class OceanFloorMap
	{
	public:

		void Init( unsigned int width, unsigned int height );

		void Process( const Line& line );

		unsigned int& Ref( unsigned int col, unsigned int row );

		unsigned int CountPointCoveredByTwoAndMore( ) const;

	private:
		std::vector<unsigned int> m_map;

		unsigned int m_width = 0;
		unsigned int m_height = 0;

	};
}

using namespace hydrothermal_venture;

void
OceanFloorMap::Init( unsigned int width, unsigned int height )
{
	m_map.clear( );
	m_map.resize( width * height, 0 );

	m_width = width;
	m_height = height;
}

void
OceanFloorMap::Process( const Line& line )
{
	if( 0 == m_width && 0 == m_height )
		throw std::logic_error( "Init first!" );

	if( line.m_start.m_x == line.m_end.m_x )
	{
		// VS20222 17.0.2 no there yet
#if 0
		std::ranges::for_each( line.m_start.m_y, line.m_end.m_y, [ this ]( unsigned int y ) -> void
			{
				++Ref( x, y );
			} );
#endif
		const auto x = line.m_start.m_x;
		for(
			auto y = std::min( line.m_start.m_y, line.m_end.m_y );
			y <= std::max( line.m_start.m_y, line.m_end.m_y );
			++y )
		{
			++Ref( x, y );
		}
	}

	if( line.m_start.m_y == line.m_end.m_y &&
		line.m_start.m_x != line.m_end.m_x ) // avoid going twice for single point lines
	{
		const auto y = line.m_start.m_y;
		for(
			auto x = std::min( line.m_start.m_x, line.m_end.m_x );
			x <= std::max( line.m_start.m_x, line.m_end.m_x );
			++x )
		{
			++Ref( x, y );
		}
	}
}

unsigned int& 
OceanFloorMap::Ref( unsigned int col, unsigned int row )
{
	return m_map.at( row * m_width + col );
}

unsigned int
OceanFloorMap::CountPointCoveredByTwoAndMore( ) const
{
	return static_cast<unsigned int>( std::count_if(
		m_map.begin( ),
		m_map.end( ),
		[ ]( const unsigned int& value ) -> bool
		{
			return value > 1;
		}
	) );
}
