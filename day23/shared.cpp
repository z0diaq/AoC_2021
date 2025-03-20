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

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace amphipod;

Result::Result()
{

}

void
Result::Init()
{
	m_moveCosts[ A ] = 1;
	m_moveCosts[ B ] = 10;
	m_moveCosts[ C ] = 100;
	m_moveCosts[ D ] = 1000;
}

void
Result::Teardown()
{
	m_map.clear( );
}
