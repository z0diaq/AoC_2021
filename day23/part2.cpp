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

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace amphipod;

using State2 = StateT<4>;  // Part 2: rooms with 4 positions

void
Result::ProcessTwo(const std::string& data)
{
	ProcessOne( data );
}

std::string
Result::FinishPartTwo( )
{
	// Insert the extra lines for part 2
	std::vector<std::string> extraLines = { "  #D#C#B#A#", "  #D#B#A#C#" };
	m_map.insert( m_map.begin( ) + 3, extraLines.begin( ), extraLines.end( ) );

	if( m_map.size( ) != 7 )
		return std::to_string( 0 );

	State2 initialState;
	// Initialize hallway as empty
	std::fill( initialState.m_hallway.begin( ), initialState.m_hallway.end( ), std::nullopt );

	// 1st room
	initialState.m_rooms[ Room1 ][ 0 ] = GetAmphipod( 2, 3, m_map );
	initialState.m_rooms[ Room1 ][ 1 ] = GetAmphipod( 3, 3, m_map );
	initialState.m_rooms[ Room1 ][ 2 ] = GetAmphipod( 4, 3, m_map );
	initialState.m_rooms[ Room1 ][ 3 ] = GetAmphipod( 5, 3, m_map );

	// 2nd room
	initialState.m_rooms[ Room2 ][ 0 ] = GetAmphipod( 2, 5, m_map );
	initialState.m_rooms[ Room2 ][ 1 ] = GetAmphipod( 3, 5, m_map );
	initialState.m_rooms[ Room2 ][ 2 ] = GetAmphipod( 4, 5, m_map );
	initialState.m_rooms[ Room2 ][ 3 ] = GetAmphipod( 5, 5, m_map );

	// 3rd room
	initialState.m_rooms[ Room3 ][ 0 ] = GetAmphipod( 2, 7, m_map );
	initialState.m_rooms[ Room3 ][ 1 ] = GetAmphipod( 3, 7, m_map );
	initialState.m_rooms[ Room3 ][ 2 ] = GetAmphipod( 4, 7, m_map );
	initialState.m_rooms[ Room3 ][ 3 ] = GetAmphipod( 5, 7, m_map );

	// 4th room
	initialState.m_rooms[ Room4 ][ 0 ] = GetAmphipod( 2, 9, m_map );
	initialState.m_rooms[ Room4 ][ 1 ] = GetAmphipod( 3, 9, m_map );
	initialState.m_rooms[ Room4 ][ 2 ] = GetAmphipod( 4, 9, m_map );
	initialState.m_rooms[ Room4 ][ 3 ] = GetAmphipod( 5, 9, m_map );

	auto result = SolveWithDijkstra( initialState );

	if( result )
		return std::to_string( *result );
	else
	{
		std::cerr << "No solution found!" << std::endl;
		return std::to_string( 0 );
	}
}