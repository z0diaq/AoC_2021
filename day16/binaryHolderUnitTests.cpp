import packet_decoder;

#include <gtest/gtest.h>

using namespace testing;
using namespace packet_decoder;

TEST( GetNextChunk, CheckProcessing_D2FE28 )
{
	BinaryHolder holder( utils::HexToBinary( "D2FE28" ) );

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
	auto binaryString = utils::HexToBinary( m_scenario.m_hexString );
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
