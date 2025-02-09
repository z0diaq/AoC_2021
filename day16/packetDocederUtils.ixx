module;

#include <string>
#include <iostream>
#include <bitset>
#include <numeric>
#include <vector>
#include <algorithm>

export module packet_decoder:utils;

export using ull = unsigned long long;

import :binary_holder;

export namespace packet_decoder
{
	namespace utils
	{
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
	}
}