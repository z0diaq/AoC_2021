#pragma once

#include <unordered_map>
#include <optional>
#include <array>

#include "playerInfo.h"


std::uint32_t
WrapPosition( std::uint32_t _position );

using Wins = std::array<std::uint64_t, 2>;


namespace dirac_dice
{
	struct GameState
	{
	private:
		PlayerInfo m_player1;
		PlayerInfo m_player2;
		bool m_isPlayer1Turn{ };

	public:
		GameState( const PlayerInfo& _player1, const PlayerInfo& _player2, const bool _isPlayer1Turn ) :
			m_player1( _player1 ), m_player2( _player2 ), m_isPlayer1Turn( _isPlayer1Turn )
		{
		}

		const PlayerInfo& GetPlayer1( ) const
		{
			return m_player1;
		}

		const PlayerInfo& GetPlayer2( ) const
		{
			return m_player2;
		}

		bool IsPlayer1Turn( ) const
		{
			return m_isPlayer1Turn;
		}

		std::optional<Wins> IsGameOver( ) const
		{
			if( m_player1.m_score >= 21 )
				return Wins{ 1, 0 };
			else if( m_player2.m_score >= 21 )
				return Wins{ 0, 1 };
			else
				return std::nullopt;
		}

		GameState ApplyMove( std::uint32_t _diceSum ) const
		{
			if( m_isPlayer1Turn )
			{
				const std::uint32_t newPlayer1Position{ WrapPosition( m_player1.m_position + _diceSum ) };
				const std::uint32_t newPlayer1Score{ m_player1.m_score + newPlayer1Position };
				return GameState( PlayerInfo{ newPlayer1Position, newPlayer1Score }, m_player2, false );
			}
			else
			{
				const std::uint32_t newPlayer2Position{ WrapPosition( m_player2.m_position + _diceSum ) };
				const std::uint32_t newPlayer2Score{ m_player2.m_score + newPlayer2Position };
				return GameState( m_player1, PlayerInfo{ newPlayer2Position, newPlayer2Score }, true );
			}
		}

		bool operator==( const GameState& _rhs ) const
		{
			return std::tie( m_player1, m_player2, m_isPlayer1Turn ) == std::tie( _rhs.m_player1, _rhs.m_player2, _rhs.m_isPlayer1Turn );
		}
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