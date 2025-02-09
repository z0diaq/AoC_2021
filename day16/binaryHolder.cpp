import packet_decoder;

#include <string>
#include <bitset>
#include <numeric>
#include <stdexcept>

using packet_decoder::BinaryHolder;

BinaryHolder::BinaryHolder( const std::string& binaryData )
{
	m_binaryData = binaryData;
	m_currentPosition = 0;
}

unsigned int BinaryHolder::GetNextChunk( size_t bitsCount )
{
	return std::bitset<32>( GetNextStringChunk( bitsCount ) ).to_ulong( );
}

std::string BinaryHolder::GetNextStringChunk( size_t bitsCount )
{
	if( m_currentPosition + bitsCount > m_binaryData.size( ) )
	{
		throw std::logic_error( "Index out of bounds!" );
	}

	std::string result = m_binaryData.substr( m_currentPosition, bitsCount );
	m_currentPosition += bitsCount;
	return result;
}

void BinaryHolder::AdjustPadding( )
{
	const unsigned int beyondPaddingPosition{ m_currentPosition % 4 };
	if( beyondPaddingPosition )
		m_currentPosition += ( 4 - beyondPaddingPosition );
}

unsigned int BinaryHolder::CurrentPosition( ) const
{
	return static_cast< unsigned int >( m_currentPosition );
}
