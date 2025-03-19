import reactor_reboot;

#include <string>
#include <vector>
#include <functional>
#include <numeric>

using namespace reactor_reboot;

void
Result::ProcessTwo( const std::string& _data )
{
	ProcessOne( _data );
}

// uses Inclusion-exclusion principle
// see https://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle

struct SignedCuboid
{
	Cuboid m_cuboid;
	int64_t m_sign; // +1 for ON, -1 for adjustment cuboids

	SignedCuboid( const Cuboid& _cuboid, int64_t _sign ) : m_cuboid( _cuboid ), m_sign( _sign ) { }
};

std::string
Result::FinishPartTwo( )
{
	std::vector<SignedCuboid> signedCuboids;

	for( const Command& command : m_commands )
	{
		Cuboid current{ command.m_ranges };

		std::vector<SignedCuboid> newIntersections;

		for( const auto& existing : signedCuboids )
		{
			auto intersection = current.intersection( existing.m_cuboid );
			if( intersection )
			{
				// intersections with opposite sign implements inclusion-exclusion principle
				newIntersections.emplace_back( *intersection, -existing.m_sign );
			}
		}

		// For ON commands, add the cuboid to our calculation
		if( command.m_isOn )
			signedCuboids.emplace_back( current, 1 );

		// Add all the intersections that adjust for overlaps
		signedCuboids.insert( signedCuboids.end( ),
			std::make_move_iterator( newIntersections.begin( ) ),
			std::make_move_iterator( newIntersections.end( ) ) );
	}

	const int64_t totalVolume = std::transform_reduce(
		signedCuboids.begin( ), signedCuboids.end( ),
		int64_t{ 0 },
		std::plus<>( ),
		[ ]( const SignedCuboid& sc ) {
			return sc.m_sign * static_cast< int64_t >( sc.m_cuboid.volume( ) );
		}
	);

	return std::to_string( totalVolume );
}
