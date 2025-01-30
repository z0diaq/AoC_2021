import chitons;

#include <string>
#include <limits>

#include <map>
#include <set>
#include <deque>
#include <queue>

using namespace chitons;

void
Result::ProcessOne( const std::string& data )
{
	m_map.push_back( data );
}

// start and end are known
int ShortestDistance( const std::deque<std::string>& _graph );

std::string
Result::FinishPartOne( )
{
	return std::to_string( ShortestDistance( m_map ) );
}

struct Position
{
	int m_col{};
	int m_row{};
};

bool operator<( const Position& _lhs, const Position& _rhs )
{
	if( _lhs.m_row != _rhs.m_row )
		return _lhs.m_row < _rhs.m_row;
	return _lhs.m_col < _rhs.m_col;
}

struct Node {
	Position m_id;
	int m_heuristic{};
	int m_cost{};
};

bool operator<( const Node& a, const Node& b ) {
	return a.m_cost + a.m_heuristic > b.m_cost + b.m_heuristic;
}

bool operator==( const Position& _lhs, const Position& _rhs )
{
	return _lhs.m_col == _rhs.m_col && _lhs.m_row == _rhs.m_row;
}

int ShortestDistance( const std::deque<std::string>& _graph )
{
	const Position start{ 0, 0 };
	const int width{ static_cast<int>( _graph.front( ).length( ) ) };
	const int height{ static_cast<int>( _graph.size( ) ) };
	const Position destination{ width - 1, height - 1 };

	// Heuristic function (Manhattan distance)
	auto heuristic = [&]( const Position& _id1, const Position& _id2 ) -> int
	{
		return abs( _id2.m_col - _id1.m_col ) + abs( _id2.m_row - _id1.m_row );
	};

	auto getCost = [&]( const Position& _position ) -> int
	{
		return _graph[ _position.m_row ][ _position.m_col ] - '0'; // convert from char to int range
	};

	auto constructNode = [&]( const Position& _position ) -> Node
	{
		return Node{ _position, heuristic( _position, destination ), getCost( _position ) };
	};

	auto getNeighbours = [&]( const Position& _position ) -> std::vector<Node>
	{
		std::vector<Node> result;
		result.reserve( 4 );

		if( _position.m_row > 0 )
			result.emplace_back( constructNode( { _position.m_col, _position.m_row - 1 } ) );
		if( _position.m_col > 0 )
			result.emplace_back( constructNode( { _position.m_col - 1, _position.m_row } ) );
		if( _position.m_row < ( height - 1 ) )
			result.emplace_back( constructNode( { _position.m_col, _position.m_row + 1 } ) );
		if( _position.m_col < ( width - 1 ) )
			result.emplace_back( constructNode( { _position.m_col + 1, _position.m_row } ) );

		return result;
	};

	std::priority_queue<Node> openList;
	std::set<Position> closedList;

	openList.push( { start, heuristic( start, destination ), 0 } ); // "don't count the risk level of your starting position unless you enter it"

	while( !openList.empty( ) )
	{
		auto currentNode = openList.top( );
		openList.pop( );

		if( currentNode.m_id == destination )
			return currentNode.m_cost;

		closedList.insert( currentNode.m_id );

		for( const auto& neighbor : getNeighbours( currentNode.m_id ) )
		{
			if( closedList.contains( neighbor.m_id ) )
				continue;

			openList.push( { neighbor.m_id, neighbor.m_heuristic, currentNode.m_cost + neighbor.m_cost } );
		}
	}

	return std::numeric_limits<int>::max( ); // No path found
}
