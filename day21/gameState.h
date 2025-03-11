#pragma once

#include <unordered_map>
#include <optional>
#include <array>

#include "playerInfo.h"

namespace dirac_dice
{
	std::uint32_t
	WrapPosition( std::uint32_t _position );

	using Wins = std::array<std::uint64_t, 2>;

	struct GameState
	{
	private:
		PlayerInfo m_player1;
		PlayerInfo m_player2;
		bool m_isPlayer1Turn{ };

	public:
		GameState( const PlayerInfo& _player1, const PlayerInfo& _player2, const bool _isPlayer1Turn );

		const PlayerInfo&
		GetPlayer1( ) const;

		const PlayerInfo&
		GetPlayer2( ) const;

		bool
		IsPlayer1Turn( ) const;

		std::optional<Wins>
		IsGameOver( ) const;

		GameState
		ApplyMove( std::uint32_t _diceSum ) const;

		bool
		operator==( const GameState& _rhs ) const;
	};
}

namespace std
{
	template<>
	struct hash< dirac_dice::GameState >
	{
		size_t operator()( dirac_dice::GameState const& _gameState ) const noexcept
		{
			size_t p1pHash{ hash<int>{}( _gameState.GetPlayer1( ).m_position ) };
			size_t p1sHash{ hash<int>{}( _gameState.GetPlayer1( ).m_score ) };
			size_t p2pHash{ hash<int>{}( _gameState.GetPlayer2( ).m_position ) };
			size_t p2sHash{ hash<int>{}( _gameState.GetPlayer2( ).m_score ) };
			size_t p1tHash{ hash<bool>{}( _gameState.IsPlayer1Turn( ) ) };

			// one of many possible hash combining methods
			return p1pHash ^ ( p1sHash << 1 ) ^ ( p2pHash << 2 ) ^ ( p2sHash << 3 ) ^ ( p1tHash << 4 );
		}
	};

} // namespace std