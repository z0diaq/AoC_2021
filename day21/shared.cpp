import dirac_dice;

using namespace dirac_dice;

void
Result::Init()
{
	m_players[ 0 ] = m_players[ 1 ] = { 0, 0 };
	m_lastDiceResult = 1U;
	m_timesDiceRolled = 0;
}
