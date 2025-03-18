import reactor_reboot;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>
#include <functional>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <numeric>

using namespace reactor_reboot;

void
Result::ProcessTwo( const std::string& _data )
{
	ProcessOne( _data );
}

std::vector<Cuboid>
mergeCuboids( std::vector<Cuboid> cuboids );

std::string
Result::FinishPartTwo( )
{
	std::vector<Cuboid> onCuboids;
	size_t commandNo{ 0 };
	for( const Command& command : m_commands )
	{
		std::vector<Cuboid> newOnCuboids;

		if( command.m_isOn )
		{
			// Start with the entire cuboid
			std::vector<Cuboid> toAdd{ Cuboid{ command.m_ranges } };

			// Subtract all existing "on" cuboids to avoid double-counting
			for( const auto& existing : onCuboids )
			{
				std::vector<Cuboid> remaining;

				for( const auto& current : toAdd )
				{
					auto parts = current.subtract( existing );
					remaining.insert( remaining.end( ), parts.begin( ), parts.end( ) );
				}

				toAdd = std::move( remaining );
			}

			// Add all existing cuboids and the new non-overlapping parts
			newOnCuboids = onCuboids;
			newOnCuboids.insert( newOnCuboids.end( ), toAdd.begin( ), toAdd.end( ) );
		}
		else
		{
			// For each existing cuboid, subtract the "off" cuboid and keep the remaining parts
			for( const auto& existing : onCuboids )
			{
				auto parts = existing.subtract( Cuboid{ command.m_ranges } );
				newOnCuboids.insert( newOnCuboids.end( ), parts.begin( ), parts.end( ) );
			}
		}

		onCuboids = mergeCuboids( newOnCuboids );
		std::cout << "After command " << ++commandNo << " have " << onCuboids.size( ) << " cuboids..." << std::endl;
	}

	// Calculate the total volume of all "on" cuboids
	const size_t onCount = std::transform_reduce(
		onCuboids.begin( ), onCuboids.end( ),
		size_t{ 0 },
		std::plus<>( ),
		[ ]( const Cuboid& c ) { return c.volume( ); }
	);
	return std::to_string( onCount );
}

std::vector<Cuboid>
mergeCuboids( std::vector<Cuboid> cuboids )
{
	if( cuboids.empty( ) )
		return cuboids;

	bool didMerge = true;
	while( didMerge )
	{
		didMerge = false;

		// Iteratively try to merge pairs of cuboids
		for( size_t i = 0; i < cuboids.size( ); ++i )
		{
			for( size_t j = i + 1; j < cuboids.size( ); ++j )
			{
				if( cuboids[ i ].canMergeWith( cuboids[ j ] ) )
				{
					// Merge the cuboids
					Cuboid merged = cuboids[ i ].mergeWith( cuboids[ j ] );

					// Replace the first cuboid with the merged result
					cuboids[ i ] = merged;

					// Remove the second cuboid
					cuboids.erase( cuboids.begin( ) + j );

					didMerge = true;
					break; // Start over with the new set of cuboids
				}
			}
			if( didMerge ) break;
		}
	}

	return cuboids;
}