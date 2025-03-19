import reactor_reboot;

#include <string>
#include <array>
#include <regex>
#include <unordered_set>

using namespace reactor_reboot;

using Point3D = std::array<int, 3>;

namespace std
{
	template<>
	struct hash< Point3D >
	{
		size_t operator()( Point3D const& _point ) const noexcept
		{
			using namespace reactor_reboot;

			size_t xHash{ hash<int>{}( _point[ X ] ) };
			size_t yHash{ hash<int>{}( _point[ Y ] ) };
			size_t zHash{ hash<int>{}( _point[ Z ] ) };

			// one of many possible hash combining methods
			return xHash ^ ( yHash << 1 ) ^ ( zHash << 2 );
		}
	};

} // namespace std

void
Result::ProcessOne( const std::string& data )
{
	static const std::regex pattern( R"((on|off) x=(-?\d+)\.\.(-?\d+),y=(-?\d+)\.\.(-?\d+),z=(-?\d+)\.\.(-?\d+))" );

	std::smatch matches;
	if( std::regex_match( data, matches, pattern ) )
	{
		m_commands.push_back( Command {
			matches[ 1 ] == "on",
			{ Range{std::stoi( matches[ 2 ] ), std::stoi( matches[ 3 ] ) + 1 },
			Range{std::stoi( matches[ 4 ] ), std::stoi( matches[ 5 ] ) + 1 },
			Range{std::stoi( matches[ 6 ] ), std::stoi( matches[ 7 ] ) + 1 } }  }
		);
	}
}

void
ProcessCommand( const Command& _cmd, std::unordered_set<Point3D>& _points );

std::string
Result::FinishPartOne( )
{
	std::unordered_set<Point3D> activatedPoints{};

	std::for_each( m_commands.begin( ), m_commands.end( ), [&activatedPoints]( const Command& _cmd ) -> void {
		ProcessCommand( _cmd, activatedPoints );
		} );


	return std::to_string( activatedPoints.size( ) );
}

[[nodiscard]] Range
TrimRange( Range _range )
{
	if( _range.m_min > 50 || _range.m_max < -50 )
		return Range{ 0, 0 };
	return Range{ std::max( _range.m_min, -50 ), std::min( _range.m_max, 51 ) };
}

[[nodiscard]] bool
IsEmptyRange( const Range& _range )
{
	return _range.m_min == _range.m_max;
}

void
ProcessCommand( const Command& _cmd, std::unordered_set<Point3D>& _points )
{
	const Range xRange{ TrimRange( _cmd.m_ranges[ X ] ) },
		yRange{ TrimRange( _cmd.m_ranges[ Y ] ) },
		zRange{ TrimRange( _cmd.m_ranges[ Z ] ) };

	if( IsEmptyRange( xRange ) || IsEmptyRange( yRange ) || IsEmptyRange( zRange ) )
		return;

	for( int x{ xRange.m_min }; x != xRange.m_max; ++x )
	{
		for( int y{ yRange.m_min }; y != yRange.m_max; ++y )
		{
			for( int z{ zRange.m_min }; z != zRange.m_max; ++z )
			{
				if( _cmd.m_isOn )
					_points.insert( Point3D{ x, y, z } );
				else
					_points.erase( Point3D{ x, y, z } );
			}
		}
	}
}
