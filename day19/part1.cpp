import beacon_scanner;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <ranges>
#include <string_view>

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

using namespace beacon_scanner;

size_t CountUniqueBeacons( const std::vector<Scanner>& scanners );

Point ParsePoint( const std::string& line );

void
Result::ProcessOne( const std::string& data )
{
	if( data.substr( 0, 12 ) == "--- scanner " )
		m_scanners.push_back( Scanner( ) );
	else if( false == data.empty( ) )
		m_scanners.back( ).AddPoint( ParsePoint( data ) );
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( CountUniqueBeacons( m_scanners ) );
}

Point ParsePoint( const std::string& line )
{
	std::deque<std::string> tokens;

	boost::split(
		tokens,
		line,
		boost::is_any_of( "," ),
		boost::token_compress_on );

	if( tokens.size( ) != 3 )
		throw std::logic_error( "No a valid Point!" );

	Point result;
	std::transform(
		tokens.begin( ),
		tokens.end( ),
		result.m_coords.begin( ),
		[ ]( const std::string& token ) -> int
		{
			return (int)std::strtol(
				token.c_str( ),
				nullptr/*ignore*/,
				0/*auto detect*/ );
		} );

	return result;
}
