import transparent_origami;

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
#include <boost/algorithm/string/replace.hpp>

using namespace transparent_origami;

void
Result::ProcessOne( const std::string& data )
{
	static bool seenFoldBy = false;

	if( m_sheet.empty( ) )
		seenFoldBy = false;

	if( false == seenFoldBy && Process( data ) )
		seenFoldBy = true;
}

std::string
Result::FinishPartOne( )
{
	int64_t visiblePoints{ 0 };
	for( const auto& line : m_sheet )
		visiblePoints += std::count( line.begin( ), line.end( ), '#' );

	return std::to_string( visiblePoints );
}
