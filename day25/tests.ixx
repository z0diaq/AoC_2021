export module sea_cucumber:tests;

import :types;
import :result;

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

	SeafloorMap
	CreateMapFromStrings( const std::vector<std::string>& strings )
	{
		SeafloorMap map;
		map.reserve( strings.size( ) );

		for( const auto& str : strings )
			map.push_back( ParseRow( str ) );

		return map;
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

		TEST( ParseRow, GivenAllEmpty_ExpectAllNone )
		{
			auto seafloorRow = ParseRow( "...." );
			ASSERT_EQ( seafloorRow.size( ), 4 );
			for( const auto& cell : seafloorRow )
				EXPECT_EQ( cell, SeaCucumber::None );
		}

		TEST( ParseRow, GivenAllEast_ExpectAllFacingEast )
		{
			auto seafloorRow = ParseRow( ">>>>" );
			ASSERT_EQ( seafloorRow.size( ), 4 );
			for( const auto& cell : seafloorRow )
				EXPECT_EQ( cell, SeaCucumber::FacingEast );
		}

		TEST( ParseRow, GivenAllSouth_ExpectAllFacingSouth )
		{
			auto seafloorRow = ParseRow( "vvvv" );
			ASSERT_EQ( seafloorRow.size( ), 4 );
			for( const auto& cell : seafloorRow )
				EXPECT_EQ( cell, SeaCucumber::FacingSouth );
		}

		TEST( ParseRow, GivenMixedPattern_ExpectCorrectMapping )
		{
			auto seafloorRow = ParseRow( ".>v.>v>" );
			ASSERT_EQ( seafloorRow.size( ), 7 );
			EXPECT_EQ( seafloorRow[ 0 ], SeaCucumber::None );
			EXPECT_EQ( seafloorRow[ 1 ], SeaCucumber::FacingEast );
			EXPECT_EQ( seafloorRow[ 2 ], SeaCucumber::FacingSouth );
			EXPECT_EQ( seafloorRow[ 3 ], SeaCucumber::None );
			EXPECT_EQ( seafloorRow[ 4 ], SeaCucumber::FacingEast );
			EXPECT_EQ( seafloorRow[ 5 ], SeaCucumber::FacingSouth );
			EXPECT_EQ( seafloorRow[ 6 ], SeaCucumber::FacingEast );
		}

		class SeaCucumberFixture : public ::testing::Test
		{
		protected:
			void
			VerifyMoveEast( SeafloorMap& map, SeafloorMap& expected )
			{
				Result result;
				result.m_initialSeafloorMap = map;

				// Create iteration state with our map
				IterationState state{ map, 0 };

				// Manually create a map with east-moving cucumbers only
				auto [afterEast, changed] = result.MoveEastOnly( state.m_currentMap, false );

				// Verify the map after east movement
				ASSERT_EQ( afterEast.size( ), expected.size( ) );
				for( size_t row = 0; row < afterEast.size( ); ++row )
				{
					ASSERT_EQ( afterEast[ row ].size( ), expected[ row ].size( ) );
					for( size_t col = 0; col < afterEast[ row ].size( ); ++col )
					{
						EXPECT_EQ( afterEast[ row ][ col ], expected[ row ][ col ] )
							<< "Mismatch at row " << row << ", col " << col;
					}
				}
			}

			void
			VerifyFullStep( SeafloorMap& map, SeafloorMap& expected )
			{
				Result result;
				result.m_initialSeafloorMap = map;

				// Create iteration state with our map
				IterationState state{ map, 0 };

				// Perform full step
				auto newState = result.Step( state );
				auto& afterStep = newState.m_currentMap;

				// Verify the map after the step
				ASSERT_EQ( afterStep.size( ), expected.size( ) );
				for( size_t row = 0; row < afterStep.size( ); ++row )
				{
					ASSERT_EQ( afterStep[ row ].size( ), expected[ row ].size( ) );
					for( size_t col = 0; col < afterStep[ row ].size( ); ++col )
					{
						EXPECT_EQ( afterStep[ row ][ col ], expected[ row ][ col ] )
							<< "Mismatch at row " << row << ", col " << col;
					}
				}
			}
		};


		TEST_F( SeaCucumberFixture, GivenSingleEastCucumber_ExpectMovement )
		{
			// Initial state: single east-facing cucumber at (0,0)
			auto map = CreateMapFromStrings( {
				">.",
				".."
				} );

			// Expected state: cucumber moved east
			auto expected = CreateMapFromStrings( {
				".>",
				".."
				} );

			VerifyMoveEast( map, expected );
		}

		TEST_F( SeaCucumberFixture, GivenEastCucumberAtEdge_ExpectWrapAround )
		{
			// Initial state: east-facing cucumber at right edge
			auto map = CreateMapFromStrings( {
				".>",
				".."
				} );

			// Expected state: cucumber wrapped around to left
			auto expected = CreateMapFromStrings( {
				">.",
				".."
				} );

			VerifyMoveEast( map, expected );
		}
	}
}