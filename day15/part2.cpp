import chitons;

#include <string>

using namespace chitons;

void
Result::ProcessTwo(const std::string& data)
{
	ProcessOne( data );
}

std::string IncrementString( std::string _row, char _increase );

std::string
Result::FinishPartTwo()
{
	auto newMap = m_map;

	for( size_t row = 0; row != m_map.size( ); ++row )
	{
		std::string& newRow = newMap[ row ];
		for( char repeat = 1; repeat < 5; ++repeat )
			newRow.append( IncrementString( m_map[ row ], repeat ) );
	}

	for( char repeat = 1; repeat < 5; ++repeat )
		for( size_t row = 0; row != m_map.size( ); ++row )
		{
			newMap.push_back( IncrementString( newMap[ row ], repeat ) );
		}

	m_map.swap( newMap );

	return FinishPartOne( );
}

std::string IncrementString( std::string _row, char _increase )
{
	for( char& c : _row )
	{
		c += _increase;
		if( c > '9' )
			c = '0' + ( c - '9' );
	}
	return _row;
}
