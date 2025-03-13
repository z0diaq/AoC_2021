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

#include <regex>
#include <unordered_set>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace reactor_reboot;

void
Result::ProcessOne( const std::string& data )
{
	static const std::regex pattern( R"((on|off) x=(-?\d+)\.\.(-?\d+),y=(-?\d+)\.\.(-?\d+),z=(-?\d+)\.\.(-?\d+))" );

	std::smatch matches;
	if( std::regex_match( data, matches, pattern ) ) {
		m_commands.emplace_back(
			matches[ 1 ] == "on",
			Range{std::stoi( matches[ 2 ] ), std::stoi( matches[ 3 ] )},
			Range{std::stoi( matches[ 4 ] ), std::stoi( matches[ 5 ] )},
			Range{std::stoi( matches[ 6 ] ), std::stoi( matches[ 7 ] )}
		);
	}
}

std::string
Result::FinishPartOne( )
{
	std::unordered_set<Point3D> activatedPoints{};



	return std::to_string( 0 );
}
