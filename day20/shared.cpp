import trench_map;

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

using namespace trench_map;

void
Result::Init()
{
	m_inImage = false;
	m_enhanceAlgorithm.reserve( 512 );
	m_scanLineNumber = 0;
	m_bounds[ 0 ] = m_bounds[ 1 ] = m_bounds[ 2 ] = m_bounds[ 3 ] = 0;
}

void
Result::Teardown()
{
	m_enhanceAlgorithm.clear( );
	m_litPixelsSet.clear( );
}
