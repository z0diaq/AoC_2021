import packet_decoder;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
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

using ull = unsigned long long;

using namespace packet_decoder;

class BinaryHolder;

void
Result::ProcessOne( const std::string& data )
{
	m_packet = data;
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
		return std::bitset<20>( GetNextStringChunk( bitsCount ) ).to_ulong( );
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

	unsigned int CurrentPosition( ) const
	{
		return static_cast< unsigned int >( m_currentPosition );
	}
};

ull DecodePacket( BinaryHolder& holder, unsigned int& sumOfPacketVersions );
std::string HexToBinary( const std::string& str );

std::string
Result::FinishPartOne( )
{
	unsigned int sumOfPacketVersions{ 0 };
	BinaryHolder holder( HexToBinary( m_packet ) );
	DecodePacket( holder, sumOfPacketVersions );

	return std::to_string( sumOfPacketVersions );
}

std::string
Result::FinishPartTwo( )
{
	unsigned int sumOfPacketVersions{ 0 };
	BinaryHolder holder( HexToBinary( m_packet ) );
	return std::to_string( DecodePacket( holder, sumOfPacketVersions ) );
}

ull ParseLiteralValue( BinaryHolder& holder );
ull ParseOperator( BinaryHolder& holder, const unsigned int typeID, unsigned int& sumOfPacketVersions );

