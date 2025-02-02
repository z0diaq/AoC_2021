import packet_decoder;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <bitset>

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

using namespace packet_decoder;

void
Result::ProcessOne( const std::string& data )
{
	m_packet = data;
}

void DecodePacket( const std::string& packet );

std::string
Result::FinishPartOne( )
{
	return std::to_string( 0 );
}

std::string HexToBinary( const std::string& str );

class BinaryHolder
{
	std::string m_binaryData;
	size_t m_currentPosition;

public:
	BinaryHolder( const std::string& binaryData )
	{
		m_binaryData = binaryData;
		m_currentPosition = 0;
	}

	unsigned int GetNextChunk( size_t bitsCount )
	{
		unsigned int result{ 0 };
		if( m_currentPosition + bitsCount >= m_binaryData.size( ) )
			throw std::logic_error( "Index out of bounds!" );

		result = std::bitset<10>( m_binaryData.substr( m_currentPosition, bitsCount ) ).to_ulong( );
		m_currentPosition += bitsCount;
		return result;
	}

	std::string GetNextStringChunk( size_t bitsCount )
	{
		if( m_currentPosition + bitsCount >= m_binaryData.size( ) )
			throw std::logic_error( "Index out of bounds!" );

		return m_binaryData.substr( m_currentPosition, bitsCount );
	}
};

unsigned int ParseLiteralValue( BinaryHolder& holder );

void DecodePacket( const std::string& packet )
{
	BinaryHolder holder( HexToBinary( packet ) );

	unsigned int versionNumber = holder.GetNextChunk( 3 );
	unsigned int typeID = holder.GetNextChunk( 3 );
	if( typeID == 4 )
		unsigned int literalValue = ParseLiteralValue( holder );
	else
		;
}

std::string HexToBinary( const std::string& str )
{
	std::string binaryResult;

	binaryResult.reserve( str.length( ) * 4 );
	static const char* hexMap = "000010001100110011001100110011001100110011001100";

	for( char c : str ) {
		unsigned idx = ( unsigned )( c & 0xF );
		binaryResult.append( hexMap + ( idx << 1 ), 4 );
	}

	return binaryResult;
}

unsigned int ParseLiteralValue( BinaryHolder& holder )
{
	constexpr unsigned int notLastGroupMask = ( 1 << 4 );
	unsigned int nextChunk{ 0 };
	unsigned int result{ 0 };
	std::string result;
	do
	{
		nextChunk = holder.GetNextChunk( 5 );


	} while( nextChunk & notLastGroupMask );
}

