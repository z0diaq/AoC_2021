import reactor_reboot;

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
#include <functional>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace reactor_reboot;

void
Result::ProcessTwo( const std::string& _data )
{
	ProcessOne( _data );
}

std::string
Result::FinishPartTwo( )
{
	std::vector<Cuboid> onCuboids;
	for( const Command& command : m_commands )
	{
		std::vector<Cuboid> newOnCuboids;

		if( command.m_isOn )
		{
		}
		else
		{
		}
	}

	return std::to_string( 0 );
}