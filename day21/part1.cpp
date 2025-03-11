import dirac_dice;

//leave what is needed
#include <string>
#include <stdexcept>

using namespace dirac_dice;

namespace dirac_dice
{
	std::uint32_t
	WrapPosition( std::uint32_t _position );
}

void
Result::ProcessOne( const std::string& data )
{
	auto colonPosition = data.find( ':' );
	if( colonPosition != std::string::npos )
	{
		std::string startingPosition = data.substr( colonPosition + 2 );
		std::uint32_t value = static_cast<std::uint32_t>( std::atoi( startingPosition.c_str( ) ) );
		if( value == 0 || value > 10 )
			throw std::runtime_error( "Unexpected source data format!" );

		if( m_players[ 0 ].m_position == 0 )
			m_players[ 0 ].m_position = value;
		else
		{
			if( m_players[ 1 ].m_position != 0 )
				throw std::runtime_error( "Player 2 already has position - not expecting that!" );
			m_players[ 1 ].m_position = value;
		}

	}
}

std::uint32_t
RollDice3Times( std::uint32_t& _currentDiceResult )
{
	std::uint32_t result{ 0 };
	
	for( int iteration{ 0 }; iteration != 3; ++iteration )
	{
		result += _currentDiceResult++;
		if( _currentDiceResult == 101 )
			_currentDiceResult = 1;
	}
	return result;
}

std::uint32_t
dirac_dice::WrapPosition( std::uint32_t _position )
{
	_position = _position % 10;
	if( _position == 0 )
		_position = 10;

	return _position;
}

std::string
Result::FinishPartOne( )
{
	std::uint16_t playerNum{ 0 };
	while( true )
	{
		m_players[ playerNum ].m_position += RollDice3Times( m_lastDiceResult );
		m_timesDiceRolled += 3;
		m_players[ playerNum ].m_position = WrapPosition( m_players[ playerNum ].m_position );
		m_players[ playerNum ].m_score += m_players[ playerNum ].m_position;
		if( m_players[ playerNum ].m_score >= 1000 )
			break;
		playerNum = ( playerNum + 1 ) % 2;
	}
	
	// assume player 2 won so take 1st player result * timeDiceRolled
	std::uint32_t result{ m_players[ 0 ].m_score * m_timesDiceRolled };
	// if player 1 won, then
	if( m_players[ 0 ].m_score >= 1000 )
		result = m_players[ 1 ].m_score * m_timesDiceRolled;

	return std::to_string( result );
}