ull DecodePacket( BinaryHolder& holder, unsigned int& sumOfPacketVersions )
{
	unsigned int versionNumber{ holder.GetNextChunk( 3 ) };
	sumOfPacketVersions += versionNumber;
	const unsigned int typeID{ holder.GetNextChunk( 3 ) };

	if( typeID == 4 )
		return ParseLiteralValue( holder );
	else
		return ParseOperator( holder, typeID, sumOfPacketVersions );
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

ull ParseLiteralValue( BinaryHolder& holder )
{
	std::string finalValue;
	while( true )
	{
		std::string nextChunk{ holder.GetNextStringChunk( 5 ) };
		finalValue.append( nextChunk.substr( 1 ) );
		if( nextChunk.front( ) == '0' )
			break;
	}

	if( finalValue.length( ) > 64 )
	{
		std::cerr << "FinalValue has " << finalValue.length( ) << " characters!" << std::endl;
		throw std::logic_error( "Need to use bigger bitset!" );
	}
	//holder.AdjustPadding( );
	return std::bitset<64>( finalValue ).to_ullong( );
}

ull ParseOperator( BinaryHolder& holder, unsigned int typeID, unsigned int& sumOfPacketVersions )
{
	unsigned int lengthTypeID = holder.GetNextChunk( 1 );
	std::vector<ull> packets{};

	if( lengthTypeID == 0 )
	{
		unsigned int totalLengthInBits = holder.GetNextChunk( 15 );
		const unsigned int startPosition = holder.CurrentPosition( );
		while( holder.CurrentPosition( ) - startPosition < totalLengthInBits )
		{
			packets.push_back( DecodePacket( holder, sumOfPacketVersions ) );

		}
	}
	else
	{
		unsigned int numberOfSubPackets = holder.GetNextChunk( 11 );
		for( unsigned int numPacket{ 0 }; numPacket < numberOfSubPackets; ++numPacket )
		{
			packets.push_back( DecodePacket( holder, sumOfPacketVersions ) );
		}
	}

	switch( typeID )
	{
	case 0:
		return std::accumulate( packets.begin( ), packets.end( ), 0ULL );
	case 1:
		return std::reduce( packets.begin( ), packets.end( ), 1ULL, std::multiplies<>( ) );
	case 2:
		return *std::min_element( packets.begin( ), packets.end( ) );
	case 3:
		return *std::max_element( packets.begin( ), packets.end( ) );
	case 5:
		return packets.front( ) > packets.back( );
	case 6:
		return packets.front( ) < packets.back( );
	case 7:
		return packets.front( ) == packets.back( );
	}

	throw std::logic_error( "Unhandled operator!" );

	return 0;
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
	ASSERT_EQ( binaryString, std::string( m_scenario.m_expectedResult ) );
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

TEST( DecodePacket, D2FE28 )
{
	BinaryHolder holder( HexToBinary( "D2FE28" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull value{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( value, 2021ULL );
}

TEST( VerifyProcessing, 38006F45291200 )
{
	BinaryHolder holder( HexToBinary( "38006F45291200" ) );

	unsigned int sumOfPacketVersions{ 0 };

	ASSERT_EQ( holder.GetNextChunk( 3 ), 1 );
	ASSERT_EQ( holder.GetNextChunk( 3 ), 6 );
	ASSERT_EQ( holder.GetNextChunk( 1 ), 0 );
	ASSERT_EQ( holder.GetNextChunk( 15 ), 27 );
	ASSERT_EQ( DecodePacket( holder, sumOfPacketVersions ), 10ULL );
	ASSERT_EQ( DecodePacket( holder, sumOfPacketVersions ), 20ULL );
}

TEST( VerifyProcessing, EE00D40C823060 )
{
	BinaryHolder holder( HexToBinary( "EE00D40C823060" ) );

	unsigned int sumOfPacketVersions{ 0 };

	ASSERT_EQ( holder.GetNextChunk( 3 ), 7 );
	ASSERT_EQ( holder.GetNextChunk( 3 ), 3 );
	ASSERT_EQ( holder.GetNextChunk( 1 ), 1 );
	ASSERT_EQ( holder.GetNextChunk( 11 ), 3 );
	ASSERT_EQ( DecodePacket( holder, sumOfPacketVersions ), 1ULL );
	ASSERT_EQ( DecodePacket( holder, sumOfPacketVersions ), 2ULL );
	ASSERT_EQ( DecodePacket( holder, sumOfPacketVersions ), 3ULL );
}

TEST( DecodePacket_SumOfVersions, 8A004A801A8002F478 )
{
	BinaryHolder holder( HexToBinary( "8A004A801A8002F478" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull value{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( sumOfPacketVersions, 16ULL );
}

TEST( DecodePacket_SumOfVersions, 8620080001611562C8802118E34 )
{
	BinaryHolder holder( HexToBinary( "620080001611562C8802118E34" ) );

	unsigned int sumOfPacketVersions{ 0 };
	DecodePacket( holder, sumOfPacketVersions );

	ASSERT_EQ( sumOfPacketVersions, 12 );
}

TEST( DecodePacket_SumOfVersions, 8C0015000016115A2E0802F182340 )
{
	BinaryHolder holder( HexToBinary( "C0015000016115A2E0802F182340" ) );

	unsigned int sumOfPacketVersions{ 0 };
	DecodePacket( holder, sumOfPacketVersions );

	ASSERT_EQ( sumOfPacketVersions, 23 );
}

TEST( DecodePacket_SumOfVersions, A0016C880162017C3686B18A3D4780 )
{
	BinaryHolder holder( HexToBinary( "A0016C880162017C3686B18A3D4780" ) );

	unsigned int sumOfPacketVersions{ 0 };
	DecodePacket( holder, sumOfPacketVersions );

	ASSERT_EQ( sumOfPacketVersions, 31 );
}

TEST( DecodePacket_ExecuteOperator, C200B40A82 )
{
	BinaryHolder holder( HexToBinary( "C200B40A82" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 3 );
}

TEST( DecodePacket_ExecuteOperator, 04005AC33890 )
{
	BinaryHolder holder( HexToBinary( "04005AC33890" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 54 );
}

TEST( DecodePacket_ExecuteOperator, 880086C3E88112 )
{
	BinaryHolder holder( HexToBinary( "880086C3E88112" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 7 );
}

TEST( DecodePacket_ExecuteOperator, CE00C43D881120 )
{
	BinaryHolder holder( HexToBinary( "CE00C43D881120" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 9 );
}

TEST( DecodePacket_ExecuteOperator, D8005AC2A8F0 )
{
	BinaryHolder holder( HexToBinary( "D8005AC2A8F0" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 1 );
}

TEST( DecodePacket_ExecuteOperator, F600BC2D8F )
{
	BinaryHolder holder( HexToBinary( "F600BC2D8F" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 0 );
}

TEST( DecodePacket_ExecuteOperator, 9C005AC2F8F0 )
{
	BinaryHolder holder( HexToBinary( "9C005AC2F8F0" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 0 );
}

TEST( DecodePacket_ExecuteOperator, 9C0141080250320F1802104A08 )
{
	BinaryHolder holder( HexToBinary( "9C0141080250320F1802104A08" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 1 );
}
