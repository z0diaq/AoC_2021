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

using AmphipodOpt = std::optional<Amphipod>;

// room can have at 0-2 amphipods
using Room = std::array<AmphipodOpt, 2>;

struct State
{
	std::array<AmphipodOpt, 10> m_hallway;
	std::array<Room, 4> m_rooms;
	std::uint32_t m_usedEnergy;

	bool IsRoomReady( const Room& _room, Amphipod _amphipod ) const
	{
		//TODO: check if empty or have required Amphipod type inside
		return false;
	}

	bool IsSolved( ) const
	{
		for( std::uint16_t type = 0; type != 4; ++type )
			if( m_rooms[ type ][ 0 ] != m_rooms[ type ][ 1 ] || m_rooms[ type ][ 0 ] != type )
				return false;
		return true;
	}

	std::vector<State> GenerateHallwayToRoomMoves( ) const
	{
		std::vector<State> nextStates;

		// TODO: fill the states

		return nextStates;
	}

	std::vector<State> GenerateRoomToHallwayMoves( ) const
	{
		std::vector<State> nextStates;

		// TODO: fill the states

		return nextStates;
	}

	std::vector<State> GenerateMoves( ) const
	{
		auto nextHallwayToRoomMoves = GenerateHallwayToRoomMoves( ),
			nextRoomToHallwaysMoves = GenerateRoomToHallwayMoves( );

		nextHallwayToRoomMoves.insert( nextHallwayToRoomMoves.end( ),
			std::make_move_iterator( nextRoomToHallwaysMoves.begin( ) ),
			std::make_move_iterator( nextRoomToHallwaysMoves.end( ) ) );

		return nextHallwayToRoomMoves;
	}
};

namespace std {
	template<>
	struct hash<State> {
		std::size_t operator()( const State& _state ) const
		{
			return 0; // TODO: hash
		}
	};
}

// Dijkstra algorithm
void
Result::ProcessOne( const std::string& data )
{
	std::priority_queue<State> queue;
	std::unordered_set<State, int> visited;

	// TODO: implement Dijkstra algorithm to find min energy spent to solve puzzle



	m_map.push_back( data );
}

Amphipod GetAmphipod( size_t _row, size_t _column, const Map& _map );

std::string
Result::FinishPartOne( )
{
	if( m_map.size( ) != 5 )
		return 0;

	State initialState;
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

	return std::to_string( 0 );
}

Amphipod GetAmphipod( size_t _row, size_t _column, const Map& _map )
{
	// TODO: extract from map
	// throw exception if not A-D

	return A;
}
