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


struct Position
{
	int m_row;
	int m_col;
};

bool operator==( const Position& _lhs, const Position& _rhs )
{
	return _lhs.m_row == _rhs.m_row && _lhs.m_col == _rhs.m_col;
}

struct Node {
	Position m_id;
	unsigned int m_heuristic;
	unsigned int m_cost;
};

bool operator<( const Node& a, const Node& b ) {
	return a.m_cost + a.m_heuristic > b.m_cost + b.m_heuristic;
}



std::size_t LengthOfShortestPath( const std::deque<std::string>& _map )
{
	const Position goal{ _map.size( ) - 1, _map[ 0 ].length( ) };
	const size_t width{ _map.front( ).length( ) };
	const size_t height{ _map.size( ) };

	// Heuristic function (Manhattan distance)
	auto heuristic = [&]( const Position& _lhs, const Position& _rhs ) -> unsigned int {
		return static_cast< unsigned int >( abs( _rhs.m_row - _lhs.m_row ) + std::abs( _rhs.m_col - _lhs.m_col ) );
		};

	auto constructNode = [&heuristic, &goal]( const Position& _where ) -> Node
		{
			return Node{ _where, heuristic( _where, goal ) };
		};

	auto getNeighbours = [&]( const Position& _position ) -> std::vector<Node>
		{
			std::vector<Node> result;
			result.reserve( 4 );

			if( _position.m_row > 0 )
				result.push_back( constructNode( { _position.m_row - 1, _position.m_col } ) );
			if( _position.m_col > 0 )
				result.push_back( constructNode( { _position.m_row, _position.m_col - 1 } ) );
			if( _position.m_col + 1 < width )
				result.push_back( constructNode( { _position.m_row, _position.m_col + 1 } ) );
			if( _position.m_row + 1 < height )
				result.push_back( constructNode( { _position.m_row + 1, _position.m_col } ) );

			return result;
		};

	std::priority_queue<Node> openList, closedList;
	openList.push( constructNode( { 0, 0 } ) );

	//open_list[ start_id ] = { start_id, heuristic( start_id, goal_id ), 0 };

	while( !openList.empty( ) ) {

		auto currentNode = openList.top( );
		openList.pop( );

		if( currentNode.m_id == goal ) {
			return currentNode.m_cost;
		}

		closedList.push( currentNode );
		//closed_list[ current_node.first ] = current_node.second;

		for( const auto& neighbor : graph[ current_node.first ] ) {
			if( closed_list.find( neighbor ) != closed_list.end( ) ) {
				continue;
			}

			double new_cost = current_node.second.cost + neighbor;
			auto it = open_list.find( neighbor );
			if( it == open_list.end( ) || new_cost < it->second.cost ) {
				open_list[ neighbor ] = { neighbor, heuristic( neighbor, goal ), new_cost };
			}
		}
	}

	return std::numeric_limits<double>::max( ); // No path found
}

{


	return 0;
}

