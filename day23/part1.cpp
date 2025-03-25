import amphipod;

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
#include <optional>
#include <queue>
#include <unordered_set>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace amphipod;



void
Result::ProcessOne( const std::string& data )
{
	m_map.push_back( data );
}

Amphipod
GetAmphipod( size_t _row, size_t _column, const Map& _map );

using State1 = StateT<2>;  // Part 1: rooms with 2 positions



std::string
Result::FinishPartOne( )
{
	if( m_map.size( ) != 5 )
		return 0;

	State1 initialState;
	// 1st room
	initialState.m_rooms[ Room1 ][ 0 ] = GetAmphipod( 2, 3, m_map );
	initialState.m_rooms[ Room1 ][ 1 ] = GetAmphipod( 3, 3, m_map );

	// 2nd room
	initialState.m_rooms[ Room2 ][ 0 ] = GetAmphipod( 2, 5, m_map );
	initialState.m_rooms[ Room2 ][ 1 ] = GetAmphipod( 3, 5, m_map );

	// 3rd room
	initialState.m_rooms[ Room3 ][ 0 ] = GetAmphipod( 2, 7, m_map );
	initialState.m_rooms[ Room3 ][ 1 ] = GetAmphipod( 3, 7, m_map );

	// 4th room
	initialState.m_rooms[ Room4 ][ 0 ] = GetAmphipod( 2, 9, m_map );
	initialState.m_rooms[ Room4 ][ 1 ] = GetAmphipod( 3, 9, m_map );

	auto result = SolveWithDijkstra( initialState );

	if( result )
		return std::to_string( *result );
	else
	{
		std::cerr << "No solution found!" << std::endl;
		return std::to_string( 0 );
	}
}



Amphipod GetAmphipod( size_t _row, size_t _column, const Map& _map )
{
	if( _row >= _map.size( ) )
	{
		std::cerr << "Requested row " << _row << " but map has only " << _map.size( ) << " rows" << std::endl;
		throw std::runtime_error( "Invalid row index" );
	}

	const auto& row = _map[ _row ];

	if( _column >= row.length( ) )
	{
		std::cerr << "Requested column " << _column << " but row " << _row << " has only " << row.length( ) << " columns" << std::endl;
		throw std::runtime_error( "Invalid column index" );
	}

	char c = row[ _column ];
	if( c < 'A' || c > 'D' )
	{
		std::cerr << "[" << c << "] from line [" << row << "] at (" << _column << ", " << _row << ") is not a valid Amphipod (A-D)" << std::endl;
		throw std::runtime_error( "Not a valid amphipod" );
	}

	return static_cast<Amphipod>(c - 'A');
}
