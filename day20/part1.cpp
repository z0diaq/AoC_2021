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
ProcessNextScanLine( LitPixelsSet& _litPixelsSet, const std::string& _data, int _scanLineNumber );

void
Result::ProcessOne( const std::string& data )
{
	if( m_inImage )
	{
		ProcessNextScanLine( m_litPixelsSet, data, m_scanLineNumber++ );
		m_bounds[ MAX_X ] = std::max( m_bounds[ MAX_X ], static_cast< int >( data.length( ) ) );
		m_bounds[ MAX_Y ] = m_scanLineNumber;
	}
	else
	{
		if( data.empty( ) )
			m_inImage = true;
		else
			m_enhanceAlgorithm.append( data );
	}
}

std::string
Result::FinishPartOne( )
{
	return std::to_string( 0 );
}

void
ProcessNextScanLine( LitPixelsSet& _litPixelsSet, const std::string& _data, int _scanLineNumber )
{
	for( int x{ 0 }; x != static_cast< int >( _data.length( ) ); ++x )
		if( _data[ x ] == '#' )
			_litPixelsSet.emplace( Pixel{ x, _scanLineNumber });
}
