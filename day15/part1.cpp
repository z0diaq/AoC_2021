import chitons;

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
#include <queue>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace chitons;

void
Result::ProcessOne( const std::string& data )
{
	m_map.push_back( data );
}

// start and end are known
std::size_t ShortestPathLength( const std::deque<std::string>& _map );

std::string
Result::FinishPartOne( )
{
	return std::to_string( ShortestPathLength( m_map ) );
}

struct PositionWithWeight
{
	unsigned int m_x, m_y, m_weight;
};

bool operator<( const PositionWithWeight& _lhs, const PositionWithWeight& _rhs )
{
	return _lhs.m_weight < _rhs.m_weight;
}


bool SamePosition( const PositionWithWeight& _lhs, const PositionWithWeight& _rhs );

std::size_t ShortestPathLength( const std::deque<std::string>& _map )
{
	// direct implementation of https://en.wikipedia.org/wiki/A*_search_algorithm

	const std::uint32_t width{ static_cast< std::uint32_t >( _map.front( ).length( ) ) };
	const std::uint32_t height{ static_cast< std::uint32_t >( _map.size( ) ) };

	std::priority_queue< PositionWithWeight> openSet;
	openSet.push( PositionWithWeight{ 0, 0, static_cast< unsigned int >( _map[ 0 ][ 0 ] ) } );

	std::map<PositionWithWeight, PositionWithWeight> cameFrom;

	using WeightsRow = std::vector<std::uint64_t>;
	using WeightsMap = std::vector<WeightsRow>;

	WeightsRow rowInit( width, std::numeric_limits<std::uint64_t>::max( ) );
	WeightsMap gScore( height, rowInit );

	WeightsMap fScore = gScore;
	fScore[ 0 ][ 0 ] = 1;// don't use heuristics since graph is weighted

	const PositionWithWeight destination{ height - 1, width - 1, 0 };

	while( false == openSet.empty( ) )
	{
		auto current = openSet.top( );
		openSet.pop( );

		if( SamePosition( current, destination ) )
			return current.m_weight;
	}

	return 0;
}

bool SamePosition( const PositionWithWeight& _lhs, const PositionWithWeight& _rhs )
{
	return _lhs.m_x == _rhs.m_x && _lhs.m_y == _rhs.m_y;
}

