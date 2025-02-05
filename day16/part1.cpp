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

#include <gtest/gtest.h>

using namespace packet_decoder;

class BinaryHolder;

void
Result::ProcessOne( const std::string& data )
{
	m_packet = data;
}

void DecodePacket( BinaryHolder& holder );

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
		return std::bitset<10>( GetNextStringChunk( bitsCount ) ).to_ulong( );
	}

	std::string GetNextStringChunk( size_t bitsCount )
	{
		if( m_currentPosition + bitsCount > m_binaryData.size( ) )
		{
			std::cout << "current pos" << m_currentPosition << " + " << bitsCount << " vs size=" << m_binaryData.size( ) << std::endl;
			throw std::logic_error( "Index out of bounds!" );
		}

		std::string result = m_binaryData.substr( m_currentPosition, bitsCount );
		m_currentPosition += bitsCount;
		return result;
	}

	void AdjustPadding( )
	{
		const unsigned int beyondPaddingPosition{ m_currentPosition % 4 };
		if( beyondPaddingPosition )
			m_currentPosition += ( 4 - beyondPaddingPosition );
	}
};

unsigned int ParseLiteralValue( BinaryHolder& holder );
unsigned int ParseOperator( BinaryHolder& holder );

void DecodePacket( BinaryHolder& holder )
{
	

	unsigned int versionNumber = holder.GetNextChunk( 3 );
	unsigned int typeID = holder.GetNextChunk( 3 );
	if( typeID == 4 )
		unsigned int literalValue = ParseLiteralValue( holder );
	else
		unsigned int operatorValue = ParseOperator( holder );
}

std::string HexToBinary( const std::string& str )
{
	std::string binaryResult;

	binaryResult.reserve( str.length( ) * 4 );
	static const char* hexMap = "0000000100100011010001010110011110001001101010111100110111101111";

	for( char hex : str ) {
		unsigned idx = ( hex >= '0' && hex <= '9' ) ? ( hex - '0' ) : 10 + ( hex - 'A' );
		binaryResult.append( hexMap + ( idx * 4 ), 4 );
	}

	return binaryResult;
}

unsigned int ParseLiteralValue( BinaryHolder& holder )
{
	std::string finalValue;
	while( true )
	{
		std::string nextChunk{ holder.GetNextStringChunk( 5 ) };
		finalValue.append( nextChunk.substr( 1 ) );
		if( nextChunk.front( ) == '0' )
			break;
	}

	std::cout << "final LiteralValue string = " << finalValue << std::endl;

	if( finalValue.length( ) > 30 )
	{
		std::cerr << "FinalValue has " << finalValue.length( ) << " characters!" << std::endl;
		throw std::logic_error( "Need to use bigger bitset!" );
	}
	holder.AdjustPadding( );
	return std::bitset<30>( finalValue ).to_ulong( );
}


unsigned int ParseOperator( BinaryHolder& holder )
{
	unsigned int lengthTypeID = holder.GetNextChunk( 1 );

	if( lengthTypeID == 0 )
	{
		unsigned int totalLengthInBits = holder.GetNextChunk( 15 );
	}
	else
	{
		unsigned int numberOfSubPackets = holder.GetNextChunk( 11 );

	}
}






using namespace testing;


TEST( GetNextChunk, CheckProcessing_D2FE28 )
{
	BinaryHolder holder( HexToBinary( "D2FE28" ) );

	ASSERT_EQ( holder.GetNextChunk( 3 ), 6 );
	ASSERT_EQ( holder.GetNextChunk( 3 ), 4 );
	ASSERT_EQ( holder.GetNextChunk( 5 ), 23 ); // 10111
	ASSERT_EQ( holder.GetNextChunk( 5 ), 30 ); // 11110
	ASSERT_EQ( holder.GetNextChunk( 5 ), 5 );  // 00101
	ASSERT_EQ( holder.GetNextChunk( 3 ), 0 );  //   000 padding
}


struct TestScenario
{
	std::string m_hexString;
	std::string m_expectedResult;
	std::string m_description;
};

class HexToBinaryTest : public TestWithParam<TestScenario>
{
protected:
	void SetUp( ) override
	{
		m_scenario = GetParam( );
	}

	TestScenario m_scenario;
};

TEST_P( HexToBinaryTest, BasicValues )
{
	auto binaryString = HexToBinary( m_scenario.m_hexString );
	ASSERT_EQ( binaryString, std::string( m_scenario.m_expectedResult ));
}

INSTANTIATE_TEST_SUITE_P(
	HexToBinaryTests,
	HexToBinaryTest,
	::testing::Values(
		TestScenario{ "0", "0000", "Zero" },
		TestScenario{ "1", "0001", "One" },
		TestScenario{ "4", "0100", "Four" },
		TestScenario{ "5", "0101", "Five" },
		TestScenario{ "6", "0110", "Size" },
		TestScenario{ "7", "0111", "Seven" },
		TestScenario{ "8", "1000", "Eight" },
		TestScenario{ "9", "1001", "Nine" },
		TestScenario{ "A", "1010", "A" },
		TestScenario{ "B", "1011", "B" },
		TestScenario{ "C", "1100", "C" },
		TestScenario{ "D", "1101", "D" },
		TestScenario{ "E", "1110", "E" },
		TestScenario{ "F", "1111", "F" },
		TestScenario{ "D2FE28", "110100101111111000101000", "D2FE28" }
	),
[ ]( const testing::TestParamInfo<HexToBinaryTest::ParamType>& p ) { return p.param.m_description; }
);

TEST( ParseLiteralValue, D2FE28 )
{
	BinaryHolder holder( HexToBinary( "D2FE28" ) );

	// skip first 6 bits - they are of no concern to us
	holder.GetNextChunk( 6 );//result ignored

	unsigned int literalValue = ParseLiteralValue( holder );

	ASSERT_EQ( literalValue, 2021 );
}
