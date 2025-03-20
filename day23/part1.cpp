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


void
Result::ProcessOne( const std::string& data )
{
	m_map.push_back( data );
}

Amphipod GetAmphipod( size_t _row, size_t _column, const Map& _map );

std::string
Result::FinishPartOne( )
{
	if( m_map.size( ) != 5 )
		return 0;

	State initialState;
	initialState.m_rooms[ 0 ][ 0 ] = GetAmphipod( 2, 3 );

	return std::to_string( 0 );
}

Amphipod GetAmphipod( size_t _row, size_t _column, const Map& _map )
{
	// TODO: extract from map
	// throw exception if not A-D

	return A;
}
