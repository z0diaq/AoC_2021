import extended_polymerization;

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

using namespace extended_polymerization;

Result::Result()
{

}

void
Result::Init()
{

}

void
Result::Teardown()
{
	m_template.clear( );
	m_pairInsertionRules.clear( );
}
