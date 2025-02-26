import beacon_scanner;

#include <string>
#include <string_view>
#include <array>
#include <vector>

#include <stdexcept>
#include <ranges>
#include <algorithm>

using namespace beacon_scanner;

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
	return std::to_string( CountUniqueBeaconsWithScannerPositions( ).first );
}

Point
ParsePoint( const std::string& line )
{
	// Create a view of tokens split by commas
	auto tokens = line | std::views::split( ',' )
	                   | std::views::transform( [ ]( auto&& rng )
		{
			return std::string_view( &*rng.begin( ), std::ranges::distance( rng ) );
		} );

	// Validate token count
	if( std::ranges::distance( tokens ) != 3 )
		throw std::logic_error( "Not a valid Point!" );

	Point result;
	std::ranges::transform( tokens, result.m_coords.begin( ), [ ]( const auto& token ) -> int
		{
			return std::stoi( std::string( token ) );
		} );

	return result;
}
