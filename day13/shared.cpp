import transparent_origami;

#include <iostream>
#include <string>
#include <algorithm>

#include <boost/lexical_cast.hpp>

using namespace transparent_origami;

void
Result::Teardown()
{
	m_sheet.clear( );
}

bool
Result::Process( const std::string& data )
{
	if( data.empty( ) )
		return false;

	if( std::isdigit( data[ 0 ] ) )
		ReadPoint( data );

	if( data.substr( 0, 10 ) == "fold along" )
	{
		ResizeLines( );
		ReadAndExecuteFoldOperation( data );
		return true;
	}

	return false;
}

void
Result::ReadPoint( const std::string& data )
{
	auto pos = data.find( ',' );
	auto strX = data.substr( 0, pos );
	auto strY = data.substr( pos + 1 );

	size_t x = boost::lexical_cast< size_t >( strX );
	size_t y = boost::lexical_cast< size_t >( strY );

	std::cout << data << " => " << x << "," << y << std::endl;
	while( y + 1 > m_sheet.size( ) )
		m_sheet.push_back( std::string( ) );

	auto& str = m_sheet[ y ];
	if( str.length( ) <= x )
		str.resize( x + 1, '.' );

	str[ x ] = '#';
}

void
Result::ReadAndExecuteFoldOperation( const std::string& data )
{
	const bool foldByX = data[ 11 ] == 'x';
	int foldPosition = boost::lexical_cast< int >( data.substr( 13 ) );
	std::cout << data << " fold by " << ( foldByX ? "x" : "y" ) << " at " << foldPosition << std::endl;

	std::cout << "before fold:" << std::endl;

	for( size_t lineNo = 0; lineNo != m_sheet.size( ); ++lineNo )
		std::cout << lineNo << "] " << m_sheet[ lineNo ] << std::endl;

	if( foldByX )
	{
		for( size_t col = 1; ; ++col )
		{
			if( foldPosition + col == m_sheet[ 0 ].length( ) )
				break;
			for( auto& line : m_sheet )
				if( line[ foldPosition + col ] == '#' )
					line[ foldPosition - col ] = '#';
		}

		for( auto& line : m_sheet )
			line.resize( foldPosition );
	}
	else
	{
		for( size_t lineNo = 1; ; ++lineNo )
		{
			if( foldPosition + lineNo == m_sheet.size( ) )
				break;

			const auto& str = m_sheet[ foldPosition + lineNo ];
			if( str.empty( ) )
				continue;

			auto& line = m_sheet[ foldPosition - lineNo ];
			line.resize( std::max( line.length( ), str.length( ) ), '.' );

			for( size_t pos = 0; pos != str.length( ); ++pos )
				if( str[ pos ] == '#' )
					line[ pos ] = '#';
		}

		m_sheet.resize( foldPosition );
	}
}

void
Result::ResizeLines( )
{
	size_t longestLineLength = 0;

	std::for_each( m_sheet.begin( ), m_sheet.end( ), [&longestLineLength]( const std::string& line )
	{
		longestLineLength = std::max( longestLineLength, line.length( ) );
	} );

	std::for_each( m_sheet.begin( ), m_sheet.end( ), [longestLineLength]( std::string& line )
	{
		line.resize( longestLineLength, '.' );
	} );
}
