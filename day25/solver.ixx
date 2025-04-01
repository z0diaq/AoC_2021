export module sea_cucumber:solver;

import :result;
import :types;

import <string>;
import <algorithm>;
import <iterator>;
import <stdexcept>;

using namespace sea_cucumber;

SeafloorRow ParseRow( const std::string& _dataRow );

void
Result::ProcessOne( const std::string& data )
{
	m_initialSeafloorMap.push_back( ParseRow( data ) );
}

std::string
Result::FinishPartOne( )
{
	auto result = Step( { m_initialSeafloorMap, 0, false } );
	while( result.m_changed )
		result = Step( result );

	return std::to_string( result.m_iterationNumber );
}

void
Result::ProcessTwo( const std::string& data )
{
}

std::string
Result::FinishPartTwo( )
{
	return std::to_string( 0 );
}

SeafloorRow ParseRow( const std::string& _dataRow )
{
	SeafloorRow row( _dataRow.length( ), SeaCucumber::None );

	std::transform( _dataRow.begin( ), _dataRow.end( ), row.begin( ), [ ]( const char _c ) {
		switch( _c )
		{
		case '.':
			return SeaCucumber::None;
		case '>':
			return SeaCucumber::FacingEast;
		case 'v':
			return SeaCucumber::FacingSouth;
		default:
			throw std::logic_error( "Invalid sea cucumber type: " + std::to_string( _c ) );
		}
		} );

	return row;
}