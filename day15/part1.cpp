import chitons;

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

using namespace chitons;

void
Result::ProcessOne( const std::string& data )
{
	m_map.push_back( data );
}

std::string
Result::FinishPartOne( )
{
	// TODO: implement A*

	return std::to_string( 0 );
}
