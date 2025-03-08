import dirac_dice;

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

using namespace dirac_dice;

void
Result::ProcessTwo(const std::string& _data)
{
	ProcessOne( _data );
}

struct GameState
{
	PlayerInfo m_player1;
	PlayerInfo m_player2;
	std::uint32_t m_player2Score{ };
	bool m_isPlayer1Turn{ };

	std::size_t GetHash( ) const
	{
		std::size_t p1pHash{ std::hash<int>{}( m_player1.m_position ) };
		std::size_t p1sHash{ std::hash<int>{}( m_player1.m_score ) };
		std::size_t p2pHash{ std::hash<int>{}( m_player2.m_position ) };
		std::size_t p2sHash{ std::hash<int>{}( m_player2.m_score ) };
		std::size_t p1tHash{ std::hash<bool>{}( m_isPlayer1Turn ) };

		// one of many possible hash combining methods
		return p1pHash ^ ( p1sHash << 1 ) ^ ( p2pHash << 2 ) ^ ( p2sHash << 3 ) ^ ( p1tHash << 4 );
	}
};

struct GameStateHash {
	std::size_t
	operator()( const GameState& _state ) const
	{
		return _state.GetHash( );
	}
};

std::string
Result::FinishPartTwo()
{
	using Wins = std::array<std::uint64_t, 2>;

	constexpr std::uint32_t winScore{ 21 };

	std::unordered_map<GameState, Wins, GameStateHash> memoization;

	GameState initialState{ m_players[ 0 ], m_players[ 1 ] };

	return std::to_string(0);
}
