#include <gtest/gtest.h>
import beacon_scanner;

using namespace beacon_scanner;

class ScannerTest : public ::testing::Test
{
protected:
	void SetUp( ) override
	{
		scanner.AddPoint( Point{ {1, 2, 3} } );
		scanner.AddPoint( Point{ {4, 5, 6} } );
		scanner.AddPoint( Point{ {7, 8, 9} } );
	}

	Scanner scanner;
};

TEST_F( ScannerTest, AddPoint )
{
	Scanner s;
	s.AddPoint( Point{ {1, 2, 3} } );

	const auto& points = s.GetPoints( );
	EXPECT_EQ( points.size( ), 1 );
	EXPECT_EQ( points[ 0 ], ( Point{ {1, 2, 3} } ) );
}

TEST_F( ScannerTest, GetPoints )
{
	const auto& points = scanner.GetPoints( );

	EXPECT_EQ( points.size( ), 3 );
	EXPECT_EQ( points[ 0 ], ( Point{ {1, 2, 3} } ) );
	EXPECT_EQ( points[ 1 ], ( Point{ {4, 5, 6} } ) );
	EXPECT_EQ( points[ 2 ], ( Point{ {7, 8, 9} } ) );
}

TEST_F( ScannerTest, GetAllRotations )
{
	auto rotations = scanner.GetAllRotations( );

	EXPECT_EQ( rotations.size( ), 3 );

	for( const auto& pointRotations : rotations )
		EXPECT_EQ( pointRotations.size( ), 24 );

	bool foundOriginal{ false };
	for( const auto& rot : rotations[ 0 ] )
	{
		if( rot == ( Point{ {1, 2, 3} } ) )
		{
			foundOriginal = true;
			break;
		}
	}
	EXPECT_TRUE( foundOriginal );
}
