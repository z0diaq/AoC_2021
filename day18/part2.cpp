import snailfish;

#include <string>

using namespace snailfish;

void
Result::ProcessTwo( const std::string& data )
{
	m_numbers.push_back( data );
}

std::string
Result::FinishPartTwo( )
{
	int maxMagnitude = 0;

	// Try each pair of numbers in both orders
	for( size_t i = 0; i < m_numbers.size( ); ++i ) {
		for( size_t j = 0; j < m_numbers.size( ); ++j ) {
			if( i == j ) continue;

			maxMagnitude = std::max( maxMagnitude,
			                         Magnitude(
			                                   Add(
			                                       Parse( m_numbers[ i ] ),
			                                       Parse( m_numbers[ j ] ) ) ) );
		}
	}

	return std::to_string( maxMagnitude );
}