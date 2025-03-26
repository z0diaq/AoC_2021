export module amphipod:state;

import :types;

import <array>;
import <cstddef>;
import <optional>;
import <vector>;
import <algorithm>;

export namespace amphipod
{
	template<::std::size_t RoomSize>
	struct StateT
	{
		using AmphipodOpt = std::optional<Amphipod>;
		// room can have at 0-2/4 amphipods
		using Room = std::array<AmphipodOpt, RoomSize>;

		::std::array<AmphipodOpt, 11> m_hallway;
		::std::array<Room, 4> m_rooms;
		::std::uint32_t m_usedEnergy{};

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
				const int roomIndex = static_cast< int >( amphipod );
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

				const int roomPos = static_cast< int >( std::distance( m_rooms[ roomIndex ].begin( ), roomIt.base( ) ) ) - 1;

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

				const int roomPos = static_cast< int >( std::distance( m_rooms[ roomIndex ].begin( ), roomIt ) );
				const Amphipod amphipod = **roomIt;
				const int targetRoomIndex = static_cast< int >( amphipod );

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
					const int cost = steps * MOVE_COSTS[ static_cast< int >( amphipod ) ];

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
} // amphipod

namespace std
{
	template<size_t RoomSize>
	struct hash<amphipod::StateT<RoomSize>>
	{
		std::size_t
			operator()( const amphipod::StateT<RoomSize>& _state ) const
		{
			std::size_t hash_value{};
			size_t shift{};

			for( const auto& spot : _state.m_hallway )
				hash_value = hash_value ^ ( hash<uint16_t>{}( spot.has_value( ) ? *spot : '.' ) << ++shift );

			for( const auto& room : _state.m_rooms )
			{
				for( const auto& spot : room )
				{
					hash_value = hash_value ^ ( hash<uint16_t>{}( spot.has_value( ) ? *spot : '.' ) << ++shift );
				}
			}

			return hash_value;
		}
	};
}