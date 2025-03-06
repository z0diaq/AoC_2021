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
Result::ProcessOne( const std::string& data )
{
	auto colonPosition = data.find( ':' );
	if( colonPosition != std::string::npos )
	{
		std::string startingPosition = data.substr( colonPosition );
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

std::string
Result::FinishPartOne( )
{
	std::uint16_t playerNum{ 0 };
	for( ; m_players[ playerNum ].m_score < 1000; ++playerNum )
	{
		playerNum = playerNum % 2;
		m_players[ playerNum ].m_position += 3 * ( m_lastDiceResult + 1 );
		m_players[ playerNum ].m_position = m_players[ playerNum ].m_position % 10;
		m_players[ playerNum ].m_score += m_players[ playerNum ].m_position;
		m_timesDiceRolled += 3;
	}
	
	std::uint32_t result{ m_players[ 0 ].m_score * m_timesDiceRolled };
	if( m_players[ 0 ].m_score >= 1000 )
		result = m_players[ 0 ].m_score * m_timesDiceRolled;

	return std::to_string( result );
}
