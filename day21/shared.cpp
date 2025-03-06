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
#include <numeric>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace dirac_dice;

Result::Result()
{

}

void
Result::Init()
{
	m_players[ 0 ] = m_players[ 1 ] = { 0, 0 };
	m_lastDiceResult = 1U;
	m_timesDiceRolled = 0;
}

void
Result::Teardown()
{

}
