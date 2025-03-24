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

namespace
{
	constexpr std::array<std::uint32_t, 4> MOVE_COSTS{ 1, 10, 100, 1000 };
}

template<std::size_t RoomSize>
struct StateT
{
	using AmphipodOpt = std::optional<Amphipod>;
	// room can have at 0-2/4 amphipods
	using Room = std::array<AmphipodOpt, RoomSize>;

	std::array<AmphipodOpt, 11> m_hallway;
	std::array<Room, 4> m_rooms;
	std::uint32_t m_usedEnergy{};

	bool
	IsRoomReady( const Room& _room, Amphipod _amphipod ) const
	{
		return std::all_of(
			_room.begin( ),
			_room.end( ),
			[_amphipod]( const auto& spot ) {
				return !spot.has_value( ) || *spot == _amphipod;
			}
		);
	}

	bool
	IsSolved( ) const
	{
		for( std::uint16_t type = 0; type != 4; ++type )
		{
			for( std::uint16_t pos = 0; pos != RoomSize; ++pos )
			{
				if( !m_rooms[ type ][ pos ].has_value( ) || *m_rooms[ type ][ pos ] != type )
					return false;
			}
		}
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

	std::vector<StateT>
	GenerateHallwayToRoomMoves( ) const
	{
		std::vector<StateT> nextStates;

		for( int hallwayPos = 0; hallwayPos < 11; ++hallwayPos )
		{
			const auto& spot = m_hallway[ hallwayPos ];
			if( !spot.has_value( ) )
				continue;

			const Amphipod amphipod = *spot;
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

			const int roomPos = static_cast<int>(std::distance( m_rooms[ roomIndex ].begin( ), roomIt.base( ) )) - 1;

			// Calculate energy cost
			const int steps = std::abs( hallwayPos - roomEntrance ) + roomPos + 1;
			const int cost = steps * MOVE_COSTS[ roomIndex ];

			// Create new state (immutable approach)
			StateT newState = *this;
			newState.m_hallway[ hallwayPos ] = std::nullopt;
			newState.m_rooms[ roomIndex ][ roomPos ] = amphipod;
			newState.m_usedEnergy += cost;

			nextStates.push_back( std::move( newState ) );
		}

		return nextStates;
	}

	std::vector<StateT>
	GenerateRoomToHallwayMoves( ) const
	{
		std::vector<StateT> nextStates;

		for( int roomIndex = 0; roomIndex < 4; ++roomIndex )
		{
			// Find the topmost amphipod in the room
			auto roomIt = std::find_if(
				m_rooms[ roomIndex ].begin( ),
				m_rooms[ roomIndex ].end( ),
				[ ]( const auto& spot ) { return spot.has_value( ); }
			);

			if( roomIt == m_rooms[ roomIndex ].end( ) )
				continue; // Room is empty

			const int roomPos = static_cast<int>(std::distance( m_rooms[ roomIndex ].begin( ), roomIt ));
			const Amphipod amphipod = **roomIt;
			const int targetRoomIndex = static_cast<int>( amphipod );

			// If amphipod is already in the correct room and all amphipods below it are also correct, don't move it
			if( roomIndex == targetRoomIndex )
			{
				const bool shouldStay = std::all_of(
					roomIt,
					m_rooms[ roomIndex ].end( ),
					[amphipod]( const auto& spot ) { return spot.has_value( ) && *spot == amphipod; }
				);

				if( shouldStay )
					continue;
			}

			const int roomEntrance = GetRoomEntrance( roomIndex );

			// Static array of valid hallway positions (skip positions directly above rooms)
			constexpr std::array<int, 7> validHallwayPositions = { 0, 1, 3, 5, 7, 9, 10 };

			for( const int hallwayPos : validHallwayPositions )
			{
				if( !IsHallwayClear( roomEntrance, hallwayPos ) )
					continue;

				// Calculate energy cost
				const int steps = std::abs( hallwayPos - roomEntrance ) + roomPos + 1;
				const int cost = steps * MOVE_COSTS[ static_cast<int>( amphipod ) ];

				StateT newState = *this;
				newState.m_rooms[ roomIndex ][ roomPos ] = std::nullopt;
				newState.m_hallway[ hallwayPos ] = amphipod;
				newState.m_usedEnergy += cost;

				nextStates.push_back( std::move( newState ) );
			}
		}

		return nextStates;
	}

	std::vector<StateT>
	GenerateMoves( ) const
	{
		auto nextHallwayToRoomMoves = GenerateHallwayToRoomMoves( ),
			nextRoomToHallwaysMoves = GenerateRoomToHallwayMoves( );

		nextHallwayToRoomMoves.insert( nextHallwayToRoomMoves.end( ),
			std::make_move_iterator( nextRoomToHallwaysMoves.begin( ) ),
			std::make_move_iterator( nextRoomToHallwaysMoves.end( ) ) );

		return nextHallwayToRoomMoves;
	}

	bool
	operator==( const StateT& _other ) const
	{
		// NOTE: intentionally not comparing energy cost
		return m_hallway == _other.m_hallway && m_rooms == _other.m_rooms;
	}

	bool
	operator<( const StateT& _other ) const
	{
		return m_usedEnergy > _other.m_usedEnergy;
	}
};

namespace std
{
	template<std::size_t RoomSize>
	struct hash<StateT<RoomSize>>
	{
		std::size_t
		operator()( const StateT<RoomSize>& _state ) const
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

void
Result::ProcessOne( const std::string& data )
{
	m_map.push_back( data );
}

Amphipod
GetAmphipod( size_t _row, size_t _column, const Map& _map );

using State1 = StateT<2>;  // Part 1: rooms with 2 positions
using State2 = StateT<4>;  // Part 2: rooms with 4 positions

// Dijkstra algorithm
template <typename StateType>
std::optional<int>
SolveWithDijkstra( const StateType& _initialState )
{
	std::priority_queue<StateType> queue;
	std::unordered_map<StateType, std::uint32_t> visited;

	queue.push( _initialState );
	visited[ _initialState ] = _initialState.m_usedEnergy;

	while( !queue.empty( ) )
	{
		StateType currentState = queue.top( );
		queue.pop( );

		auto it = visited.find( currentState );
		if( it != visited.end( ) && it->second < currentState.m_usedEnergy )
			continue;

		if( currentState.IsSolved( ) )
			return currentState.m_usedEnergy;

		auto nextStates = currentState.GenerateMoves( );

		for( const auto& nextState : nextStates )
		{
			auto it = visited.find( nextState );

			// If we haven't visited this state or found a better path, update it
			if( it == visited.end( ) || nextState.m_usedEnergy < it->second )
			{
				visited[ nextState ] = nextState.m_usedEnergy;
				queue.push( nextState );
			}
		}
	}

	return std::nullopt; // No solution found

}

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
