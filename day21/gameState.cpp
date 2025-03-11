
#include "gameState.h"

using dirac_dice::GameState;
using dirac_dice::PlayerInfo;
using dirac_dice::Wins;


GameState::GameState( const PlayerInfo& _player1, const PlayerInfo& _player2, const bool _isPlayer1Turn ) :
	m_player1( _player1 ), m_player2( _player2 ), m_isPlayer1Turn( _isPlayer1Turn )
{
}

const PlayerInfo&
GameState::GetPlayer1( ) const
{
	return m_player1;
}

const PlayerInfo&
GameState::GetPlayer2( ) const
{
	return m_player2;
}

bool
GameState::IsPlayer1Turn( ) const
{
	return m_isPlayer1Turn;
}

std::optional<Wins>
GameState::IsGameOver( ) const
{
	if( m_player1.m_score >= 21 )
		return Wins{ 1, 0 };
	else if( m_player2.m_score >= 21 )
		return Wins{ 0, 1 };
	else
		return std::nullopt;
}

GameState
GameState::ApplyMove( std::uint32_t _diceSum ) const
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

bool
GameState::operator==( const GameState& _rhs ) const
{
	return std::tie( m_player1, m_player2, m_isPlayer1Turn ) == std::tie( _rhs.m_player1, _rhs.m_player2, _rhs.m_isPlayer1Turn );
}










