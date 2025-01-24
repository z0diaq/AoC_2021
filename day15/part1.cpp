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

std::size_t ShortestPathLength( const std::deque<std::string>& _map )
{

	std::priority_queue< PositionWithWeight> openSet;
	openSet.push( PositionWithWeight{ 0, 0, static_cast<unsigned int>(_map[ 0 ][ 0 ]) });







	return 0;
}
