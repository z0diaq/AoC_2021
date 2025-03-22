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

	bool
	IsRoomReady( const Room& _room, Amphipod _amphipod ) const
	{
		//TODO: check if empty or have required Amphipod type inside
		return false;
	}

	bool
	IsSolved( ) const
	{
		for( std::uint16_t type = 0; type != 4; ++type )
			if( m_rooms[ type ][ 0 ] != m_rooms[ type ][ 1 ] || m_rooms[ type ][ 0 ] != type )
				return false;
		return true;
	}

	constexpr int
	GetRoomEntrance( int _roomIndex ) const
	{
		return 2 + _roomIndex * 2;
	}

	bool
	IsHallwayClear( int _from, int _to ) const
	{
		const int start = std::min( _from, _to );
		const int end = std::max( _from, _to );

		return std::all_of(
			m_hallway.begin( ) + start,
			m_hallway.begin( ) + end + 1,
			[_from, this]( const auto& spot )
			{
				return !spot.has_value( ) || &spot == &m_hallway[ _from ];
			}
		);
	}

	std::vector<State> GenerateHallwayToRoomMoves( ) const
	{
		std::vector<State> nextStates;

		for( int hallwayPos = 0; hallwayPos < 11; ++hallwayPos )
		{
			const auto& spot = m_hallway[ hallwayPos ];
			if( !spot.has_value( ) )
				continue;

			const char amphipod = *spot;
			const int roomIndex = static_cast<int>( amphipod );
			const int roomEntrance = GetRoomEntrance( roomIndex );

			// Check if path to room entrance is clear
			if( !IsHallwayClear( hallwayPos, roomEntrance ) )
				continue;

			// Check if the destination room is ready
			if( !IsRoomReady( m_rooms[ roomIndex ], amphipod ) )
				continue;

			// Find the deepest empty spot in the room
			auto roomIt = std::find_if(
				m_rooms[ roomIndex ].rbegin( ),
				m_rooms[ roomIndex ].rend( ),
				[ ]( const auto& spot ) { return !spot.has_value( ); }
			);

			if( roomIt == m_rooms[ roomIndex ].rend( ) )
				continue; // Room is full

			const int roomPos = std::distance( m_rooms[ roomIndex ].begin( ), roomIt.base( ) ) - 1;

			// Calculate energy cost
			const int steps = std::abs( hallwayPos - roomEntrance ) + roomPos + 1;
			const int cost = steps * m_moveCosts[ roomIndex ];

			// Create new state (immutable approach)
			State newState = *this;
			newState.m_hallway[ hallwayPos ] = std::nullopt;
			newState.m_rooms[ roomIndex ][ roomPos ] = amphipod;
			newState.m_usedEnergy += cost;

			nextStates.push_back( std::move( newState ) );
		}

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
			std::size_t hash_value{};
			size_t shift{};

			for( const auto& spot : _state.m_hallway )
				hash_value = hash_value ^ ( std::hash<std::uint16_t>{}( spot.has_value( ) ? *spot : '.' ) << ++shift );

			for( const auto& room : _state.m_rooms )
			{
				for( const auto& spot : room )
				{
					hash_value = hash_value ^ ( std::hash<std::uint16_t>{}( spot.has_value( ) ? *spot : '.' ) << ++shift );
				}
			}

			return hash_value;
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
