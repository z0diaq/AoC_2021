import packet_decoder;

#include <gtest/gtest.h>

using namespace testing;
using namespace packet_decoder;

TEST( DecodePacket, D2FE28 )
{
	BinaryHolder holder( utils::HexToBinary( "D2FE28" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull value{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( value, 2021ULL );
}

TEST( VerifyProcessing, 38006F45291200 )
{
	BinaryHolder holder( utils::HexToBinary( "38006F45291200" ) );

	unsigned int sumOfPacketVersions{ 0 };

	ASSERT_EQ( holder.GetNextChunk( 3 ), 1 );
	ASSERT_EQ( holder.GetNextChunk( 3 ), 6 );
	ASSERT_EQ( holder.GetNextChunk( 1 ), 0 );
	ASSERT_EQ( holder.GetNextChunk( 15 ), 27 );
	ASSERT_EQ( utils::DecodePacket( holder, sumOfPacketVersions ), 10ULL );
	ASSERT_EQ( utils::DecodePacket( holder, sumOfPacketVersions ), 20ULL );
}

TEST( VerifyProcessing, EE00D40C823060 )
{
	BinaryHolder holder( utils::HexToBinary( "EE00D40C823060" ) );

	unsigned int sumOfPacketVersions{ 0 };

	ASSERT_EQ( holder.GetNextChunk( 3 ), 7 );
	ASSERT_EQ( holder.GetNextChunk( 3 ), 3 );
	ASSERT_EQ( holder.GetNextChunk( 1 ), 1 );
	ASSERT_EQ( holder.GetNextChunk( 11 ), 3 );
	ASSERT_EQ( utils::DecodePacket( holder, sumOfPacketVersions ), 1ULL );
	ASSERT_EQ( utils::DecodePacket( holder, sumOfPacketVersions ), 2ULL );
	ASSERT_EQ( utils::DecodePacket( holder, sumOfPacketVersions ), 3ULL );
}

TEST( DecodePacket_SumOfVersions, 8A004A801A8002F478 )
{
	BinaryHolder holder( utils::HexToBinary( "8A004A801A8002F478" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull value{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( sumOfPacketVersions, 16ULL );
}

TEST( DecodePacket_SumOfVersions, 8620080001611562C8802118E34 )
{
	BinaryHolder holder( utils::HexToBinary( "620080001611562C8802118E34" ) );

	unsigned int sumOfPacketVersions{ 0 };
	utils::DecodePacket( holder, sumOfPacketVersions );

	ASSERT_EQ( sumOfPacketVersions, 12 );
}

TEST( DecodePacket_SumOfVersions, 8C0015000016115A2E0802F182340 )
{
	BinaryHolder holder( utils::HexToBinary( "C0015000016115A2E0802F182340" ) );

	unsigned int sumOfPacketVersions{ 0 };
	utils::DecodePacket( holder, sumOfPacketVersions );

	ASSERT_EQ( sumOfPacketVersions, 23 );
}

TEST( DecodePacket_SumOfVersions, A0016C880162017C3686B18A3D4780 )
{
	BinaryHolder holder( utils::HexToBinary( "A0016C880162017C3686B18A3D4780" ) );

	unsigned int sumOfPacketVersions{ 0 };
	utils::DecodePacket( holder, sumOfPacketVersions );

	ASSERT_EQ( sumOfPacketVersions, 31 );
}

TEST( DecodePacket_ExecuteOperator, C200B40A82 )
{
	BinaryHolder holder( utils::HexToBinary( "C200B40A82" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 3 );
}

TEST( DecodePacket_ExecuteOperator, 04005AC33890 )
{
	BinaryHolder holder( utils::HexToBinary( "04005AC33890" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 54 );
}

TEST( DecodePacket_ExecuteOperator, 880086C3E88112 )
{
	BinaryHolder holder( utils::HexToBinary( "880086C3E88112" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 7 );
}

TEST( DecodePacket_ExecuteOperator, CE00C43D881120 )
{
	BinaryHolder holder( utils::HexToBinary( "CE00C43D881120" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 9 );
}

TEST( DecodePacket_ExecuteOperator, D8005AC2A8F0 )
{
	BinaryHolder holder( utils::HexToBinary( "D8005AC2A8F0" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 1 );
}

TEST( DecodePacket_ExecuteOperator, F600BC2D8F )
{
	BinaryHolder holder( utils::HexToBinary( "F600BC2D8F" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 0 );
}

TEST( DecodePacket_ExecuteOperator, 9C005AC2F8F0 )
{
	BinaryHolder holder( utils::HexToBinary( "9C005AC2F8F0" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 0 );
}

TEST( DecodePacket_ExecuteOperator, 9C0141080250320F1802104A08 )
{
	BinaryHolder holder( utils::HexToBinary( "9C0141080250320F1802104A08" ) );

	unsigned int sumOfPacketVersions{ 0 };
	ull result{ utils::DecodePacket( holder, sumOfPacketVersions ) };

	ASSERT_EQ( result, 1 );
}
