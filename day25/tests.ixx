export module sea_cucumber:tests;

import :types;

import <gtest/gtest.h>;

sea_cucumber::SeafloorRow ParseRow( const std::string& _dataRow );

namespace sea_cucumber
{
	std::vector<std::string>
	ToString( const SeafloorMap& _map )
	{
		std::vector<std::string> result;
		for( const SeafloorRow& row : _map )
		{
			std::string outRow;
			outRow.reserve( row.size( ) );
			for( const auto& cell : row )
			{
				switch( cell )
				{
				case SeaCucumber::FacingEast:
					outRow.push_back( '>' );
					break;
				case SeaCucumber::FacingSouth:
					outRow.push_back( 'v' );
					break;
				case SeaCucumber::None:
					outRow.push_back( '.' );
					break;
				}
			}
			result.push_back( std::move( outRow ) );
		}
		return result;
	}

	namespace tests
	{
		TEST( ParseRow, GivenEmptyRow_ExpectEmptyResult )
		{
			auto seafloorRow = ParseRow( "" );
			EXPECT_TRUE( seafloorRow.empty( ) );
		}

		TEST( ParseRow, GivenThreeItems_ExpectThreeItems )
		{
			auto seafloorRow = ParseRow( ".>v" );
			ASSERT_EQ( seafloorRow.size( ), 3 );
			EXPECT_EQ( seafloorRow[ 0 ], SeaCucumber::None );
			EXPECT_EQ( seafloorRow[ 1 ], SeaCucumber::FacingEast );
			EXPECT_EQ( seafloorRow[ 2 ], SeaCucumber::FacingSouth );
		}

		TEST( Step, GivenSampleDataAndSimpleStep_ExpectValidState )
		{
			
		}
	}
}